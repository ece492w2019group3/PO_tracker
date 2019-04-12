# PO_tracker
Position and orientation tracking system using an IMU. Potential applications for biomechanical gait analysis to measure how far a foot moves and the changes in the foot's orientation while a user walks. 

The ArduinoCode folder contains most of the algorithms and code required to interface the IMU with the Arduino 2560 Mega. The main file in this folder is under the OrientationCalculation folder and is called OrientationCalculation.ino. Uploading this code to the Arduino will run the code to obtain sensor readings from the IMU and process the data to obtain orientation and position

The web folder contains the code for displaying the graphs of orientation and position on a webpage. Server.js handles the server side code, while home.html contains the plotting and client capabilities. 

To run this code:
1. Connect the 3.3V and ground of the Arduino to the VDD and GND pins of the
IMU. Connect the SDA/SCL pins of the Arduino to the same pins on the IMU.
(Suggested to use a ribbon cable for these 4 connections)
2. Connect the USB blaster port to the computer which will display the results
a. The computer must have Node.js and the Arduino IDE installed
3. Upload the Arduino code if not already uploaded through the Arduino IDE
a. May need to select the Arduino board and port in the Tools section
4. Open a terminal and navigate to the /web/ folder of the project. (on windows you
must use the dedicated Node.js terminal)
5. Run the command: node ./server.js this will list the current ports available on
your computer, one of which should be the connected Arduino
6. Run the command again, but adding the name of the port as a command line
argument.
7. Open an internet browser and navigate to http://localhost:3000 to connect to the
server and view the results on graphical plots.
