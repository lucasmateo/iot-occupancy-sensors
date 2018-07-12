http = require('http');
fs = require('fs');
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
        res.writeHead(200, {'Content-Type': 'text/html'});
        res.end('post received');
    }
    else
    {
        console.log("GET");
        res.end("OK");
    }

});

port = 9000;
host = '127.0.0.1';
server.listen(port, host);
console.log('Listening at http://' + host + ':' + port);
