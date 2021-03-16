const SerialPort = require('serialport');

const portName = process.argv[2];

let myPort = new SerialPort(portName, 9600);
myPort.on('data', (data) => {
  console.log(data.toString('hex'));
});
