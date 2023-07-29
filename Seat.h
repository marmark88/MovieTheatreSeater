// Mark Cubi
// June 26, 2023
// C++ code to define Seat class

#ifndef SEAT_H
#define SEAT_H

#include <string>
using namespace std;

class Seat
{
	public:
		Seat();
		char getAvailability();
		string getPosition();
		void setAvailability(char availToSet);
		void setPosition(string posToSet);
		// basic setters and getters
	private:
		char availability;
		string position;
};

#endif
