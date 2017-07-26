# Serial v3
This serial library is an asynchronous serial communication protocol between a raspberry pi as a master, and an arduino as a slave. 

# Hardware Setup
There are two lines in this protocol. A request line, and a data line. The request line is connected to pin 9 on the arduino and pin 17 on the raspberry pi. The data line is connected to pin 10 on the arduino and pin 27 on the raspberry pi. 

# Software Setup
On the Arduino side of the code, the function:
```c
beginSerial();
```
should be in the setup to initialize the pins.
To request a trasmission from the raspberry pi, run the function:
```c
receiveSerial();
```
The command and data bytes are stored in commandRecieved and dataRecieved respectively. 

# How it Works
If the arduino requests a transmission, the first thing that occurs is that the request line is powered on. The raspberry pi will send  one bit down the data line to signal that it has acknowledged the request. Then, at 75 us pulses the raspberry pi sends down the command bit. At the same time, the arduino is recording the bits in a buffer. Once the command bit has been sent, the system goes into a synchronization mode to synchronize the clocks again. The raspberry pi holds the data line high for 100 us before sending the data bit. The arduino uses this specific pulse to resynchronize its clock to match the speed of the incoming bits. 

# Issues
This code is nowhere near perfect. For my purposes, I need it to be run under 2000 us, so  if you want to use it for faster speeds, it may not work as well. Becuase I don't have an osilliscope, I can't measure exactly where the arduino is reading the incoming bitstream. As a result, there are some *magic* delays in the code to center the read along the bitstream which I determined through guess and check. If you want to increase the speed, those delays may have to be changed. Also, the very first read will be off becuase the arduino needs to calculate how much time the raspberry pi takes to send its data, so that the Arduino can set its delays accordingly. 