# DESK LAMP FIRMWARE
The repo contains all the firmware codes for the project and instructions on how to load them to the hardware

## Requirements
1) Set up the IDE, for this application you will need to download the Arduino ide [here](https://www.arduino.cc/en/software) if you don't have it already installed for your distributions
2) Instal the board support package for ESP32 by goint to ` Tools > Board:xx > Board Manager`. In the search bar type ESP32 and select install ESP32 by Espressid Systems.  
3) Now select TinyPico from ` Tools > Board:xx > ESP32 Arduino > TinyPico`

 Once done proceed to the next instructions.
## Download the files 
4)  Download all the files on the `Code`:arrow_down_small: on this platform, In your downloads you will get the a folder :file_folder:  `desk_lamp_firmware`this will have:
 - desk_lamp_firmware - containing actual code
 - library -this contains all the related libraries used in the project

## Library Installation
5)  On library installation open the folder `library` folder:file_folder downloaded above:,
copy and paste all the folders to your directory `documents/arduino/library` folder :file_folder:

6)  Open the `desk_lamp_firmware.ino`  on `desk_lamp_firmware`folder :file_folder: with the downloaded ide, compile and upload to the hardware `(procedure on how to use the ide is on the tutorial link)`:link:
[tutorial](https://www.youtube.com/watch?v=nL34zDTPkcs&t=3s)

# Uploading the codes  :arrow_up:
You can buy the FTDI from here :link: [buy ftdi](https://www.amazon.com/HiLetgo-FT232RL-Converter-Adapter-Breakout/dp/B00IJXZQ7C/ref=sr_1_3?keywords=FTDI&qid=1650483928&sr=8-3)
or here  :link: [buy usbasp](https://www.amazon.com/CP2102-Module-Converter-Downloader-Compatible/dp/B092YMT52G_)

1) Insert the FTDI programmer cable socket onto UART headers. ...
2) Open Arduino IDE software. ...
3) Next, call out the source code. ...
4) Select “FTDI” from the Tools > Programmer menu.
5) Select “Upload using Programmer” from the File menu.

You can also explore more from the following tutorial :link:[How to Use FTDI Programmer to upload Code](https://www.youtube.com/watch?v=JYchUapoqzc)

## Debugging 
To see the serial data as sent or received from either of the boards we can use the FTDI programmer or any USB to TTL converter so that you can have access to a serial port. Check out the headers on the board for uart communications 

## Operation of desk lamp
- Press on/off button to turn the lamp on or off
- Color button is used to select between 3 color modes: warm , neutral and cool white
- Brightness up is used to increase brightness of the led from 10% to 100%
- Brightness down button is used to decrease brightness down up to 10%

# END


