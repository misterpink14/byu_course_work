var express     =   require("express");
var app         =   express();
var bodyParser  =   require("body-parser");
var mongoOp     =   require("./models/mongo");
var router      =   express.Router();
var fs 			= 	require('fs');
var url 		= 	require('url');

var ROOT_DIR	=	"./html/";

app.use(bodyParser.json());
app.use(bodyParser.urlencoded({"extended" : false}));

router.get("/",function(req,res){
	var urlObj = url.parse(req.url, true, false);
    fs.readFile(ROOT_DIR + 'index.html', function (err,data) {
			
			if (err) { // Error occured
			  res.writeHead(404);
			  res.end(JSON.stringify(err));
			  return;
			}
			res.writeHead(200);
			res.end(data);
		});
});

router.get("/script.js",function(req,res){
	var urlObj = url.parse(req.url, true, false);
    fs.readFile(ROOT_DIR + 'script.js', function (err,data) {
			
			if (err) { // Error occured
			  res.writeHead(404);
			  res.end(JSON.stringify(err));
			  return;
			}
			res.writeHead(200);
			res.end(data);
		});
});

//route() will allow you to use same path for different HTTP operation.
//So if you have same URL but with different HTTP OP such as POST,GET etc
//Then use route() to remove redundant code.

router.route("/users")
	// GET
    .get(function(req,res){
        var response = {};
        mongoOp.find({},function(err,data){
        // Mongo command to fetch all data from collection.
            if(err) {
                response = {"error" : true,"message" : "Error fetching data"};
            } else {
                response = {"error" : false,"message" : data};
            }
            res.json(response);
        });
    })

    // POST
    .post(function(req,res){

    	console.log(req)

        var db = new mongoOp();
        var response = {};
        // fetch email and password from REST request.
        // Add strict validation when you use this in Production.
        db.userEmail = req.body.email; 
        // Hash the password using SHA1 algorithm.
        db.userPassword =  require('crypto')
                          .createHash('sha1')
                          .update(req.body.password)
                          .digest('base64');
        db.save(function(err){
        // save() will run insert() command of MongoDB.
        // it will add new data in collection.
            if(err) {
                response = {"error" : true,"message" : "Error adding data"};
            } else {
                response = {"error" : false,"message" : "Data added"};
            }
            res.json(response);
        });
    });

    router.route("/users/:email")
    .get(function(req,res){
        var response = {};
        mongoOp.find({'userEmail' :req.params.email},function(err,data){
        // This will run Mongo Query to fetch data based on ID.
            if(err) {
                response = {"error" : true,"message" : "Error fetching data"};
            } else {
                response = {"error" : false,"message" : data};
            }
            res.json(response);
        });
    })

    router.route("/users/:id")
    .get(function(req,res){
        var response = {};
        mongoOp.findById(req.params.id,function(err,data){
        // This will run Mongo Query to fetch data based on ID.
            if(err) {
                response = {"error" : true,"message" : "Error fetching data"};
            } else {
                response = {"error" : false,"message" : data};
            }
            res.json(response);
        });
    })
    .put(function(req,res){
        var response = {};
        // first find out record exists or not
        // if it does then update the record
        console.log(req)
	mongoOp.findById(req.params.id,function(err,data){
            if(err) {
                response = {"error" : true,"message" : "Error fetching data"};
            } else {
            // we got data from Mongo.
            // change it accordingly.
                if(req.body.userEmail !== undefined) {
                    // case where email needs to be updated.
                    data.userEmail = req.body.userEmail;
                }
                if(req.body.userPassword !== undefined) {
                    // case where password needs to be updated
                    data.userPassword = req.body.userPassword;
                }
		if(req.body.userInfo !== undefined) {
			data.userInfo = req.body.userInfo;
		}
                // save the data
                data.save(function(err){
                    if(err) {
                        response = {"error" : true,"message" : "Error updating data"};
                    } else {
                        response = {"error" : false,"message" : "Data is updated for "+req.params.id};
                    }
                    res.json(response);
                })
            }
        });
    })
    .delete(function(req,res){
        var response = {};
        // find the data
        mongoOp.findById(req.params.id,function(err,data){
            if(err) {
                response = {"error" : true,"message" : "Error fetching data"};
            } else {
                // data exists, remove it.
                mongoOp.remove({_id : req.params.id},function(err){
                    if(err) {
                        response = {"error" : true,"message" : "Error deleting data"};
                    } else {
                        response = {"error" : true,"message" : "Data associated with "+req.params.id+"is deleted"};
                    }
                    res.json(response);
                });
            }
        });
    })

app.use('/',router);

app.listen(3000);
console.log("Listening to PORT 3000");
