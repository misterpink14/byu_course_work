#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

/**
	default assigns the all the addresses of the array to the specified value, which
	is in this case 0. There is no return value, because the array is a reference point.
	@param temps[][]	the array being addressed
	@param value		the value being passed into the required positions in the array
	@param rows			the number of rows in the array
	@param columns		the number of columns in the array
*/

void default_temp(double temps[][20], int value, int rows, int columns)
{
	for(int j = 0; j < columns; j++)
	{
	for(int i = 0; i < rows; i++)
	{
		temps[i][j] = value;
	}
	}
	
}

/**
	top_bottom assigns the first and last row, not including the first and last column of 
	the array to the specified value, which is in this case 100. There is no return value, 
	because the array is a reference point.
	@param temps[][]	the array being addressed
	@param value		the value being passed into the required positions in the array
	@param rows			the number of rows in the array
	@param columns		the number of columns in the array
*/

void top_bottom(double temps[][20], int value, int rows, int columns)
{
	const int FIRSTROW = 0;
	const int LASTROW = 19;
	int row_position = FIRSTROW;
	for(int j = 0; j < 2; j++)
	{
	for(int i = 1; i < (columns-1); i++)
	{
		temps[row_position][i] = value;
	}
	row_position = LASTROW;
	}
	
}

/**
	ss_avg is used to find the area of the four surrounding elements of an array, top,
	bottom, right, left.
	@param temps	the array being addressed
	@param j		the row of the element
	@param i		the column of the element
*/

double ss_avg(double temps[][20], int j, int i)
{
	double avg = 0;
	avg = (temps[(j+1)][(i+1)] + temps[(j+1)][(i-1)] + temps[(j-1)][(i+1)]
			+ temps[(j-1)][(i-1)]) / 4;
	return avg;
}

/**
	steady_state finds the steady-state temperature distribution of the interior element
	@param temps	the array being addressed
	@param rows		the number of rows in the array
	@param columns	the number of columns in the array
*/

void steady_state(double temps[][20], int rows, int columns)
{
	for(int j = 1; j < (rows - 1); j++)
	{
	for(int i = 1; i < (columns-1); i++)
	{
		temps[j][i] = ss_avg(temps, j, i);
	}
	}
}

/**
	avg_all returns the average of the total of all the elements in the array,
	aside from the outside values.
	@param temps	the array being addressed
	@param rows		the amount of rows in the array
	@param columns	the amount of columns in the array
*/
double avg_all(double temps[][20], int rows, int columns)
{
	double total = 0;
	for(int j = 1; j < (rows - 1); j++)
	{
	for(int i = 1; i < (columns -1); i++)
		{
			total = total + temps[j][i];
		}
	}
	total = total / 400.0;
	return total;
}

/**
	Main Function finds the steady state of a 20 by 20 array where the top and
	bottom rows, not including the first and last column, are equal to 100 and
	all other values are set to 0 initially.
*/
int main ()
{
	const int ROWS = 20;
	const int COLUMNS = 20;
	const int TOPBOTTOM = 100;
	const int DEFAULT = 0;
	double temps[ROWS][COLUMNS];
	default_temp(temps, DEFAULT, ROWS, COLUMNS);
	top_bottom(temps, TOPBOTTOM, ROWS, COLUMNS);
	for(int j = 0; j < ROWS; j++)						// output the formatted array
	{
		for(int i = 0; i < COLUMNS	; i++)
		{
			cout << setw(4) << temps[j][i];
		}
		cout << endl;
	}
	
	double newnum = 0;
	double oldnum = 0;
	do													// store the final array in a file
	{
		
		oldnum = avg_all(temps, ROWS, COLUMNS);
		steady_state(temps, ROWS, COLUMNS);
		newnum = avg_all(temps, ROWS, COLUMNS);
	}
	while(0.1 < (newnum - oldnum));
	ofstream myfile;
	myfile.open ("example.csv");
	for(int j = 0; j < ROWS; j++)
	{
		for(int i = 0; i < COLUMNS	; i++)
		{
			myfile << fixed << setprecision(1) << temps[j][i] << ",";
		}
		myfile << endl;
	}
	
	system("pause");
	return 0;
}