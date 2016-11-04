var red = ["red", true, "Times New Roman"];
var green = ["green", false, ""];
var blue = ["blue", true, "Arial"];
var black = ["black", false, "", true, "Hello there"];

var text_id = "target";


var text = {
	"red" : red,
	"green" : green,
	"blue" : blue,
	"black" : black,
}


function setText (tag_id) {
	var font_style = text[tag_id];
	document.getElementById(text_id).style.color = font_style[0];
	
	if (font_style[1]) {
		document.getElementById(text_id).style.fontFamily = font_style[2];
	}
	if (font_style[3])
	{
		document.getElementById(text_id).innerHTML = font_style[4];
	}
	// console.log('success');
}