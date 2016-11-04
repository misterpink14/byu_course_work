/*
Purpose of program: to compute the cost of owning a hybrid and non-hybrid car for 5 years
	to help the user decide which vehicle he or she will purchase. This program will ask
	the user to input information related to the calculations: the estimated miles driven per
	year, the estimated price of a gallon of gas, the cost of a hybrid car, the efficiency
	of the hybrid car in miles per gallon, the estimated resale value for a hybrid after 5
	years, the cost of a non-hybrid car, the efficiency of the non-hybrid car in miles per
	gallon, the estimated resale value for a non-hybrid after 5 years, and the users buying
	criteria, either "Gas" consumption or "Total" cost. After verifying that the information
	was entered in as positive numbers, the program will calculate, according to the user's
	criteria, which vehicle would better suit their needs. The outputted information will
	include the type of vehicle that fills their needs, the total gallons of fuel used in
	5 years, and the total cost of owning the vehicle for 5 years.
_________________________________________________________________________________________________

Test 1 -					miles	pricepg	costHy	mpgHy	resaleHy	costCar	mpgCar	resaleCar	criteria
		Input				10,000	2.5		30,000	60		10,000		17,000	25		6,000		Total
		Expected output		Non-hybrid	2000	16000					Hybrid	833.333	22083
		Acual Output		Non-hybrid	2000	13000					Hybrid	833.333	22083
		WRONG. Made corrections in code.
Test 2 -
		Input				2,000	3.5		25,000	65		15,000		22,000	22		10,000		Total
		Expected Output		Hybrid	153.846	10538					Non-hybrid	454.54	13590
		Actual Output		Non-hybrid	454.54	13590				Hybrid		153.846	10538
		WRONG. In reverse order, made corrections. 
Test 3 -
		Input				7,000	10		100,000	62		50,000		120,000	15		100,000		Gas
		Expected Output		Hybrid	564.516	55645						Non-Hybrid	2333	43333
		Actual Output		Hybrid	564.516	55645						Non-Hybrid	2333	433335

EXTRA CREDIT:
miles	pricepg	costHy	mpgHy	resaleHy	costCar	mpgCar	resaleCar	criteria
10000	2.5		32,000	?		24000		15,000	25		11,250		N/A

Attempts	100		200		180		175		170		160		165		168		
			High	Low		Low		Low		Low		High	High	Low		
166-167 MPG
*/

#include <iostream>
#include <string>

using namespace std;

int main()
{
	double miles, pricepg, costHy, mpgHy, resaleHy;						// User input
	double costCar, mpgCar, resaleCar;									// User input
	string criteria;													// User input
	string hy = "Hybrid";												// For output
	string car = "Non-Hybrid";											// For output
	double totalCostHy, totalCostCar, gallonsHy, gallonsCar;			// For program calculations
	
	/*----------------------------------------------------------|
	|					For user input							|
	|-----------------------------------------------------------*/
	cout << "Please input the following information:\n"
		<< "\nThe estimated miles driven per year\n";
	cin >> miles;
	if (miles <= 0)														// Verify that the input is positive 
	{
		cout << "\nPositve numbers are required, please try again";
		cin >> miles;
	}

	cout << "\nThe estimated price of a gallon of gas\n";
	cin >> pricepg;
	if (pricepg <= 0)													// Verify that the input is positive 
	{
		cout << "\nPositve numbers are required, please try again";
		cin >> pricepg;
	}

	cout << "\nThe cost of a hybrid car\n";
	cin >> costHy;
	if (costHy <= 0)													// Verify that the input is positive 
	{
		cout << "\nPositve numbers are required, please try again";
		cin >> costHy;
	}

	cout << "\nThe efficiency of the hybrid car in miles per gallon\n";
	cin >> mpgHy;
	if (mpgHy <= 0)														// Verify that the input is positive 
	{
		cout << "\nPositve numbers are required, please try again";
		cin >> mpgHy;
	}

	cout << "\nThe estimated resale value for a hybrid after 5 years\n";
	cin >> resaleHy;
	if (resaleHy <= 0)													// Verify that the input is positive 
	{
		cout << "\nPositve numbers are required, please try again";
		cin >> resaleHy;
	}

	cout << "\nThe cost of a non-hybrid car\n";
	cin >> costCar;
	if (costCar <= 0)													// Verify that the input is positive 
	{
		cout << "\nPositve numbers are required, please try again";
		cin >> costCar;
	}

	cout << "\nThe efficiency of the non-hybrid car in miles per gallon\n";
	cin >> mpgCar;
	if (mpgCar <= 0)													// Verify that the input is positive 
	{
		cout << "\nPositve numbers are required, please try again";
		cin >> mpgCar;
	}

	cout << "\nThe estimated resale value for a non-hybrid after 5 years\n";
	cin >> resaleCar;
	if (resaleCar <= 0)													// Verify that the input is positive 
	{
		cout << "\nPositve numbers are required, please try again";
		cin >> resaleCar;
	}

	cout << "\nYour buying criteria, either \"Gas\" consumption or \"Total\" cost(input Gas or Total)\n";
	cin >> criteria;

	/*-----------------------------------------------------------|
	|					Program Calculations					 |
	|-----------------------------------------------------------*/
	miles = miles * 5;													// Convert annual milage to 5 years
	gallonsHy = miles / mpgHy;											// Total gallons used in 5 years (Hybrid)
	totalCostHy = (gallonsHy * pricepg) + costHy - resaleHy;			// Total cost of Hybrid (owning the car for 5 years)

	gallonsCar = miles / mpgCar;										// Total gallons used in 5 years (Non-Hybrid)
	totalCostCar = (gallonsCar * pricepg) + costCar - resaleCar;		// Total cost of Non-Hybrid (owning the car for 5 years)

	/*-----------------------------------------------------------|
	|							Output							 |
	|-----------------------------------------------------------*/
	if ((criteria == "Gas") && (mpgHy > mpgCar))
	{
		cout << "\nThe " << hy << " would use " << gallonsHy << 
			" gallons of fuel in 5 years\nThe total cost of owning the " 
			<< hy << " for 5 years is $" << totalCostHy << endl;
		cout << "\nThe " << car << " would use " << gallonsCar << 
			" gallons of fuel in 5 years\nThe total cost of owning the " 
			<< car << " for 5 years is $" << totalCostCar << endl;
	}
	else if (totalCostCar > totalCostHy)
	{
		cout << "\nThe " << hy << " would use " << gallonsHy << 
			" gallons of fuel in 5 years\nThe total cost of owning the " 
			<< hy << " for 5 years is $" << totalCostHy << endl;
		cout << "\nThe " << car << " would use " << gallonsCar << 
			" gallons of fuel in 5 years\nThe total cost of owning the " 
			<< car << " for 5 years is $" << totalCostCar << endl;
	}
	else
	{
		cout << "\nThe " << car << " would use " << gallonsCar << 
			" gallons of fuel in 5 years\nThe total cost of owning the " 
			<< car << " for 5 years is $" << totalCostCar << endl;
		cout << "\nThe " << hy << " would use " << gallonsHy << 
			" gallons of fuel in 5 years\nThe total cost of owning the " 
			<< hy << " for 5 years is $" << totalCostHy << endl;
	}

	system("pause");
	return 0;
}