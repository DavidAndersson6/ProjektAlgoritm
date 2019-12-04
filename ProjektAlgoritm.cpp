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
	int fukt;
	string dag;
	string inUt;
	Data() : temp(0), fukt(0), dag("0"), inUt("0"), mold(0) {}	// Puts varible value at 0 
};

void winter(vector <Data>& dv, int n)			// Function for calculating and printing out the first date for meterological winter
{
	bool foundWinter = false;			// Sets variable to false

	for (int i = 0; i < n; i++)
	{
		if (dv[i].temp <= 0 && dv[i + 1].temp <= 0 && dv[i + 2].temp <= 0 && dv[i + 3].temp <= 0 && dv[i + 4].temp <= 0)	// if one day's average temperature is 0 and the following 4 days aswell
		{																													// The variable foundwinter turns true and the program prints out the first day where the if statement is true

			foundWinter = true;
			cout << dv[i].dag << endl;
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
				cout << dv[i].dag << endl;				// print out the day where both these statements are true
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
		if (dv[i].temp >= 15 && dv[i].temp < 50 && dv[i].fukt >= humLimit)	// If temperature is between 15 and 50 and humidity is exactly or above 78
		{
			dv[i].mold = (dv[i].fukt - humLimit) / 0.22;					// Subtract 78 which is the humidity limit from the humidity of the day where the above if statement is true
																			// Then divide that number by 0.22 to get a value on a 100 grade scale 
		}
		else if (dv[i].temp >= 0 && dv[i].temp < 15 && dv[i].fukt >= humLimit)	// If the temperature is between 0 and 15 degrees and humidity is exactly or above 78
		{
			dv[i].mold = ((dv[i].fukt - humLimit) * (dv[i].temp / 15)) / 0.22;	// Subtract humLimit from the humidity again and then multiply that by temperature divided by 15 which is the temperature limit
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

			// Last i elements are already in place  
		for (int j = 0; j < n - i - 1; j++)
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
			if (dv[j].fukt > dv[j + 1].fukt)
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
		cout << dv[i].dag << " " << dv[i].temp << " " << dv[i].inUt << " " << endl;

}
void printVectorFukt(vector <Data> dv, int n)
{

	int i;
	for (i = 0; i < 5; i++)
		cout << dv[i].dag << " " << dv[i].fukt << " " << dv[i].inUt << " " << endl;

}
void printVectorMold(vector <Data> dv, int n)
{

	int i;
	for (i = 0; i < n; i++)
		cout << dv[i].dag << " \t Temperature:  " << dv[i].temp << " \t Humidity:  " << dv[i].fukt << " \t Mold index: " << dv[i].mold << endl;

}



int main()
{

	string day, time, inOut, temperature, humidity;       // Deklarerar variabler


	ifstream file("tempdata4.txt");              // Läser in textfilen
	if (file.is_open())                      // Om det går att öpnna filen
	{


		string currentDate = " ";			// Sätter värdet av currentDate till 0
		string checkDate = " ";				// Sätter värdet av checkDate till 0


		long int inCount = 1;				// Sätter värdet av inCount till 0
		long int outCount = 0;				// Sätter värdet av outCount till 0
		long int count = 0;					 // Sätter värdet av count till 0

		vector <Data> dvIn;				// skapa en vector för alla värden jag vill ha utomhus
		vector <Data> dvOut;			// skapa en vector för alla värden jag vill ha inomhus

		Data i;						// Deklarera variabler för inne och ute i min vector
		Data u;



		while (!file.eof())				// Kör detta medans filen inte är slut
		{

			getline(file, day, ' ');		// Läser in värden av datum etc från textfilen in i variabler
			getline(file, time, ',');
			getline(file, inOut, ',');
			getline(file, temperature, ',');
			getline(file, humidity);

			if (day == checkDate)				// Om dag = checkDate som just nu är 0
			{
				if (inOut == "Inne")			// Om det står "Inne" på inOut raden
				{

					i.temp += stod(temperature);	// Plussa ihop alla inne-temperaturer och gör om string temperature till en double
					i.fukt += stod(humidity);		// Plussa ihop alla inne-fuktvärden och gör om string humidity till en int
					inCount++;					// Starta en räknare för inne

				}
				else if (inOut == "Ute")		// Gör likadant med alla "Ute" värden och spara dom i u varibeln
				{


					u.temp += stod(temperature);
					u.fukt += stod(humidity);
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

					i.temp = round((i.temp / inCount) * 10) / 10;
					i.fukt = round((i.fukt / inCount) * 10) / 10;

					i.dag = currentDate;
					i.inUt = "Inne";

					dvIn.push_back(i);

					u.temp = round((u.temp / outCount) * 10) / 10;
					u.fukt = round((u.fukt / outCount) * 10) / 10;
					u.dag = currentDate;
					u.inUt = "Ute";


					dvOut.push_back(u);

					inCount = 0;
					outCount = 0;
					checkDate = day;
					u.temp = 0;
					i.temp = 0;

					// dela in i ute och inne, pushback till inne eller ute beroende på värdet av inOut.



						// cout << currentDate << " " << d.medelF << " " << d.medelT << " " <<  inOut << endl;



						// Separera inne och ute, gör en variabel för inne och ute var? Jag vill bara sortera temperaturer separat från varann. 

						// sortera medeltemperaturen från max till min och skriv sedan ut 5 värden med bubblesort





				}
			}

		}

		int n = dvIn.size();
		char selection;
		int select;
		string search;

		while (true)
		{
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
						if (dvIn[i].dag == search)
						{
							cout << dvIn[i].dag << " " << dvIn[i].temp << "  " << dvIn[i].inUt << endl;
						}
					}
				}
				else if (select == 2)
				{
					cout << "\n Search for Date in this format: YYYY-MM-DD ";
					cin >> search;
					for (int i = 0; i < n; i++)
					{
						if (dvOut[i].dag == search)
						{
							cout << dvOut[i].dag << " " << dvOut[i].temp << " " << dvOut[i].inUt << endl;
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
}
