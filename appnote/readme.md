Application Note from Group 3, completed by Maxime Houle (mhoule@ualberta.ca)

Example and tutorial on serial communication with Node.js and plotting data to
a browser. For this example, an Arduino mega 2560 was used as the serial input
of the node server, but any serial input should be usable.
Requirements:
- Arduino device (but a different device connected serially could be used with the right output format)  
- Computer compatible with Node.js  

Instructions:
1) Install Node.js (https://nodejs.org/en/) Windows or macOS installers provided
2) Clone the contents of this appnote.

When refering to the terminal, for macOS the standard terminal is usable,
for Windows, installing Node.js will provide a Node.js command prompt.

3) In the terminal, navigate to the folder with server.js
We must now install the node dependencies to run server.js
4) In the terminal, run the following commands (Working directory same as server.js):

```
npm install express
npm install serialport
npm install ws
```

Steps 5-9 are for using the Arduino example code. If you wish to use a different
board, you will need to create code for that device which performs similarly to
the Arduino code (arduino_example.ino) provided in this application note.

5) Install the Arduino IDE (https://www.arduino.cc/en/main/software) (Don't need to donate)
6) Connect the Arduino through USB connection to your computer.
7) Open the Arduino IDE and select the open button, and select arduino_example.ino
8) Verify and upload the code to the board.
  * You will likely need to select the board in the Tools>Board menu option,
    and the port in the Tools>Port menu.
  * The port you select here will look similar to the port required as the input of server.js
9) Open the serial monitor (Tools>Serial Monitor) and set the baudrate to 9600.
The monitor should display lines similar to: "one 1 0.5". Close the serial monitor.

Now that the code is running on the Arduino (or the device you have decided to use)
we can read the serial output through running the server.js file.

10) With the terminal used in step 4) run the following command:

``node ./server.js``

11) The program will now display a list of serial ports which could be used with
the program. One of these should be the serial device you want to read.
12) Now rerun the command but this time add the serial device as an argument:

``node ./server.js  /dev/tty.usbmodemXXXX``

Above is the format that the current (April 5th 2019) macOS system displays usb connections,
with XXXX being replaced with a 4 digit number.

13) The terminal should display lines similar to what was observed in step 9) if
you are using the Arduino example.

Since we don't want to display our data on a terminal this next part demonstrates
a simple way to plot streamed (x,y) coordinate data in HTML. For your own implementation
you will likely want to plot with a more specific type of graph. There are many
other options available for plotly, which can be explored using the link in the
sources section at the end of these instructions.

14) Our server.js program accepts connections on port 3000 as an http server. Open
a web browser and navigate to "http://localhost:3000" while the node program is
still running.
15) The web browser now displays a 2-D graph of points labeled with the word
and coordinates of each line output by the serial port. The code in home.html
limits the number of displayed points to 20 to prevent clutter.

Code index:
* arduino_example/arduino_example.ino: Arduino example code which creates and
outputs a known format (string int float) through the serial port.

* home.html: html code, uses websockets to connect to server.js for obtaining
graph data

* server.js: Node.js code, reads serial port data, sets string to uppercase, and
sends the data through websockets to connected clients. Also acts as http server
which sends home.html on request.

Sources:  
https://plot.ly/javascript/  
https://github.com/ITPNYU/physcomp/tree/master/labs2014/Node%20Serial%20Lab  
Last accessed on April 5th 2019  
