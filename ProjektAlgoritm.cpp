#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// Create a struct with variables for temperature, humidity, day, in eller out
struct Data
{
	double temp;
	double mold;
	int hum;	
	string day;
	string inOut;
	Data() : temp(0), hum(0), day("0"), inOut("0"), mold(0) {}	// Puts varible value at 0 
};

void winter(vector <Data>& dv, int n)			// Function for calculating and printing out the first date for meterological winter
{
	bool foundWinter = false;			// Sets variable to false

	for (int i = 0; i < n; i++)
	{
		if (dv[i].temp <= 0 && dv[i + 1].temp <= 0 && dv[i + 2].temp <= 0 && dv[i + 3].temp <= 0 && dv[i + 4].temp <= 0)	// if one day's average temperature is 0 and the following 4 days aswell
		{																													// The variable foundwinter turns true and the program prints out the first day where the if statement is true

			foundWinter = true;
			cout << dv[i].day << endl;
			break;
		}
	}
	if (foundWinter == false)			// If the statement above never happens, the variable foundWinter won't change and therefore this if statement will be true, prints out "No Winter"
	{
		cout << "No Winter";

	}
}
void fall(vector <Data>& dv, int n)	   // Function for calculating and printing out the first date for meterological fall
{
	for (int i = 0; i < n; i++)
	{
		if (dv[i].temp >= 0 && dv[i].temp <= 10 && dv[i + 1].temp <= 10 && dv[i + 2].temp <= 10 && dv[i + 3].temp <= 10 && dv[i + 4].temp <= 10)	// The first element it encounters that has a temperature between 0-10 degrees
																																					// and the subsequent 4 elements are below 10 degrees
		{
			if (dv[i].temp >= dv[i + 1].temp && dv[i + 1].temp >= dv[i + 2].temp && dv[i + 2].temp >= dv[i + 3].temp && dv[i + 3].temp >= dv[i + 4].temp)	// Also if the temperature the next day goes down from the previous day the 4 coming days
			{
				cout << dv[i].day << endl;				// print out the day where both these statements are true
				break;
			}
		}
	}
}


void mold(vector <Data>& dv, int n)			//Function to calculate mold risk
{

	double humLimit = 78;			// Set value of humLimit to 78
	for (int i = 0; i < n; i++)
	{
		if (dv[i].temp >= 15 && dv[i].temp < 50 && dv[i].hum >= humLimit)	// If temperature is between 15 and 50 and humidity is exactly or above 78
		{
			dv[i].mold = (dv[i].hum - humLimit) / 0.22;					// Subtract 78 which is the humidity limit from the humidity of the day where the above if statement is true
																			// Then divide that number by 0.22 to get a value on a 100 grade scale 
		}
		else if (dv[i].temp >= 0 && dv[i].temp < 15 && dv[i].hum >= humLimit)	// If the temperature is between 0 and 15 degrees and humidity is exactly or above 78
		{
			dv[i].mold = ((dv[i].hum - humLimit) * (dv[i].temp / 15)) / 0.22;	// Subtract humLimit from the humidity again and then multiply that by temperature divided by 15 which is the temperature limit
																				// After that, divide the result by 0.22 
		}

		else {		// If none of the statements are true, the mold risk is 0% 

			dv[i].mold = 0;

		}
	}

}

void swap(Data* xp, Data* yp)				// Swap function to use for bubblesort
{
	Data tempo = *xp;
	*xp = *yp;
	*yp = tempo;
}
// A function to implement bubble sort for temperature 

void bubbleSortTemp(vector <Data>& dv, int n)
{
	int i;
	for (i = 0; i < n - 1; i++)					// Start with a for loop to include all the 130 days in the list
	{

			
		for (int j = 0; j < n - i - 1; j++)		// Goes through all unsorted values because the following values are already sorted.
		{
			if (dv[j].temp > dv[j + 1].temp)		
			{
				swap(&dv[j], &dv[j + 1]);	
			}
		}
	}
}

void bubbleSortFukt(vector <Data>& dv, int n)
{
	int i;
	for (i = 0; i < n - 1; i++)
	{

		// Last i elements are already in place  
		for (int j = 0; j < n - i - 1; j++)
		{
			if (dv[j].hum > dv[j + 1].hum)
			{
				swap(&dv[j], &dv[j + 1]);
			}
		}
	}
}

void bubbleSortMold(vector <Data>& dv, int n)
{
	int i;
	for (i = 0; i < n - 1; i++)
	{

		// Last i elements are already in place  
		for (int j = 0; j < n - i - 1; j++)
		{
			if (dv[j].mold > dv[j + 1].mold)
			{
				swap(&dv[j], &dv[j + 1]);
			}
		}
	}
}


// Function to print vector
void printVectorTemp(vector <Data> dv, int n)
{

	int i;
	for (i = n - 1; i > n - 6; i--)
		cout << dv[i].day << " " << dv[i].temp << " " << dv[i].inOut << " " << endl;

}
void printVectorFukt(vector <Data> dv, int n)
{

	int i;
	for (i = 0; i < 5; i++)
		cout << dv[i].day << " " << dv[i].hum << " " << dv[i].inOut << " " << endl;

}
void printVectorMold(vector <Data> dv, int n)
{

	int i;
	for (i = 0; i < n; i++)
		cout << dv[i].day << " \t Temperature:  " << dv[i].temp << " \t Humidity:  " << dv[i].hum << " \t Mold index: " << dv[i].mold << endl;

}



