http = require('http');

server = http.createServer( function(req, res) {

    if (req.method == 'POST') {
        console.log("POST");
        var body = '';
        req.on('data', function (data) {
            body += data;
        });
        req.on('end', function () {
            console.log(body);
        });
        res.writeHead(200, {'Content-Length': 'post received'.length,'Content-Type': 'text/plain' });
        res.end('post received');
    }
    else
    {
        console.log("GET");
        id = {
          id: "tesst",
          status: "OK"
        }

        toSend = JSON.stringify(id);
        res.writeHead(200, {'Content-Length': toSend.length,'Content-Type': 'text/plain' });
        res.end(toSend);
    }

});
/*require('dns').lookup(require('os').hostname(), function (err, add, fam) {
  console.log('addr: '+add);
})
*/
port = 9000;
host = '9.233.65.174';
server.listen(port, host);
console.log('Listening at http://' + host + ':' + port);
