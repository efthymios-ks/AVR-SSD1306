# AVR SSD1306 Library  

---

**Description:**  
A library to control SSD1306-based GLCD using AVR microcontrollers.  
+ Functions include:  
  + Basic operations.  
  + Geometrical objects (draw/fill/invert rectangle/circle/triangle etc.).  
  _These functions have been searched for and found in various Arduino libraries. Their logic and functionality is not to be credited to me. I have only gathered, studied and modified them so that they work under AVR-GCC environmemt._  
  + Printing text anywhere in the screen using custom imported fonts.  
  + Printing pictures.  
   _Read the bottom of "SSD1306.h" to see all functions available._  
+ A screen buffer stored in RAM is used to complete the operations faster at the cost of memory size (128x64 pixels / 8 = 1kB).  
_You can edit the **GLCD_BufferWrite** and **GLCD_BufferRead** functions to change the buffer's location from the RAM to the EEPROM or any other external memory source._  
+ The GLCD is interfaced using the TWI (I2C) protocol at 400KHz. You can use your own or my included TWI library.  
+ There is an error checking option while tranceiving data via TWI protocol. If you are not using my library, you have to either define the codes or disable error checking.
+ My custom I/O macros are required and are included.  

---  

**Memory usage:**  
+ Program: 0 bytes  
+ Data: 1034 bytes  
  + Display buffer: 1024 bytes (128x(64/8))
  + Display auxiliary data: 10 bytes  
  
**Compiler:**  
AVR-GCC  
  
**Optimization Level:**  
Optimize (-O1)  
  
--- 
**How to create a new font:**  
(needs some advanced knowledge)  
 1. Download the free **GLCD Font Creator** from **MikroElektronika**, install it and run it.  
 2. If you are on Windows 7, run the program under **Windows XP (Service Pack 3) compatibility mode** (google it), else you won't be able to save fonts.  
 3. File > New Font > Import an Existing System Font.  
 4. Choose your font, press ok to each pop-up window and wait for the processing to finish.  
 5. Export for GLCD > mikroC > X-GLCD Lib > Samsung KS0108 > Save.  
 6. Change the extension of the produced file from **.c** to **.h**.
 7. Open the file and add **Include Guards** (google it again).  
 8. Import the file into your project and your code.  
 _Include Guards example:_  
    `#ifndef _FONTNAME_H_`  
    `#define _FONTNAME_H_`  
    `//The content of the file`  
    `#endif`  

---
  
![picture alt](https://raw.githubusercontent.com/efthymios-ks/AVR-SSD1306-Library/master/Demonstration%20(1).PNG)
![picture alt](https://raw.githubusercontent.com/efthymios-ks/AVR-SSD1306-Library/master/Demonstration%20(2).PNG)
  
--- 
