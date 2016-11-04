var express = require('express')
var app = express()

// Settings
app.enable('trust proxy')
app.disable('strict routing')
app.set('view engine', 'jade')

app.listen(3000)
