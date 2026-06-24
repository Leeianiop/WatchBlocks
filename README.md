# WatchBlocks
The New Fashion is Customizable  
![WatchBlocks](Images/ZINE.png)

## Inspired by the legendary "PhoneBlocks"  
A watch that can be added on extensions.

## How it started
This idea came to me when I saw the story of the PhoneBlocks Movement and how it eventually died out. I suppose an issue was also that nobody was willing to risk having their phones being blocks., and rather go with traditional "Big Brands"  
So, I lowered it down into a compact watch, well its more of a wrist bracelet thingymabob if you think about it. (WatchBlocks sounds cooler than Wrist-Bracelet-ThingymabobBlocks)  

## BOM
# WatchBlocks - Bill of Materials (BOM)

## Core Components

| Component | Description | Qty | Cost |
|------------|------------|------|------|
| ESP32S3 XIAO | Microcontroller | 1 | $13.73 |
| 1.8" TFT Touch Screen Display | UI Display | 1 | $2.57 |
| Perfboard Wires | Connect the circuit | 1 | $1.48 |
| Female Pin Header (1x40) | Solder to PCB | 1 | $0.20 |
| Male Pin Header (1x40) | Connect extensions to socket | 6 | $0.72 |
| Magnets (10 pcs) | Locking extensions and closures | 1 | $1.20 |
| DS3231 RTC Module | Track local time offline | 1 | $2.21 |

## Power System

| Component | Description | Qty | Cost |
|------------|------------|------|------|
| Lipo Battery 3.7v | Supply power | 1 | $1.03 |
| Velcro Strap | Wrist strap | 1 | $3.01 |
| Velcro Patch | Attach block to strap | 1 | $1.15 |

## Speaker Extension

| Component | Description | Qty | Cost |
|------------|------------|------|------|
| 4Ω Speaker | Audio output | 1 | $3.63 |

## Rocket Launcher 3000 Extension

| Component | Description | Qty | Cost |
|------------|------------|------|------|
| Servo Motor | Launch mechanism | 1 | $1.54 |
| Springs | Hold and launch rockets | 1 | $0.76 |

---

# Total Cost

**$33.51**

## Files
STL files include an extentions folder which are for the speaker extention and rocket launcher extentions.     
If you want to make your own extention which you definetly should (its the whole purpose of this project) modify (WatchBlocksTemplate)    
PCB file has 2 pcb inside for the top (left) and bottom layer (right).  PCB also has 8 layers, below are all of them separately (Last layer contains nothing)  
![WatchBlocks](Images/Layers/1.png)  
![WatchBlocks](Images/Layers/2.png)  
![WatchBlocks](Images/Layers/3.png)  
![WatchBlocks](Images/Layers/4.png)  
![WatchBlocks](Images/Layers/5.png)  
![WatchBlocks](Images/Layers/6.png)  
![WatchBlocks](Images/Layers/7.png)  
![WatchBlocks](Images/Layers/8.png)  
![WatchBlocks](Images/Layers/3d.png)  
![WatchBlocks](Images/WBPCB.png)  
## Where everything goes  
### 1. Start by soldering the wires then sliding in the tft.  
![WatchBlocks](Images/WBM.png)  
### 2. Close the lid & fit both the sliders in, remember to fit the wires of the tft through the hole and into the main case.
![WatchBlocks](Images/WBS.png)  
### 3. Align with Main Case and Hot glue them with the nuts and screws  
![WatchBlocks](Images/WBMS.png)  
### 4. IMPORTANT!! solder bottom pcb first (the one with 12 pin headers) Place xiao in (bottom to top), then use perfboard wire to connect them with XIAO, only then insert PCB in  
![WatchBlocks](Images/WBBPCB.png)  
![WatchBlocks](Images/WBXIAO.jpeg)  
![WatchBlocks](Images/WBXIAO1.png)  
### 5. Now solder the to pcb with the XIAO and place it in, then put on the cover (WatchBlocksSocket)  
![WatchBlocks](Images/WBSO.png)   
### 6. Place Lipo battery in this cover, then connect with VBUS and GND to the pin headers
![WatchBlocks](Images/WBBS.png)  
### 7. Fit your RTC module in here and connect directly to the XIAO sharing the same I2C bus  
![WatchBlocks](Images/WBRTC.png)  
### 8. Close the MAIN Lid, and that's it, really simple !!  
![WatchBlocks](Images/WBML.png)  
## Final assembly below (Including PCB):  
![WatchBlocks](Images/FinalAssembly/FAM.png)  
![WatchBlocks](Images/FinalAssembly/FAMS.png)  
# Battery Extention:  
![WatchBlocks](Images/FinalAssembly/FAB.png)  
![WatchBlocks](Images/FinalAssembly/FABC.png) 

## Extentions
For the servo extension, get springs and hot glue them down, it's the only way to keep them locked in place,   
Screw on the hinge to the servo then mount the servo.  
Also install 4x1x7 pin headers at the bottom and connect with the servo according to the schematic  
### Final assembly below:  
![WatchBlocks](Images/FinalAssembly/FASP.png)    
![WatchBlocks](Images/FinalAssembly/FASPB.png)   
For the speaker just slot it in and solder to pin headers according to the schematic. 
### Final Assembly below:  
![WatchBlocks](Images/FinalAssembly/FAS.png)    
![WatchBlocks](Images/FinalAssembly/FASB.png)   
## Schematic
For those who think the schematic is hard to comprehend, it is just pin headers connected to their corresponding pin of the XIAO, so its like every extention is a XIAO itself. The components work by sharing the same i2c or spi bus also.  
![WatchBlocks](Images/WBSCH.png)  

## Make Your Own Extension?
Just work on the (WatchBlocksTemplate) file but instead of female pin headers make the bottom male pin headers. Then update the code according to your components.

## Notes
Hope you like and enjoy this project as much as I do, 36 hours logged :)


