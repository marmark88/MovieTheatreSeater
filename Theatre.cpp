// Mark Cubi
// June 7, 2023
// C++ code to impliment Ticket class

#include <iostream>
#include "Theatre.h"
#include <fstream>
#include <sstream>

using namespace std; 

Theatre::Theatre()
{
	movie = "NOT SET";
	time = 000000;
	currentTheatreNum++;
}

Theatre::Theatre(string movieToSet, int timeToSet)
{
	char rowLetter;
	string columnNum;

	movie = movieToSet;
	time = timeToSet;
	currentTheatreNum++;
	theatreNum = currentTheatreNum;

	for (int i = 0; i < ROW_SIZE; i++)
	{
		rowLetter = static_cast<char>('A' + i);

		for (int z = 0; z < COLUMN_SIZE; z++)
		{
			columnNum = to_string(z + 1);
			theatreSeats[i][z].setPosition(rowLetter + columnNum);
		}
	}
}

int Theatre::currentTheatreNum = 0;

void Theatre::selectSeat(int rowPos, int columnPos) 
{
	theatreSeats[rowPos][columnPos].setAvailability('X');
}

void Theatre::printTheatre()
{
	char rowLetter;
	ofstream outData;
	string fileNum = to_string(theatreNum);
	string fileName = "SeatInfo" + fileNum + ".txt";

	cout << "Theatre Number " << theatreNum << ", " << movie << endl;
	cout << "-------------------------MOVIE SCREEN-----------------------------        X = taken | O = available " << endl;
	for (int i = 0; i < ROW_SIZE; i++)
	{
		rowLetter = static_cast<char>('A' + i);
		cout << "   " << rowLetter << "     ";

		for (int z = 0; z < COLUMN_SIZE; z++)
		{
			cout << theatreSeats[i][z].getAvailability() << "     "; 
		}
		cout << endl;
	}

	cout << "         ";
	for (int i = 0; i < COLUMN_SIZE; i++)
	{
		cout << i + 1 << "     ";
	}
	cout << endl;

	outData.open(fileName); // after the theatre seating is outputed, update a seperate data file 
	if (!outData.is_open()) // tracking seating so that changes to seating are saved
	{
		cout << fileName << " Outfile has failed to open!";
		exit(-1);
	}

	for (int i = 0; i < ROW_SIZE; i++)
	{
		for (int z = 0; z < COLUMN_SIZE; z++)
		{
			outData << theatreSeats[i][z].getPosition() << " " << theatreSeats[i][z].getAvailability() << endl;
		}
	}
	outData.close();
}

void Theatre::readTheatre()
{
	ifstream inFile;
	string posReader, inputReader;
	char availReader;
	int columnCounter = 0;
	int rowCounter = 0;
	string fileNum = to_string(theatreNum);
	string fileName = "SeatInfo" + fileNum + ".txt";

	inFile.open(fileName); // reads the data file for a selected theatre so that seating info can be updated to account for changes
	if (!inFile.is_open())
	{
		cout << fileName << " Infile could not be opened!";
		exit(-1);
	}

	while (getline(inFile, inputReader))
	{
		istringstream inSS(inputReader);
		inSS >> posReader;
		inSS >> availReader;

		theatreSeats[rowCounter][columnCounter].setPosition(posReader);
		theatreSeats[rowCounter][columnCounter].setAvailability(availReader);
		
		if (columnCounter < (COLUMN_SIZE - 1))
		{
			columnCounter++;
		}
		else
		{
			columnCounter = 0;
			rowCounter++;
		}
	} 
	inFile.close();

	
}

bool Theatre::theatreIsFull(int orderSize)
{
	int availSeats = 0;
	
	for (int i = 0; i < ROW_SIZE; i++)
	{
		for (int z = 0; z < COLUMN_SIZE; z++)
		{
			if(theatreSeats[i][z].getAvailability() == 'O')
				availSeats++;
		}
	}

	if (orderSize > availSeats)
		return true;
	else
		return false;
}

bool Theatre::noConsecSeats(int orderSize)
{
	int availConsecSeats = 0;
	int largestConsecSeats = 0;

	for (int i = 0; i < ROW_SIZE; i++)
	{
		for (int z = 0; z < COLUMN_SIZE; z++)
		{
			if (theatreSeats[i][z].getAvailability() == 'O')
			{
				availConsecSeats++;
				// work on this to make 3 seats in a row and stuff availConsecSeats++;	
			}
			else
				availConsecSeats = 0;

		}
		if (availConsecSeats > largestConsecSeats)
			largestConsecSeats = availConsecSeats;

		availConsecSeats = 0;
	}

	if (orderSize > largestConsecSeats)
		return true;
	else
		return false;
}

void Theatre::deleteSeats()
{
	ofstream outData;

	for (int i = 0; i < ROW_SIZE; i++)
	{
		for (int z = 0; z < COLUMN_SIZE; z++)
		{
			theatreSeats[i][z].setAvailability('O');
		}
	}

	outData.open("SeatInfo.txt");
	if (!outData.is_open())
	{
		cout << "Outdata has failed to open!";
		exit(-1);
	}

	for (int i = 0; i < ROW_SIZE; i++)
	{
		for (int z = 0; z < COLUMN_SIZE; z++)
		{
			outData << theatreSeats[i][z].getPosition() << " " << theatreSeats[i][z].getAvailability() << endl;
		}
	}
	outData.close();
}

bool Theatre::matchSeat(string posToMatch, int rowPos, int columnPos)
{
	if (theatreSeats[rowPos][columnPos].getPosition() == posToMatch)
		return true;
	else
		return false;
}

bool Theatre::overlapSeat(int rowPos, int columnPos)
{
	if (theatreSeats[rowPos][columnPos].getAvailability() == 'X')
	{
		cout << "Seat " << theatreSeats[rowPos][columnPos].getPosition() << " has already been taken!" << endl;
		return true;
	}
	else
		return false;
} 

string Theatre::getMovie()
{
	return movie;
}

int Theatre::getTime()
{
	return time; 
}

int Theatre::getTheatreNum()
{
	return theatreNum;
}