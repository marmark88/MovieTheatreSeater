// Mark Cubi
// June 8, 2023
// C++ code to impliment Ticket class

#include "Ticket.h"

using namespace std;

Ticket::Ticket()
{
	movie = "NOT SET";
	seat = "N/A";
	ageType = "NOT SET";
	time = -1;
	price = -1;

}

Ticket::Ticket(string moviePar, string ageTypePar, int timePar, int pricePar)
{
	movie = moviePar;
	ageType = ageTypePar;
	time = timePar;
	price = pricePar;
	seat = "NA";

}

string Ticket::getMovie()
{
	return movie;
}

string Ticket::getSeat()
{
	return seat;
}

string Ticket::getAgeType()
{
	return ageType;
}

int Ticket::getTime()
{
	return time;
}

float Ticket::getPrice()
{
	return price;
}

void Ticket::setMovie(string movieToSet)
{
	movie = movieToSet;
}

void Ticket::setSeat(string seatToSet)
{
	seat = seatToSet;
}

void Ticket::setAgeType(string ageTypeToSet)
{
	ageType = ageTypeToSet;
}

void Ticket::setTime(int timeToSet)
{
	time = timeToSet;
}

void Ticket::setPrice(float priceToSet)
{
	price = priceToSet;
}