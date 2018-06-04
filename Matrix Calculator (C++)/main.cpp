/****************************************************************************************************************
Project Name: MatrixMenu
File Name: main.cpp
Programmed By: Derek Chan
IDE/Compiler: Microsoft Visual Studio Community
Date: 10/9/16
Project Description: This is a menu driver for the class <MatrixType>. It allows a user to store, add, subtract,
and multiply a total of 10 matrices in an array. Also, contains a Print to file function.
****************************************************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "MatrixType.h"
using namespace std;
enum Menu { newMatrix, addMatrix, subMatrix, multMatrix, printMatrix, Quit };
const int ARRAY_SIZE = 10;

int main()
{
	int menuChoice;										//user menu choice
	int matrixChoice1, matrixChoice2, matrixChoice3;	//user matrix choice
	int rowSize, colSize;								
	int userNum;			
	ofstream outFile;
	string filename;
	MatrixType arr[ARRAY_SIZE];							//array of MatrixType objects
	
	/*taking a user inputed filename and opening for write*/
	cout << "Please specify an outfile for printing matrices: ";
	cin >> filename;
	outFile.open(filename);

	do
	{
		/*Menu Display*/
		cout << "Choice and Parameters:" << endl;
		cout << left << setw(22) << "0 New Matrix" << "Usage: 0 <matrix>" << endl;
		cout << left << setw(22) << "1 Add Matrices" << "Usage: 1 <matrix> <matrix> <matrix>" << endl;
		cout << left << setw(22) << "2 Subtract Matrices" << "Usage: 2 <matrix> <matrix> <matrix>" << endl;
		cout << left << setw(22) << "3 Multiply Matrices" << "Usage: 3 <matrix> <matrix> <matrix>" << endl;
		cout << left << setw(22) << "4 Print Matrix" << "Usage: 4 <matrix>" << endl;
		cout << left << setw(22) << "5 Quit" << "Usage: 5" << endl << endl;
		cout << left << setw(22) << "Enter Choice and Parameters: ";
		cin >> menuChoice;
		
		/*Switch statement for Menu*/
		switch (menuChoice)
		{
		case newMatrix:							//Creating New Matrix
			cin >> matrixChoice1;
			cout << "Creating new matrix in slot " << matrixChoice1 << endl;
			cout << "Enter row and column size: ";

			/*Error checking on size of matrix*/
			try
			{
				cin >> rowSize;
				cin >> colSize;

				if (rowSize > 10 || colSize > 10 || rowSize < 0 || colSize < 0)
					throw string("Incorrect Sizes!");		
			}
			catch (string message)
			{
				cout << message << " Returning to Main Menu." << endl << endl;
				break;
			}

			/*Store user input values into new matrix*/
			arr[matrixChoice1].SetSize(rowSize, colSize);

			for (int i = 0; i < rowSize; i++)
			{
				cout << "Row " << i << ": ";

				for (int j = 0; j < colSize; j++)
				{
					cin >> userNum;
					arr[matrixChoice1].StoreItem(userNum, i, j);
				}
			}

			arr[matrixChoice1].PrintScr();

			break;
		case addMatrix:
			cin >> matrixChoice1;
			cin >> matrixChoice2;
			cin >> matrixChoice3;

			/*error checking for add compatibility*/
			try
			{
				if (!arr[matrixChoice1].AddSubCompatible(arr[matrixChoice2]))
					throw string("Matrices are NOT Add Compatible.");
			}
			catch (string message)
			{
				cout << message << " Returning to Main Menu." << endl << endl;
				break;
			}

			cout << "Adding Matrix " << matrixChoice1 << " and Matrix " << matrixChoice2 << ". Storing in Matrix " << matrixChoice3 << endl;

			arr[matrixChoice1].Add(arr[matrixChoice2], arr[matrixChoice3]);

			cout << "Result: " << endl;

			arr[matrixChoice3].PrintScr();

			break;
		case subMatrix:
			cin >> matrixChoice1;
			cin >> matrixChoice2;
			cin >> matrixChoice3;

			/*error checking for subtraction compatibility*/
			try
			{
				if (!arr[matrixChoice1].AddSubCompatible(arr[matrixChoice2]))
					throw string("Matrices are NOT Sub Compatible.");
			}
			catch (string message)
			{
				cout << message << " Returning to Main Menu." << endl << endl;
				break;
			}

			cout << "Subtracting Matrix " << matrixChoice1 << " from Matrix " << matrixChoice2 << ". Storing in Matrix " << matrixChoice3 << endl;

			arr[matrixChoice1].Sub(arr[matrixChoice2], arr[matrixChoice3]);

			cout << "Result: " << endl;

			arr[matrixChoice3].PrintScr();

			break;
		case multMatrix:
			cin >> matrixChoice1;
			cin >> matrixChoice2;
			cin >> matrixChoice3;

			/*error checking for multiplication compatibility*/
			try
			{
				if (!arr[matrixChoice1].MultCompatible(arr[matrixChoice2]))
					throw string("Matrices are NOT Multi Compatible.");
			}
			catch (string message)
			{
				cout << message << " Returning to Main Menu." << endl << endl;
				break;
			}

			cout << "Multiplying Matrix " << matrixChoice1 << " and Matrix " << matrixChoice2 << ". Storing in Matrix " << matrixChoice3 << endl;

			arr[matrixChoice1].Mult(arr[matrixChoice2], arr[matrixChoice3]);

			cout << "Result: " << endl;

			arr[matrixChoice3].PrintScr();

			break;
		case printMatrix:
			cin >> matrixChoice1;

			cout << "Printing Matrix " << matrixChoice1 << endl;
			
			arr[matrixChoice1].Print(outFile);

			break;
		case Quit:
			break;
		default:
			cout << "USER CHOICE UNRECOGNIZED. PLEASE TRY AGAIN" << endl;
			break;
		}

	} while (menuChoice != Quit);

	outFile.close();

	return 0;
}