// Mark Cubi
// June 7, 2023
// C++ code to define Ticket class


#ifndef Theatre_H
#define Theatre_H

#include "Seat.h"
#include <string>
using namespace std;

const int ROW_SIZE = 8;
const int COLUMN_SIZE = 10;

class Theatre
{
	public:
		Theatre();
		Theatre(string movieToSet, int timeToSet);
		string getMovie();
		int getTime();
		int getTheatreNum();
		void selectSeat(int rowPos, int columnPos); // marks seat as unavailable
		void printTheatre();
		void readTheatre();
		bool theatreIsFull(int orderSize = 1);
		bool matchSeat(string posToMatch, int rowPos, int columnPos); // matches user selected seat to theatre seat
		bool overlapSeat(int rowPos, int columnPos); // checks if seat is already taken
		bool noConsecSeats(int orderSize);
		void deleteSeats(); // deletes seats once the theatre is completely full
		static int currentTheatreNum;

	private:
		Seat theatreSeats[ROW_SIZE][COLUMN_SIZE]; // maybe make this dynamic array
		string movie;
		int time;
		int theatreNum;
};

#endif
