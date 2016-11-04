var fs = require('fs');
var http = require('http');
var url = require('url');
var ROOT_DIR = "html/";
var cities_dat = 'cities.dat.txt'

http.createServer(function (req, res) {
	var urlObj = url.parse(req.url, true, false);
	
	if (urlObj.pathname == '/getcity') { // REST server
		console.log("here")
		fs.readFile(ROOT_DIR + cities_dat, function(err, data) {
			
			if (err) { // ERROR occured
				res.writeHead(200)
				res.end(JSON.stringify(err))
				return
			} else {
				var arr_data = data.toString().split('\n')
				var r = new RegExp('^'+urlObj.query['q'])
				var filtered = (arr_data.filter(function(o) {
					
					if (o.search(r) != -1)
						return true
					return false
				}))
				console.log(JSON.stringify(filtered))
				res.writeHead(200)
				res.end(JSON.stringify(filtered))
			}
		})
	} else { // Static pages
		fs.readFile(ROOT_DIR + urlObj.pathname, function (err,data) {
			
			if (err) { // Error occured
			  res.writeHead(404);
			  res.end(JSON.stringify(err));
			  return;
			}
			res.writeHead(200);
			res.end(data);
		});
	}
}).listen(3000);

