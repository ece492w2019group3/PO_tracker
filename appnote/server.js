/*  server.js by Maxime Houle
*   Dependencies: - requires Node.js installed
*   - express, serialport, and ws from npm
*
*   Execute format: node /path/to/server.js <serialport> [baudrate]
*   omit <serialport> to obtain a list of active serial ports
*   [baudrate] is optional, default is 9600
*
*   This program demonstrates basic serial port, websocket, and express server
*   activity as a basic tutorial. Useful for reading printed output from any
*   board through USB connection, possibly manipulating the values, and then
*   sending the information through a websocket.
*/

//  This appnote uses the following 3 libraries
const express = require('express');
var SerialPort = require('serialport');
var WebSocketServer = require('ws').Server;
var Readline = SerialPort.parsers.Readline;

const PORT = 3000;
const WS_PORT = 8080;
var baudRate = 9600;

//  print serial ports if missing serial port argument
if (process.argv.length < 3) {
  SerialPort.list(function (err, ports) {
    ports.forEach(function(port) {
      console.log(port.comName);
    });
  });
  console.log("Usage: node /path/to/server.js <serialport> [baudrate]");
  return;
}
if (process.argv.length > 3) {
  baudRate = parseInt(process.argv[3]);
}

//  create basic http server, websocket, and prepare list of clients
var app = express();
var wss = new WebSocketServer({port: WS_PORT});
var connections = new Array;

//  server will respond to a '/' request by sending the home.html file
app.get('/', function(req, res) {
  res.sendFile('home.html', {root: __dirname })
});

//  create the serialport object using the baudRate and
//  the user defined serial port name
//  typically for OSX users this will be in the form /dev/tty.usbmodemXXXX
var serialName = process.argv[2];
//  default of ReadLine() is to parse on newline.
//  can change this character to ',' for example, which will
//  set the parser to separate input on ',' instead of newlines.
var parser = new Readline();
var serialPort = new SerialPort(serialName, {
  baudRate: baudRate
});
//  we will pipe the data from the serial port through the ReadLine parser.
serialPort.pipe(parser);

//  on receiving data the parser will execute the function below.
//  "receiving data" occurs when the parser detects the parsing character
//  used as the input of the ReadLine constructor on line 55.
//  To demonstrate modification of data, we set the string to uppercase
//  before broadcasting to all connections.
parser.on('data', function(data) {
  var uppercase = data.toString().toUpperCase();
  console.log(data.toString());
  for (c in connections)  {
    connections[c].send(uppercase);
  }
})

//  init function when connecting to serial port.
serialPort.on('open', function() {
  console.log('port open');
});

//  clean up function when serial port connection is closed
serialPort.on('close', function() {
  console.log("port closed");
});

serialPort.on('error', function(error) {
  console.log('error: ' + error);
});

var server = app.listen(PORT);

// execute handleConnection function
// when a new client connects to the websocket
wss.on('connection', handleConnection);

//  this program handles clients by adding them to them to a list
//  when new data is obtained, the parser 'data' function will
//  broadcast the data to all current connections
//
//  additionally provides a clean up function to any new clients
//  which is performed when a connection is closed.
function handleConnection(client) {
  console.log("New Connection");
  connections.push(client);
  //  cleanup function
  client.on('close', function() {
    console.log("Connection closed");
    var position = connections.indexOf(client);
    connections.splice(position, 1);
  })
}
