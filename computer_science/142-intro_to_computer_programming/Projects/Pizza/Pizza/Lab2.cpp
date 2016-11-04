/*
Test 1: 
After inputing 2 guests, I expect to see the program state that I need to order 0 large pizzas, 0 medium pizzas,
and 2 small pizzas. I also expect to see that the total area of pizza is 226.194 and the area of pizza each 
person can eat to be 113.097. After declaring a 15 percent tip, I expect to see the total cost as being $17.
Upon entering this information, I found that the total cost was only $16. Upon inspecting, I noticed that the
mistake I had made was adding 0.05 as opposed to 0.5 to the double to int conversion at the end of the code.

Test 2:
After inputing 305 guests, I expect to see the program state that I need to order 43 large pizzas, 1 medium pizza,
and 1 small pizza. I also expect to see that the total area of pizza is 13823 and the area of pizza each 
person can eat to be 45.3213. After declaring a 15 percent tip, I expect to see the total cost as being $780.
As anticipated, the program did show the correct information.

Test 3:
After inputing 48 guests, I expect to see the program state that I need to order 6 large pizzas, 2 medium pizzas,
and 0 small pizzas. I also expect to see that the total area of pizza is 2287.08 and the area of pizza each 
person can eat to be 47.6474. After declaring a 17 percent tip, I expect to see the total cost as being $130.
Once again, the program functioned properly.
*/

#include <iostream>

using namespace std;

int main()
{
	/*
		Part 1 - Count Your Many Pizzas
		Part 1 of the program will calculate the amount of small, medium, and large pizza's the user will need for his
		or her party. The user will input the amount of guests, and the program will display the approriate amount of 
		pizza for the amount of guests given.
	*/
	int lg_pizza = 7;													// A large pizza will feed 7 people
	int md_pizza = 3;													// A medium pizza will feed 3 people
	int sm_pizza = 1;													// A large pizza will feed person
	int remainder, guests, amt_lg, amt_md, amt_sm;						// Variables for calculating the amount of large, medium,
																		// and small pizzas to order for the party. 
	cout << "How many guests will be attending your event(ie.25)?\n";	// Requesting input from the user
	cin >> guests;														// The user inputs the amount of guests going to the party

	amt_lg = guests / lg_pizza;											// Calculate the amount of large pizza's
	remainder = guests % lg_pizza;										// Calculate the remainder, or unaccounted for students
	amt_md = remainder / md_pizza;										// Calculate the amount of medium pizza's
	remainder = remainder % md_pizza;									// Calculate the remainder again
	amt_sm = remainder / sm_pizza;										// Calculate the amount of small pizza's

	cout << "\nOrder " << amt_lg << " large pizza(s).\n"				// Display the amount of large, medium, and small pizzas
		<< "Order " << amt_md << " medium pizza(s).\n"					// needed for the party
		<< "Order " << amt_sm << " small pizza(s).\n\n";

	/*
		Part 2 - Serving Size
		Part 2 of the program will calculate the total area of pizza's the user will need to order, as well as the area each
		guest can eat. The area of a circle is calculated by the equation pi * r * r.
	*/
	double pi = 3.14159;												// Estimated value of pi, needed for math with circles
	double total_area;													// To store the total area of pizza for the party
	double area_per_person;												// To store the area of pizza each guest can eat
	int two = 2;														// Use to find the radius (diameter / 2)

	int lg_diameter = 20;												// The diameter of a large pizza is 20 inches
	int lg_radius = lg_diameter / two;									// The radius of a large pizza is 10 inches
	int md_diameter = 16;												// The diameter of a medium pizza is 16 inches
	int md_radius = md_diameter / two;									// The radius of a large pizza is 8 inches
	int sm_diameter = 12;												// The diameter of a small pizza is 12 inches
	int sm_radius = sm_diameter / two;									// The radius of a small pizza is 6 inches

	total_area = pi * (lg_radius * lg_radius * amt_lg +					// Calculate the total area of the pizza to be eaten
		md_radius * md_radius * amt_md +								// at the party
		sm_radius * sm_radius * amt_sm);

	area_per_person = total_area / guests;								// Calculate the area of the pizza that each guest can eat

	cout << "The total area of the pizza you will be ordering is "		// Display the total area of pizza for the party and the
		<< total_area << " square inches.\n" <<							// total area each guest can eat.
		"The area each person may eat is "	<< 
		area_per_person << " square inches.\n";

	/*
		Part 3 - Supplementing the Budget
		Part 3 of the program will calculate the total cost of the order from Jenga's Pizza. The user will be prompted to insert
		the tip percentage they would like to pay. With the given information, and the known price per pizza, the program will 
		calculate and display the total cost of the pizza, rounded to the nearest dollar.
	*/

	int tip;															// The tip percentage the user will input
	int percent = 100;													// For converting the input to a computable percentage
	double lg_cost = 14.68;												// A large pizza costs $14.68
	double md_cost = 11.48;												// A medium pizza costs $11.48
	double sm_cost = 7.28;												// A small pizza costs $7.28
	double round = 0.5;													// Needed to round to the nearest dollar amount
	
	double cost = (lg_cost * amt_lg) + (md_cost * amt_md)				// Calculate the total cost of the pizzas
		+ (sm_cost * amt_sm);											// not including the tip

	cout << "\n\nWhat tip percentage will you be leaving(0 to 100)?\n";		// Promp the user to input his/her tip percentage
	cin >> tip;															// Save users inputed percentage

	int total_cost = cost + ((cost * tip) / percent) + round;			// Calculate the total cost of the pizzas including tip

	cout << "\nThe total cost for your order, rounded to the "			// Output the total cost to the user
		<< "next dollar, will be $" << total_cost << endl;

	system("pause");
	return 0;
}