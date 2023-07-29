// Mark Cubi
// June 8, 2023
// C++ code to declare a Ticket class

#ifndef TICKET_H
#define TICKET_H

#include <string>
using namespace std;

class Ticket
{
	public:
		Ticket();
		Ticket(string moviePar, string ageTypePar, int timePar, int pricePar);
		string getMovie();
		string getSeat();
		string getAgeType();
		int getTime();
		float getPrice();
		void setMovie(string movieToSet);
		void setSeat(string seatToSet);
		void setAgeType(string ageTypeToSet);
		void setTime(int timeToSet);
		void setPrice(float priceToSet);
		// basic getters and setters
	private:
		string movie;
		string seat;
		string ageType;
		int time;
		float price; 
};

#endif
