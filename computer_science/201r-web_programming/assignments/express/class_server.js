var express = require('express');
var bodyParser = require('body-parser');
var https = require('https');
var http = require('http');
var fs = require('fs');
var url = require('url');
var app = express();
var ROOT_DIR = "html/";
var cities_dat = 'cities.dat.txt'

app.use(bodyParser());

var options = {
    host: '127.0.0.1',
    key: fs.readFileSync('ssl/server.key'),
    cert: fs.readFileSync('ssl/server.crt')
};


  http.createServer(app).listen(80);
  https.createServer(options, app).listen(443);


  app.use('/', express.static('./html', {maxAge: 60*60*1000}))
  

  app.get('/getcity', function (req, res) {
    console.log("In getcity route");
    fs.readFile(ROOT_DIR + cities_dat, function(err, data) {
      var arr_data = data.toString().split('\n')
      var r = new RegExp('^'+req.query['q'])
      var filtered = (arr_data.filter(function(o) {

        if (o.search(r) != -1)
          return true
        return false
      }))
      console.log(JSON.stringify(filtered))
      //res.writeHead(200)
      res.json(filtered)
      //res.json([{city:"Price"},{city:"Provo"}]);
    })
  })


  app.get('/comment', function (req, res) {
    console.log("In comment route");
  })


  app.post('/comment', function (req, res) {
    console.log("In POST comment route");
    console.log(req.body);
    res.status(200);
    res.end();
  })


