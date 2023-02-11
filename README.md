# MyMorning
The repo contains all the firmware codes for the project and instructions on how to load them to the hardware.

## Requirements
1) Download and setup the Arduino ide [here](https://www.arduino.cc/en/software) if you don't have it already installed for your machine.
2) Install the board support package for ESP32 by goint to ` Tools > Board:xx > Board Manager`. In the search bar type ESP32 and select install ESP32 by Espressif Systems.
3) Now select `ESP32 Dev Module` from ` Tools > Board:--- > ESP32 Arduino > ESP32 Dev Module`

## Download the files 
4)  Download all the files on the `Code`:arrow_down_small: on this platform, In your downloads you will get the a folder :file_folder:  `MyMorningArduino`this will have:
 - `main` - containing actual code
 - `library.zip` - this contains the libraries used in the project
 - `MyMorning.apk` - the app

## Library Installation
5)  Unzip the `library.zip` and copy and paste all the different folders inside to your Arduino library directory usually `user/documents/arduino/library` folder :file_folder:

6)  Run Arduino and open the `main` folder. Compile and upload to the hardware. `(procedure on how to use the ide is on the tutorial link)`:link:
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
Open the `Serial Monitor` to see the serial data as sent or received from either of the boards using the FTDI programmer or any USB to TTL converter so that you can have access to a serial port. Check out the headers on the board for uart communications.

## Operation
- Once the code is uploaded, open MyMorning app and turn on bluetooth.
- Go to `Devices` tab and pair your device.
- This will sync time from your phone to the device. You can also set time in `main.ino` in `setupTime()`.
- Create an alarm as desired. maybe a minute away.
- When the alarm rings and the motor vibrates, a single button press will snooze the alarm while a long press will stop the alarm.
- On snoozing, the alarm will vibrate again after the snooze time.

# To implement: 
- battery monitoring
- esp32-sleep
- choose vibration patterns

# END


