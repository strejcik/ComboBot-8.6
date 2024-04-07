'use strict';



let express = require('express');
let app = express();
let http = require('http');
let server = http.createServer(app);
var net = require('net');




const connectedSockets = new Set();

// broadcast to all connected sockets except one
connectedSockets.broadcast = function(data, except) {
    for (let sock of this) {
        if (sock !== except) {
            sock.write(data);
        }
    }
}



var s = net.createServer(function(socket) {
  console.log('User connected.');
connectedSockets.add(socket);
  socket.on('data', (data) => {
    connectedSockets.broadcast(data, socket);
  });

  socket.on('end', function () {
    console.log('end, socket disconnected', socket.name);
    //removePairedUser(socket.id);
    console.log(socket.id);
    socket.end();
    socket.destroy();
    connectedSockets.delete(socket);
  });

  socket.on('close', function () {
      console.log('close, socket disconnected', socket.name);
      //removePairedUser(socket.id);
      socket.end();
      socket.destroy();
      connectedSockets.delete(socket);
  });

  socket.on('error', function (error) {
      console.log('User disconnected', error);
      socket.end();
      socket.destroy();
      connectedSockets.delete(socket);
  });
  
});




s.listen(8081, '192.168.1.100');