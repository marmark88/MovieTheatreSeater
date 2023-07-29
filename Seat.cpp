// Mark Cubi
// June 26, 2023
// C++ code to define Seat class

#include "Seat.h"

using namespace std;

Seat::Seat()
{
	availability = 'O';
	position = "NX";
}

char Seat::getAvailability()
{
	return availability;
}

string Seat::getPosition()
{
	return position;
}

void Seat::setAvailability(char availToSet)
{
	availability = availToSet;
}

void Seat::setPosition(string posToSet)
{
	position = posToSet;
}