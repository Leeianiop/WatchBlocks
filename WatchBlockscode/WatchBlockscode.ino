#include <SPI.h>
#include <Wire.h>
#include <RTClib.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <XPT2046_Touchscreen.h>
#include <ESP32Servo.h>

// --- Pin Definitions ---
#define TFT_CS   D1
#define TFT_DC   D2  // 'A0' pin maps to Data/Command
#define TFT_RST  D3
#define TOUCH_CS  D0
#define TOUCH_IRQ D5 
#define SERVO_PIN D6

// RTC I2C Pins (From your code)
#define RTC_SDA   D4
#define RTC_SCL   D7

Adafruit_ST7735 tft(TFT_CS, TFT_DC, TFT_RST);
XPT2046_Touchscreen ts(TOUCH_CS, TOUCH_IRQ); 
Servo servo;
RTC_DS3231 rtc;

#define SCREEN_W 160
#define SCREEN_H 128

// --- Touchscreen Calibration Constants ---
#define TS_MINX 300
#define TS_MAXX 3800
#define TS_MINY 300
#define TS_MAXY 3800

// --- Modern 16-bit RGB565 Color Palette ---
#define COLOR_BG      0x18C3 
#define COLOR_CARD    0x2946 
#define COLOR_ACCENT  0x3CD9 
#define COLOR_TEXT    0xFFFF 
#define COLOR_MUTED   0x9CF3 
#define COLOR_ON      0x34EB 
#define COLOR_OFF     0xD224 
#define COLOR_SHADOW  0x0841 

bool servoOn = false;
unsigned long lastClockUpdate = 0;

enum Screen {
  HOME,
  CLOCK_VIEW,
  SETTINGS
};

Screen screen = HOME;

bool pressed(int px, int py, int x, int y, int w, int h) {
  return (px > x && px < x + w && py > y && py < y + h);
}

void drawBack() {
  tft.fillRoundRect(8, 8, 55, 24, 6, COLOR_SHADOW);
  tft.fillRoundRect(5, 5, 55, 24, 6, COLOR_CARD);
  tft.drawRoundRect(5, 5, 55, 24, 6, 0x4B55); 
  
  tft.setTextColor(COLOR_TEXT);
  tft.setTextSize(1);
  tft.setCursor(12, 13);
  tft.print("< BACK");
}

void drawIcon(int x, int y, uint16_t accentColor, const char* txt) {
  tft.fillRoundRect(x + 3, y + 3, 64, 52, 10, COLOR_SHADOW);
  tft.fillRoundRect(x, y, 64, 52, 10, COLOR_CARD);
  tft.fillRect(x + 10, y + 6, 44, 3, accentColor);
  
  tft.setTextSize(1);
  tft.setTextColor(COLOR_TEXT);
  int length = strlen(txt);
  int x_offset = (64 - (length * 6)) / 2; 
  
  tft.setCursor(x + x_offset, y + 26);
  tft.print(txt);
}

// Dynamically updates the real-time clock header on the Home Screen
void updateHomeClock() {
  if (!rtc.begin()) return;
  DateTime now = rtc.now();
  
  char buf[9];
  sprintf(buf, "%02d:%02d:%02d", now.hour(), now.minute(), now.second());
  
  // Clean text background overlay boundary box
  tft.fillRect(10, 8, 140, 16, COLOR_BG);
  
  tft.setTextColor(COLOR_TEXT);
  tft.setTextSize(2);
  tft.setCursor(32, 8);
  tft.print(buf);
}

void drawHome() {
  screen = HOME;
  tft.fillScreen(COLOR_BG);
  
  // Render the initial RTC Time header
  updateHomeClock();
  
  tft.drawFastHLine(10, 30, 140, 0x2946); 
  
  // App icons rearranged beautifully underneath the main clock
  drawIcon(12, 42, 0xF52A, "SERVO"); 
  drawIcon(84, 42, COLOR_ACCENT, "DETAILS");  
}

