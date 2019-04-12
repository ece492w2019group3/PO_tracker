const express = require('express');
var SerialPort = require('serialport');
var WebSocketServer = require('ws').Server;
var Readline = SerialPort.parsers.Readline;

const hostname = '127.0.0.1';
const port = 3000;
const WS_PORT = 8080;

// print serial ports if missing serial port argument
if (process.argv.length < 3) {
  SerialPort.list(function (err, ports) {
    ports.forEach(function(port) {
      console.log(port.comName);
    });
  });
  console.log("Usage: node ./server.js <serialport>");
  return;
}

var app = express();
var wss = new WebSocketServer({port: WS_PORT});
var connections = new Array;

// HTTP handlers
app.get('/', function(req, res) {
  res.sendFile('home.html', {root: __dirname })
});

app.get('/home.html', function(req, res) {
  res.sendFile('home.html', {root: __dirname })
});

app.get('/credits.html', function(req, res) {
  res.sendFile('credits.html', {root: __dirname})
});

// turn on HTTP server
var server = app.listen(port);
// end of HTTP handlers

// read serial port name from command line arguments
var serialName = process.argv[2];
var parser = new Readline();
// Baudrate set to maximum of USB
var serialPort = new SerialPort(serialName, {
  baudRate: 115200
});
// serial port output will be piped through the readline parser
// the parser will activate the "on data" handler only when a "\n" is
// obtained from serial port
serialPort.pipe(parser);

// parser "on data" handler
parser.on('data', function(data) {
  broadcast(data.toString());
})

// serial port handlers
serialPort.on('open', function() {
  console.log('port open');
});

serialPort.on('close', function() {
  console.log("port closed");
  for (c in connections) {
    connections[c].close();
  }
  process.exit();
});
serialPort.on('error', function(error) {
  console.log('error: ' + error);
});
// end serial port handlers

// web socket stuff
wss.on('connection', handleConnection);

// on receiving a new client, add to list of clients for broadcasting data
// include an "on close" handler for each client which removes the client
// from the list of connections
function handleConnection(client) {
  console.log("New Connection");
  connections.push(client);
  client.on('close', function() {
    console.log("Connection closed");
    var position = connections.indexOf(client);
    connections.splice(position, 1);
  })
}

// Echo data to terminal and send obtained data to all clients
function broadcast(data) {
  console.log(data);
  for (c in connections)  {
    connections[c].send(data);
  }
}
// end websocket stuff