int main()
{

	string day, time, inOut, temperature, humidity;       


	ifstream file("tempdata4.txt");              //Read in textfile
	if (file.is_open())                      // If the file can be opened, do this
	{


		string currentDate = " ";			// Sätter värdet av currentDate till 0
		string checkDate = " ";				// Sätter värdet av checkDate till 0


		long int inCount = 1;				// Sätter värdet av inCount till 0
		long int outCount = 0;				// Sätter värdet av outCount till 0
		long int count = 0;					 // Sätter värdet av count till 0

		vector <Data> dvIn;				// Create a vector for all values I want indoors
		vector <Data> dvOut;			// Create a vector for all values I want outdoors

		Data i;						// Declare variables for in and out
		Data u;



		while (!file.eof())				// Run this until the end of the file
		{

			getline(file, day, ' ');		// Get values from file and set the values to variables
			getline(file, time, ',');
			getline(file, inOut, ',');
			getline(file, temperature, ',');
			getline(file, humidity);

			if (day == checkDate)				// If day = Checkdate which is now 0
			{
				if (inOut == "Inne")			// If it says "Inne" in the inOut field in the file
				{

					i.temp += stod(temperature);	// Sum of all temperatures, convert string temperature to double.
					i.hum += stod(humidity);		// Sum of all humidity, convert string humidity to double.
					inCount++;						// Start counter for inside.

				}
				else if (inOut == "Ute")		// Do the same for all outside values and save them in the u variable.
				{


					u.temp += stod(temperature);
					u.hum += stod(humidity);								
					outCount++;

				}

				currentDate = day;
				count++;
			}

			else
			{
				checkDate = day;

				if (count != 0)
				{

					i.temp = round((i.temp / inCount) * 10) / 10;		// Calculating average temperature of all values indoors
					i.hum = round((i.hum / inCount) * 10) / 10;			// Calculating average temperature of all values outdoors

					i.day = currentDate;
					i.inOut = "Inne";

					dvIn.push_back(i);									// Push all values into the dvIn vector

					u.temp = round((u.temp / outCount) * 10) / 10;		// Calculating average temperature of all values outdoors
					u.hum = round((u.hum / outCount) * 10) / 10;		// Calculating average humidity of all values outdoors
					u.day = currentDate;
					u.inOut = "Ute";


					dvOut.push_back(u);				// Push all values into the dvOut vector

					inCount = 0;			// Set all values to 0 after each day
					outCount = 0;
					checkDate = day;
					u.temp = 0;
					i.temp = 0;





				}
			}

		}

		int n = dvIn.size();
		char selection;
		int select;
		string search;

		// Create a menu using switch: case, call the appropriate function for every choice.

			cout << "\n Menu";

			cout << "\n========";

			cout << "\n 1 - Search for date";

			cout << "\n 2 - Average Temp, 5 max values";

			cout << "\n 3 - Average Humidity, 5 min values";

			cout << "\n 4 - Lowest to highest chance of mold";

			cout << "\n 5 - Meteorological Winter and Fall dates";

			cout << "\n Enter selection: ";



			cin >> selection;

			switch (selection)

			{

			case '1':
			{
				system("CLS");

				cout << "\n 1- Inne ";
				cout << "\n 2 - Ute ";
				cin >> select;
				if (select == 1)
				{
					cout << "\n Search for Date in this format: YYYY-MM-DD ";
					cin >> search;
					for (int i = 0; i < n; i++)
					{
						if (dvIn[i].day == search)
						{
							cout << dvIn[i].day << " " << dvIn[i].temp << "  " << dvIn[i].inOut << endl;
						}
					}
				}
				else if (select == 2)
				{
					cout << "\n Search for Date in this format: YYYY-MM-DD ";
					cin >> search;
					for (int i = 0; i < n; i++)
					{
						if (dvOut[i].day == search)
						{
							cout << dvOut[i].day << " " << dvOut[i].temp << " " << dvOut[i].inOut << endl;
						}
					}
				}

				break;
			case '2': {system("CLS");

				cout << "\n 1 - Inside ";
				cout << "\n 2 - Outside "; }
					cin >> select;

					if (select == 1)
					{
						system("CLS");
						bubbleSortTemp(dvIn, n);
						printVectorTemp(dvIn, n);
					}
					else if (select == 2)
					{
						system("CLS");
						bubbleSortTemp(dvOut, n);
						printVectorTemp(dvOut, n);
					}
					break;

			case '3': {system("CLS");

				cout << "\n 1 - Inside ";
				cout << "\n 2 - Outside "; }

					cin >> select;

					if (select == 1)
					{
						system("CLS");
						bubbleSortFukt(dvIn, n);
						printVectorFukt(dvIn, n);
					}
					else if (select == 2)
					{
						system("CLS");
						bubbleSortFukt(dvOut, n);
						printVectorFukt(dvOut, n);
					}
					break;

			case '4': {system("CLS");

				cout << "\n 1 - Inside ";
				cout << "\n 2 - Outside "; }

					cin >> select;

					if (select == 1)
					{
						system("CLS");
						mold(dvIn, n);
						bubbleSortMold(dvIn, n);
						printVectorMold(dvIn, n);
					}
					else if (select == 2)
					{
						system("CLS");
						mold(dvOut, n);
						bubbleSortMold(dvOut, n);
						printVectorMold(dvOut, n);

					}
					break;

			case '5': {

				cout << "\n 1 - Winter ";
				cout << "\n 2 - Fall "; }

					cin >> select;

					if (select == 1)
					{
						system("CLS");
						winter(dvOut, n);
					}
					else if (select == 2)
					{
						system("CLS");
						fall(dvOut, n);

					}

					break;
			}
			default: cout << "\n Invalid selection";

				break;
			}


			cout << "\n";

			string y;
			getline(cin, y);
			return 0;
		}
	
}