void drawClockView() {
  screen = CLOCK_VIEW;
  tft.fillScreen(COLOR_BG);
  drawBack();
  
  tft.setTextColor(COLOR_MUTED);
  tft.setTextSize(1);
  tft.setCursor(68, 13);
  tft.print("RTC STATUS");
}

void updateClockViewPage() {
  if (!rtc.begin()) return;
  DateTime now = rtc.now();

  char timeBuf[12];
  char dateBuf[12];
  sprintf(timeBuf, "%02d:%02d:%02d", now.hour(), now.minute(), now.second());
  sprintf(dateBuf, "%02d/%02d/%04d", now.month(), now.day(), now.year());
  
  tft.fillRoundRect(12, 48, 136, 60, 8, COLOR_CARD);
  tft.drawRoundRect(12, 48, 136, 60, 8, 0x10A2); 

  tft.setTextSize(2); 
  tft.setTextColor(0x07E0); // Electric digital green
  tft.setCursor(32, 58);
  tft.print(timeBuf);

  tft.setTextSize(1);
  tft.setTextColor(COLOR_MUTED);
  tft.setCursor(48, 88);
  tft.print(dateBuf);
}

void drawSettings() {
  screen = SETTINGS;
  tft.fillScreen(COLOR_BG);
  drawBack();
  
  tft.setTextColor(COLOR_TEXT);
  tft.setTextSize(2);
  tft.setCursor(15, 42);
  tft.print("Servo Control");

  tft.setTextColor(COLOR_MUTED);
  tft.setTextSize(1);
  tft.setCursor(15, 62);
  tft.print("Position Switch Panel");
  
  uint16_t switchColor = servoOn ? COLOR_ON : COLOR_OFF;
  tft.fillRoundRect(30, 82, 100, 32, 16, switchColor);
  
  if (servoOn) {
    tft.fillCircle(114, 98, 12, COLOR_TEXT); 
  } else {
    tft.fillCircle(46, 98, 12, COLOR_TEXT);  
  }
}

void moveServoFast(int target) {
  servo.write(target); 
}

void toggleServo() {
  servoOn = !servoOn;
  if (servoOn) {
    moveServoFast(90);
  } else {
    moveServoFast(0);
  }
  drawSettings();
}

void setup() {
  SPI.begin(D8, D9, D10); 
  Wire.begin(RTC_SDA, RTC_SCL); // Initializes your specified RTC I2C pins
  
  tft.initR(INITR_GREENTAB);
  tft.setRotation(3); 
  
  pinMode(TOUCH_CS, OUTPUT);
  digitalWrite(TOUCH_CS, HIGH);
  
  ts.begin(SPI); 
  ts.setRotation(3); 
  
  rtc.begin(); // Spins up the DS3231 timing hardware
  
  servo.attach(SERVO_PIN);
  servo.write(0);
  
  drawHome();
}

void loop() {
  // Handles non-blocking clock refresh cycles every second
  if (millis() - lastClockUpdate >= 1000) {
    lastClockUpdate = millis();
    if (screen == HOME) {
      updateHomeClock();
    } else if (screen == CLOCK_VIEW) {
      updateClockViewPage();
    }
  }

  if (ts.touched()) {
    TS_Point p = ts.getPoint();
    
    if (p.z > 200) {
      int x = map(p.x, TS_MINX, TS_MAXX, 0, SCREEN_W);
      int y = map(p.y, TS_MINY, TS_MAXY, 0, SCREEN_H);
      
      delay(75); 

      if (screen == HOME) {
        // Left Button (Servo Control)
        if (pressed(x, y, 2, 35, 74, 85)) {
          drawSettings();
        }
        // Right Button (Clock View Details)
        else if (pressed(x, y, 74, 35, 84, 85)) {
          drawClockView();
        }
      } 
      else {
        if (pressed(x, y, 0, 0, 75, 45)) {
          drawHome();
        }

        if (screen == SETTINGS) {
          if (pressed(x, y, 15, 72, 130, 50)) {
            toggleServo();
          }
        }
      }
    }
  }
  delay(10);
}