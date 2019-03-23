const express = require('express');
var SerialPort = require('serialport');

const hostname = '127.0.0.1';
const port = 3000;

var app = express();
app.get('/', function(req, res) {
  res.sendFile('home.html', {root: __dirname })
});

app.get('/home.html', function(req, res) {
  res.sendFile('home.html', {root: __dirname })
});

app.get('/credits.html', function(req, res) {
  res.sendFile('credits.html', {root: __dirname})
});


// change the port name here when changing computer
// change the baud rate for different sampling speeds
// var serialPort = new SerialPort('/dev/ttyACM0', {
//     baudRate: 57600,
//     parser: new SerialPort.parsers.Readline("\n")
// });
//
// // Read the port data
// serialPort.on("open", function () {
//     console.log('open');
//     port.on('data', function(data) {
//         console.log(data);
//     });
// });

var server = app.listen(port);
