/*
Christopher Custer
Assignment 7
Description: Use loops to create various different arrows and output it to a file.
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;
stringstream output;


//function for creating a box from user input with designated chars
void printZero(int size, char letter)
{
	// output header info of file
	output << "Symbol: Zero" << " Size: " << size << " Character: " << letter;
	if (size < 5)
	{
		size = 5;
		output << "Zero must have at least a size of 5.  Shape created with size: 5" << endl;
	}
	else
	{
		output << endl;
	}
	stringstream outputChars;

	// keeps the count of which column you are on for output
	int headerinfo = 0;
	for (int length = 0; length < size; length++)
	{
		headerinfo = headerinfo + 1;
		if (headerinfo > 9)
		{
			headerinfo = 0;
		}
		output << headerinfo;

		// if first or last line, fill in entire row
		if (length == 0 || length == size - 1)
		{
			for (int height = 0; height < size; height++)
			{
				outputChars << letter;
			}
		}
		else
		{
			for (int height = 0; height < size; height++)
			{
				if (height == size - length - 1 || height == 0 || height == size - 1)
				{
					outputChars << letter;
				}
				else
				{
					outputChars << " ";
				}
			}
		}
		outputChars << endl;
	}
	output << endl << endl << outputChars.str();
}

void printUpArrow(int size, char letter)
{
	int height = 1;
	stringstream outputChars;

	//makes the size even if its odd
	if (size % 2 != 0)
	{
		size++;
	}
	while (height <= size)
	{
		//if the height is the upper half create the arrow
		if (height <= size / 2)
		{
			int spaces = size - (2 * height);
			// spaces before
			int  i = 0;
			while (i < spaces / 2) {
				outputChars << ' ';
				i++;
			}
			i = 0;
			// chars after
			while (i < size - spaces)
			{
				outputChars << letter;
				i++;
			}

			while (i < spaces / 2) {
				outputChars << ' ';
				i++;
			}
			outputChars << endl;
		}
		else
		{
			int i = 0;
			// base
			while (i < (size - 2) / 2)
			{
				outputChars << ' ';
				i++;
			}
			i = 0;

			while (i < 2)
			{
				outputChars << letter;
				i++;
			}
			outputChars << endl;
		}

		height++;
	}
	output << endl << endl << outputChars.str();
}

void printRightArrow(int size, char letter)
{
	stringstream outputChars;

	int height = 1;
	int i = 0;
	//makes the size even if its odd
	if (size % 2 != 0)
	{
		size++;
	}
	int halfSize = (size / 2);

	//creates the upper half of the right arrow
	do
	{
		// top part
		if (height < size / 2)
		{
			i = 0;
			// put number of spaces 1/2 the size
			do
			{
				output << ' ';
				i++;

			} while (i < halfSize);

			// now put number of letters which is height
			i = 0;
			do
			{
				output << letter;
				i++;
			} while (i < height);
		}
		// middle
		else if (height == size / 2 || height == size / 2 + 1)
		{
			i = 1;
			do
			{
				output << letter;
				i++;
			} while (i <= size);
		}
		// lower
		else
		{
			i = 1;
			do
			{
				output << ' ';
				i++;

			} while (i <= halfSize);

			i = size - height + 1;

			do
			{
				output << letter;
				i--;
			} while (i > 0);
		}

		output << endl;
		height++;
	} while (height <= size);


	output << endl << endl << outputChars.str();

}


int main(int argc, char* argv[])
{

	int size = 0;
	char letter = ' ';
	string shape = "";
	string filename = "data.txt";
	ifstream fin;

	//statement to check if the file opened or not
	do
	{
		// todo: remove for final project 
		if (argc == 1)
		{
			cout << "Open file: ";
			cin >> filename;
		}
		fin.open(filename.c_str());
		if (!fin.is_open())
		{
			cout << "Could not open " << filename << endl;
		}
	} while (!fin.is_open());

	while (!fin.eof())
	{
		fin >> shape;
		fin >> size;
		fin >> letter;
		// protects against empty lines at end of file
		if (!fin.good())
		{
			break;
		}
		string filename = shape + "_" + to_string(size) + ".txt";

		ofstream fout(filename);
		if (shape == "zero")
		{
			printZero(size, letter);
			fout << output.str();
		}

		if (shape == "upArrow")
		{
			printUpArrow(size, letter);
			fout << output.str();
		}

		if (shape == "rightArrow")
		{
			printRightArrow(size, letter);
			cout << output.str();
		}
		fout.close();
		output.str("");

		//cout << "Shape Created: " << shape << endl;

	}

	fin.close();
}
