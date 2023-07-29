// Mark Cubi
// June 6, 2023
// C++ code to create movie theatre schedule

#include <iostream>
#include <fstream>
#include <vector>
#include "Theatre.h"
#include "Ticket.h"
#include "Seat.h"

using namespace std;

// functions
vector<Ticket*> getOrder(); // gets information about how many tickets, what movie, and what time
string timeConverter(int timeToConvert); // converts  time form conventional to military
void printReceipt(int time, int theatreNum, string movieName, const vector<Ticket*>& order); // prints out all order info for user

// constant variables
const int CHILD_PRICE = 15;
const int ADULT_PRICE = 20;
const int SENIOR_PRICE = 17; 
const double TAX_RATE = .086;
const vector<string> MOVIE_LIST = { "Spiderman: Across the Spider-Verse", "The Little Mermaid", "Elemental" };
const vector<int> TIME_LIST = { 1800, 2000, 2200 }; // maybe combine into one 2d schedule array in later revision
size_t NUM_OF_SHOWINGS = MOVIE_LIST.size() * TIME_LIST.size();

int main()
{
	ofstream outFile;
	ifstream inFile;
	vector<Ticket*> order;
	vector<Theatre> cinema;
	string placement;
	string columnNum; 
	bool error = false;
	int seatCounter = 0;
	int selectedTheatre = 0;

	order = getOrder();

	for (int i = 0; i < MOVIE_LIST.size(); i++)
	{
		for (int z = 0; z < TIME_LIST.size(); z++)
		{
			Theatre cinemaToAdd(MOVIE_LIST[i], TIME_LIST[z]); // matches each movie and time with a theatre
			cinema.push_back(cinemaToAdd);
		}
	}

	for (int i = 0; i < NUM_OF_SHOWINGS; i++)
	{
		if (order[0]->getMovie() == cinema[i].getMovie() && order[0]->getTime() == cinema[i].getTime())
			selectedTheatre = i; // matches the users selected movie and time with its respective theatre
	}
	
	cinema[selectedTheatre].readTheatre(); // readTheatre reads seating information is a separate file, allowing theatre to update with each use

	cinema[selectedTheatre].printTheatre(); // outputs theatre with updated seating 

	if (cinema[selectedTheatre].theatreIsFull() == true)
	{
		cout << "The Theatre is Full!";
		cinema[selectedTheatre].deleteSeats(); // resets the theatre to all empty seats if it is full
		return 1;
	}

	if (cinema[selectedTheatre].noConsecSeats(order.size()) == true) 
	{
		cout << "WARNING: There are not enough consecutive seats in a row for your order! People may have \n";
		cout << "to sit in different areas of the theatre! \n";
	}
		
		while(seatCounter < order.size()) // process for selected seats, resets if user selected an already taken seat
		{
			if (error == true)
				cout << "Please enter a different seat: ";
			else
				cout << "Please enter where you want to sit (enter a capital row letter and column number): ";

			cin >> placement;
			cout << endl;

			for (int z = 0; z < ROW_SIZE; z++)
			{
				for (int g = 0; g < COLUMN_SIZE; g++)
				{
					if (cinema[selectedTheatre].matchSeat(placement, z, g)) //matches seat to its respective theatre seat
					{
						if (cinema[selectedTheatre].overlapSeat(z, g)) // returns an error if seat is already taken
						{
							error = true;
							break;
						}
						else
						{
							cinema[selectedTheatre].selectSeat(z, g); // otherwie marks the seat as unavailable and continues loop
							error = false;
							order[seatCounter]->setSeat(placement);
							seatCounter++;
						}
					}
				}
			}
			cinema[selectedTheatre].printTheatre(); // prints theatre each time to update UI
		}

		printReceipt(cinema[selectedTheatre].getTime(), cinema[selectedTheatre].getTheatreNum(), cinema[selectedTheatre].getMovie(), order);

	return 0;

}


