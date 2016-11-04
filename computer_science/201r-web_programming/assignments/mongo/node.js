var fs = require('fs');
var http = require('http');
var url = require('url');
var readline = require('readline');
var ROOT_DIR = "src/html/";
http.createServer(function (req, res) {
  console.log("made it!");
  var urlObj = url.parse(req.url, true, false);
  // If this is our comments REST service
  if(urlObj.pathname.indexOf("comment") !=-1) {
    console.log("comment route");
    if(req.method === "POST") {
      var jsonData = "";
      req.on('data', function (chunk) {
        jsonData += chunk;
      });
      req.on('end', function () {
        var reqObj = JSON.parse(jsonData);
        console.log(reqObj);
        console.log("Name: "+reqObj.Name);
        console.log("Comment: "+reqObj.Comment);
        var MongoClient = require('mongodb').MongoClient;
        MongoClient.connect("mongodb://localhost/weather", function(err, db) {
          if(err) throw err;
          db.collection('comments').insert(reqObj,function(err, records) {
            console.log("Record added as "+records[0]._id);
          });
        });
        res.writeHead(200);
        res.end("");
      });

      var basicAuth = require('basic-auth-connect');
      var auth = basicAuth(function(user, pass) {
        return((user ==='cs201r')&&(pass === 'test'));
      });
      app.post('/comment', auth, function (req, res) {
      console.log("In POST comment route");
      console.log(req.user);
      console.log("Remote User");
      console.log(req.remoteUser);
      res.status(200);
      res.end();
    });
    
      console.log("POST comment route");
    } else if(req.method === "GET") {
      console.log("In GET"); 
      var MongoClient = require('mongodb').MongoClient;
      MongoClient.connect("mongodb://localhost/weather", function(err, db) {
        if(err) throw err;
        db.collection("comments", function(err, comments){
          if(err) throw err;
          comments.find(function(err, items){
            items.toArray(function(err, itemArr){
              console.log("Document Array: ");
              console.log(itemArr);
              res.writeHead(200);
              res.end(JSON.stringify(itemArr));
            });
          });
        });
      });
    }
  } else {
   // Normal static file
    fs.readFile(ROOT_DIR + urlObj.pathname, function (err,data) {
      if (err) {
        res.writeHead(404);
        res.end(JSON.stringify(err));
        return;
      }
      res.writeHead(200);
      res.end(data);
    });
  }
}).listen(3000);
