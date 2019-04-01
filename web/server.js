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

app.get('/', function(req, res) {
  res.sendFile('home.html', {root: __dirname })
});

app.get('/home.html', function(req, res) {
  res.sendFile('home.html', {root: __dirname })
});

app.get('/credits.html', function(req, res) {
  res.sendFile('credits.html', {root: __dirname})
});


// change the baud rate for different sampling speeds
var serialName = process.argv[2];
var parser = new Readline();
var serialPort = new SerialPort(serialName, {
  baudRate: 19200
});
serialPort.pipe(parser);


parser.on('data', function(data) {
  // var values = data.toString().split(',');
  // console.log(values[0]);
  broadcast(data.toString());
})

serialPort.on('open', function() {
  console.log('port open');
});
// serialPort.on('data', function(data) {
//   console.log(data);
// });
serialPort.on('close', function() {
  console.log("port closed");
});
serialPort.on('error', function(error) {
  console.log('error: ' + error);
});

var server = app.listen(port);

// web socket stuff
wss.on('connection', handleConnection);

function handleConnection(client) {
  console.log("New Connection");
  connections.push(client);
  client.on('close', function() {
    console.log("Connection closed");
    var position = connections.indexOf(client);
    connections.splice(position, 1);
  })
}

function broadcast(data) {
  console.log(data);
  for (c in connections)  {
    connections[c].send(data);
  }
}
