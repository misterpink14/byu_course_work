var num = 1;



function addToFizzBuzz (val) {
	var element = document.getElementById("fizz-buzz");
	var output = "";
	var isFizzBuzz = false;

	if (!(val % 3)) {
		output += "Fizz";
		isFizzBuzz = true;
	}
	if (!(num % 5)) {
		output += "Buzz";
		isFizzBuzz = true;
	}

	if (!isFizzBuzz) {
		output += val;
	}

	if (val !== 1) {
		output = ", " + output;
	} 
	element.innerHTML += output;
};


var clickEvent = function(e) {
	addToFizzBuzz(num);
	num++;
}

document.getElementById("fizz-buzz-btn").addEventListener("click", clickEvent);


