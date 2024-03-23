# freeRTOSproject
---
Project for learning about the freeRTOS framework. This will become more defined later but for now, I'm using the ESP32 board with the ESPIDF for learning about how to properly use an RTOS. 

This project is based off one I have completed already in college where I made a crude gardening center with a Arduino IoT 33 controlled in the Arduino cloud. But this project is to expand on that and use a more advanced structure than Arduino.

### How to compile the program.
---
This project is built inside of PlatformIO. Please download PlatformIO inside VSCode extensions.

You can then open and build this project through the "Open Project" button on the top left.
I am using an ESP32 board from a random Amazon seller (Who is  not on Amazon anymore so I can't share the link...)
and it is very possible you would also select the board  "nodemcu-32s" 


### Project Tools
---
This project is using the ESP-IDF framework. Which is much more complex than the alternative to Arduino.

ESP-IDF is not nearly as bare metal as something like the STM32, but it still gives you very similar tools.
freeRTOS is added into the ESP-IDF framework, this project is going to take a more exagerated way to solve problems, so that I can utilize freeRTOS and gain experience from this project.


### Project Longterm Goals
---
This project will host a 1 or 2 ESP32 project.
**1st Step:** 
I plan on building a gardening automation project that also collects humidity, temperature, and soil moisture levels. The project will also control water pumps to keep the plant watered. 
The data this project will produce will more than likely lead to a Data project as well, for dashboarding. So the data will need to be moved off of the controller. I will either:
    - Setup a RaspiPi API on my local network to feed the data into (This is a project I've been planning on doing for awhile, just haven't set it up yet)
    - Feed it into Firebase instead since it's a free platform.

We also more than likely need to set up a lite http server, so that whatever controller is connected to it, we can read immediate data and use the pump as needed.

**2nd Step:** 
We need a way to control the garden center. 
- I am leaning towards O1, since this will make the project self contained. Give me controller experience and LCD experience as well.

*Option 1:* We build a small control box. That can be used anywhere in the house, which would use a 2nd ESP32 that would directly connect to the Garden HTTP server. This controller will GET the current state/readings of each sensor and be able to POST a command to run the pump.

*Option2:* Instead of a 2nd IoT device, we'll do everything the same but in a Mobile App/Web Page. Will probably port forward the device on my network if I do this.  


#### Debugging Notes
---
If using the ESP-Prog for using a debugger like I am, use this video as reference for setup.

(Remember if you get the red error the driver just needs to be regenerated in zadig)


https://www.youtube.com/watch?v=TivyIFF-dzw&t=34s&ab_channel=BrianLough