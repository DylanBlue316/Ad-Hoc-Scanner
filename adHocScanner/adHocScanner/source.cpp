/*
Programmer: Dylan Yeary
Date: 19 September 2023
Design:This program is designed as an ad hoc scanner for calculator language
*/
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

//declare functions
void stripSpacing(string&);
void checkForCommands();
void checkForLetters();
void checkForDecimals();
void checkForDigits();
void checkForOp();
void checkAssignment();

int x1=0;
int x2=0;

//holds the string for processing
string holder;

//file input and output variables
fstream input;
fstream output;

//used to navigate holder and find certain characters within the holder string
char tempA[1];
char tempB[1];
int x = 0;
int xTemp = 0;

//main function
int main()
{
	output.open("output.txt");
	input.open("input.txt");

	if (input.is_open())
	{
		while (!input.eof())
		{
			start:
			getline(input, holder);
			//modification to check for comments and ignore them when writing to the output file
			if (holder[x] == '/' && holder[x + 1] == '/')
			{
				cout << "Comment ignored: Continuing... " << endl;
				goto start;
			}


			stripSpacing(holder);

			while (holder.length() != x)
			{
				checkForOp();
				checkAssignment();
				checkForDecimals();
				checkForDigits();
				checkForCommands();
				checkForLetters();
			}
			output <<endl;
			x = 0;
		}
	}
	input.close();
	output.close();
	cout << "Check output file: ";
	return 0;
}

//function definitions

//strip empty spaces from the string
void stripSpacing(string& s)
{
	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] == ' ')
		{
			s.erase(i, 1);
			i--;
		}
	}
}

//checks for the read, write, and sum commands
void checkForCommands()
{
	xTemp = x;

	//read command
	if (holder[x] == 'r')
	{
		x++;
		if (holder[x] == 'e')
		{
			x++;
			if (holder[x] == 'a')
			{
				x++;
				if (holder[x] == 'd')
				{
					x++;
					output << "read\n";
					goto stop;
				}
				else x = xTemp;
				goto stop;
			}
			else x = xTemp;
			goto stop;
		}
		else x = xTemp;
		goto stop;
	}

	//write command
	if (holder[x] == 'w')
	{
		x++;
		if (holder[x] == 'r')
		{
			x++;
			if (holder[x] == 'i')
			{
				x++;
				if (holder[x] == 't')
				{
					x++;
					if (holder[x] == 'e')
					{
						x++;
						output << "write\n";
						goto stop;
					}
					else x = xTemp;
					goto stop;
				}
				else x = xTemp;
				goto stop;
			}
			else x = xTemp;
			goto stop;
		}
		else x = xTemp;
		goto stop;
	}

	//sum command
	if (holder[x] == 's')
	{
		x++;
		if (holder[x] == 'u')
		{
			x++;
			if (holder[x] == 'm')
			{
				x++;
				output << "sum\n";
				goto stop;
			}
			else x = xTemp;
			goto stop;
		}
		else x = xTemp;
		goto stop;
	}
	stop:
	cout << "";
}

void checkForLetters()
{
	if (isalpha(holder[x]))
	{
		output << holder[x];
		x++;
	}
}

void checkForDecimals()
{
	if (isdigit(holder[x]))
	{
		output << holder[x];
		x++;

		// Check for decimal point after a digit
		if (holder[x] == '.')
		{
			output << ".";
			x++;
		}
	}
}

void checkForDigits()
{
	if (isdigit(holder[x]))
	{
		output << holder[x];
		x++;
	}
}

void checkForOp()
{
	// Checks for operators
	if (holder[x] == '(' || holder[x] == ')' || holder[x] == '+' || holder[x] == '-' || holder[x] == '*' || holder[x] == '/')
	{
		// Add a newline if the previous character was a digit
		if (x > 0 && isdigit(holder[x - 1]))
		{
			output << "\n"; 
		}

		output << holder[x];
		x++;

		// Check for spaces or newlines after the operator
		while (holder[x] == ' ' || holder[x] == '\n')
		{
			output << holder[x];
			x++;
		}
		output << "\n";

	}
}

void checkAssignment()
{
	//assignment command
	if (holder[x] == ':')
	{
		x++;
		if (holder[x] == '=')
		{
			output << ":=\n";
			x++;
		}
		else
		{
			output << "Error: Incorrect Input" << endl;
		}
	}
}