vector<Ticket*> getOrder()
{
	int movieNum, timeNum;
	string movie;
	int childTicket, adultTicket, seniorTicket;
	vector<Ticket*> orderList;
	int time = 0; // initialize to 0 to avoid error if for loop does not match a time below 

	cout << "Hello! Select a movie you would like to see (enter the number next to the movie)" << endl;
	for (int i = 0; i < MOVIE_LIST.size(); i++)
	{
		cout << i + 1 << ")" << " " << MOVIE_LIST[i] << endl; // for loop allows for movie lists to be easily customizable
	}

	cin >> movieNum;


	for (int i = 0; i < MOVIE_LIST.size(); i++)
	{
		if (movieNum == (i + 1))
			movie = MOVIE_LIST[i];
	}
	
	cout << "What time would you like to see " << movie << "? (enter the number next to the time)" << endl;
	for (int i = 0; i < TIME_LIST.size(); i++)
	{
		cout << i + 1 << ")" << " " << timeConverter(TIME_LIST[i]) << endl;
	}
	
	cin >> timeNum;

	for (int i = 0; i < TIME_LIST.size(); i++)
	{
		if (timeNum == (i + 1))
			time = TIME_LIST[i];
	}

	cout << "How many children tickets would you like to purchase (must be 13 and under): $" << CHILD_PRICE << " each : ";
	cin >> childTicket;
	cout << "How many adult tickets would you like to purchase: $" << ADULT_PRICE << " each: ";
	cin >> adultTicket;
	cout << "How many senior tickets would you like to purchase: $" << SENIOR_PRICE << " each : ";
	cin >> seniorTicket;
	cout << endl;

	for (int i = 0; i < childTicket; i++)
	{
		Ticket* order = new Ticket(movie, "child", time, CHILD_PRICE);
		orderList.push_back(order);
	}

	for (int i = 0; i < adultTicket; i++)
	{
		Ticket* order = new Ticket(movie, "adult", time, ADULT_PRICE);
		orderList.push_back(order);
	}

	for (int i = 0; i < seniorTicket; i++)
	{
		Ticket* order = new Ticket(movie, "senior", time, SENIOR_PRICE);
		orderList.push_back(order);
	}

	return orderList;
}

string timeConverter(int timeToConvert) // converts conventional time to military time
{
	string time; 
	string hour, minute;

	if (timeToConvert == 0)
		return "12:00";
	else if (timeToConvert <= 12)
	{
		hour = to_string(timeToConvert / 100);
		time = hour;
		minute = to_string(timeToConvert % 100);
		
		if (minute == "0")
		{
			minute = ":00am";
			time = hour + minute;
		}
		else
			time = hour + minute + "am";

		return time;
	}
	else
	{
		hour = to_string((timeToConvert / 100)-12);
		time = hour;
		minute = to_string(timeToConvert % 100);

		if (minute == "0")
		{
			minute = ":00pm";
			time = hour + minute;
		}
		else
			time = hour + minute + "pm";


		return time;
	}
}

void printReceipt(int time, int theatreNum, string movieName, const vector<Ticket*>& order) 
{
	double costOfTickets = 0;
	double taxTotal = 0;

	cout << endl;
	cout << "Here is your receipt!" << endl;
	cout << endl;
	cout << "MOVIE: " << movieName << endl;
	cout << "TIME: " << timeConverter(time) << endl;
	cout << "THEATRE NUMBER: " << theatreNum << endl;
	cout << "NUMBER OF TICKETS: " << order.size() << endl;
	cout << "TICKET LOCATION + INFO" << endl;
	cout << "-----------------------------" << endl;

	for (int i = 0; i < order.size(); i++)
	{
		cout << order[i]->getAgeType() << " ticket| seat: " << order[i]->getSeat() << " price: $" << order[i]->getPrice() << endl;
	}

	cout << endl;
	cout << "      SUBTOTAL" << endl;
	cout << "---------------------" << endl;
	for (int i = 0; i < order.size(); i++)
	{
		costOfTickets += order[i]->getPrice();
	}
	taxTotal = costOfTickets * TAX_RATE; // add decimal places that cut off after 2 
	
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2);

	cout << "Tickets: $" << costOfTickets << endl;
	cout << "TAX: $" << taxTotal << endl;
	cout << endl;
	cout << "Total: $" << costOfTickets + taxTotal;
	cout << endl;
	cout << "Thank you for shopping with us!" << endl;
}

