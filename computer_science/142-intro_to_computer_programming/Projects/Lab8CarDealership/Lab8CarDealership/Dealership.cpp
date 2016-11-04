/*******************************************************************
	TEST CASES
	Test1: 
		Buy a car named Grey
		Worked, price added
	Test2:
		Sell the car names Grey
		Worked, price deleted
	Test 3:
		Load a file and view it
		Works

BENJAMIN THOMPSON
Section 2
*******************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "Car.h"
#include <fstream>

using namespace std;

// Menu options
const int QUIT = 0;
const int INV = 1;
const int BAL = 2;
const int BUY = 3;
const int SELL = 4;
const int PAINT = 5;
const int LOAD = 6;
const int SAVE = 7;

/****************************************************************
	The menu functions acts as the main menu for the program
	@return input	The user's selection from the menu
****************************************************************/
int menu()
{
	int input;
	do
	{
	cout << "1 - Show Current Inventory\n" << 
		"2 - Show Current Balance\n" <<
		"3 - Buy a Car\n" << 
		"4 - Sell a Car\n" << 
		"5 - Paint a Car\n" << 
		"6 - Load File\n" <<
		"7 - Save File\n" << 
		"0 - Quit Program\n";
	cin >> input;
	cin.sync();
	cin.clear();
	}
	while(cin.fail());
	return input;
}

void inventory(vector<Car> &vehicles)
{
	cout << "\n\n" << setw(15) << left << "NAME:" << "|" <<
		setw(15) << left << "COLOR:" << "|" << 
		"Price" << "\n";
	// list all vehicles
	for(int i = 0; i < vehicles.size(); i++){
		cout << setw(15) << left << vehicles[i].getName() << "|" <<
			setw(15) << left << vehicles[i].getColor() << "|" << "$" <<
			setprecision(2) << fixed << vehicles[i].getPrice() << "\n";
	}
}

void currentBalance(double *balance)
{
	cout << "\n\n" << setprecision(2) << fixed << "$" << *balance << "\n\n";
	return;
}

bool inInv(vector<Car> & vehicles, string name)
{
	for(int i = 0; i < vehicles.size(); i++){
		if(name == vehicles[i].getName()){
			cout << "\n\nThis car is already in your inventory.\n\n";
			return true;
		}
	}
	return false;
}

void buy(vector<Car> &vehicles, double *balance)
{
	string name;
	string color;
	double price;
	bool notokay = false;

	// Do not allow a duplicate car
	cout << "\nPlease enter the name of the car that you wish to buy:\n";
	getline(cin, name);
	notokay = inInv(vehicles, name);
	if(notokay == true)
		return;

	// color
	cout << "\nPlease enter the color of the car:\n";
	getline(cin, color);

	// Do not buy anything that worth more than is available
	cout << "\n\nPlease enter the price of the car:\n";
	cin >> price;
	if(price > *balance){
		cout << "\nThe price of this car exceeds your balance.\n\n";
		return;
	}

	// subtract price of car & add car
	*balance -= price;
	vehicles.push_back(Car(name, color, price));
	cout << "\nCar sucessfully added to inventory!\n\n";

	return;
}

int findCar(vector<Car> vehicles, string name)
{
	for(int i = 0; i < vehicles.size(); i++)
	{
		if (name == (vehicles[i].getName())){
			return i;
			cout << "l";
		}
	}
	// to show the car is not in the inventory
	return (vehicles.size()+1);
}

void remove(vector<Car> &vehicles, int carLoc)
{
	vehicles[carLoc] = vehicles[(vehicles.size() - 1)];
	vehicles.pop_back();
}

void sell(vector<Car> &vehicles, double *balance)
{
	string name;					// Name of car
	const int NOCAR = 0;
	int carLoc;						// Location of car to remove

	if(vehicles.size() == NOCAR)
	{
		cout << "\n\nYou have no vehicles.\n\n";
		return;
	}
	
	// get the name of the car the user wishes to sell
	cout << "\n\nPlease enter the name of the car you wish to sell:";
	getline(cin, name);

	// if the car is not in the inventory, let the user know and exit
	carLoc = findCar(vehicles, name);
	if(findCar(vehicles, name) == (vehicles.size() + 1)){
		cout << "\n\nThere is not a car by that name in your inventory.\n\n";
		return;
	}

	// add price to balance
	*balance += vehicles[carLoc].getPrice();

	// remove vehicle
	remove(vehicles, carLoc);

	cout << "\n\nYour vehicle has been removed from the inventory!\n\n";

	return;
}

void paint(vector<Car> &vehicles)
{
	int carLoc;					// location of car to paint
	const int NOCAR = 0;
	string input;				// To store car name and paint color

	if(vehicles.size() == NOCAR)
	{
		cout << "\n\nYou have no vehicles.\n\n";
		return;
	}
	cout << "\n\nEnter the name of the car you wish to paint: \n";
	getline(cin, input);

	// if the car is not in the inventory, let the user know and exit
	carLoc = findCar(vehicles, input);
	if(findCar(vehicles, input) == (vehicles.size() + 1)){
		cout << "\n\nThere is not a car by that name in your inventory.\n\n";
		return;
	}

	// get color
	cout << "\nEnter the color that you wish to paint the car with: \n";
	getline(cin,input);

	// paint and add $1000 to value
	vehicles[carLoc].paint(input);
	cout << "\nYour new paint job has been added processed!\n\n";
	
	return;
}

void load(vector<Car> &vehicles, double *balance)
{
	string name, color, filename;
	double price, bal;

	cout << "\n\nEnter the filename you wish to load: ";
	cin >> filename;

	ifstream file;
	file.open(filename.c_str());

	file >> bal;
	*balance += bal;
	while(!file.eof())
	{
		file >> name >> color >> price;
		vehicles.push_back(Car(name, color, price));
	}

	file.close(); 
	
	cout << "\n\nFile loaded!\n\n";
	return;
}



void save(vector<Car> &vehicles, double *balance)
{
	ofstream file;
	string filename;
	cout << "Enter the filename you wish to save under: ";
	cin >> filename;
	file.open(filename.c_str());
	
	file << *balance << endl;
	for(int i = 0; i < vehicles.size(); i++)
	{
		file << vehicles[i].getName() << " " << vehicles[i].getColor() << " "
			<< vehicles[i].getPrice() << endl;
	}

	file.close(); 

	cout << "\n\nFile saved!\n\n";
	return;
}

/****************************************
	The main function of the program
****************************************/
int main()
{
	int option;
	double balance = 10000;
	vector<Car> vehicles;
	for(;;)
	{
		// menu for program
		option = menu();

		if(option == QUIT)
			break;
		else if(option == INV){
			inventory(vehicles);
		}
		else if(option == BAL){
			currentBalance(&balance);
		}
		else if(option == BUY){
			buy(vehicles, &balance);
		}
		else if(option == SELL){
			sell(vehicles, &balance);
		}
		else if(option == PAINT){
			paint(vehicles);
		}
		else if(option == LOAD){
			load(vehicles, &balance);
		}
		else if(option == SAVE){
			save(vehicles, &balance);
		}
	}

	system("pause");
	return 0;
}