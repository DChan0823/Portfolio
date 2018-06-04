/****************************************************************************************************************
Project Name: MatrixMenu
File Name: MatrixType.cpp
Programmed By: Derek Chan
IDE/Compiler: Microsoft Visual Studio Community
Date: 10/9/16
Project Description: This is the .cpp file for MatrixType.
****************************************************************************************************************/
#include <iostream>
#include <fstream>
#include "MatrixType.h"
using namespace std;

//const int MAX_ROWS = 10;
//const int MAX_COLS = 10;

	/*************************************************************************
	MatrixType()
	Function: Constructor
	Precondition: the MatrixType Object is properly declared
	Postcondition: the object is initialized and the variables numRows and 
	numCols is set to 0
	*************************************************************************/
	MatrixType::MatrixType()
	{
		numRows = 0;
		numCols = 0;
	}
	/*************************************************************************
	MakeEmpty()
	Function: Zeros out the matrix.
	Precondition: none.
	Postcondition: Each cell of private var values[i][j] are set to 0
	*************************************************************************/
	void MatrixType::MakeEmpty()
	{
		for (int i = 0; i < numRows; i++)
		{
			for (int j = 0; j < numCols; j++)
			{
				values[i][j] = 0;
			}
		}
	}
	/*************************************************************************
	SetSize(int rowSize, int colSize)
	Function: sets the size of the matrix
	Precondition: parameters rowSize and colSize are initialized ints
	Postcondition: private var rowSize and colSize are mutated into the param
	values.
	*************************************************************************/
	void MatrixType::SetSize(int rowSize, int colSize)
	{
		numRows = rowSize;
		numCols = colSize;
	}
	/*************************************************************************
	StoreItem(int item, int row, int col)
	Function: stores a value into a specific cell of matrix
	Precondition: item, row, and col params are initialized ints
	Postcondition: value in the specified cell of var array values is mutated
	into value of param item.
	*************************************************************************/
	void MatrixType::StoreItem(int item, int row, int col)
	{
		values[row][col] = item;
	}
	/*************************************************************************
	Add(MatrixType otherOperand, MatrixType& result)
	Function: adds two matrices together and saves the result
	Precondition: the MatrixType object param otherOperand is initialized properly,
	the pass by reference MatrixType object param result is initialized properly
	Postcondition: the result object's matrix size is set to numRows and numCols,
	the resulting values from the add are stored in the result object param
	*************************************************************************/
	void MatrixType::Add(MatrixType otherOperand, MatrixType& result)
	{
		result.SetSize(numRows, numCols);		//initializing result matrix

		for (int i = 0; i < numRows; i++)
		{
			for (int j = 0; j < numCols; j++)
			{
				result.values[i][j] = values[i][j] + otherOperand.values[i][j];
			}
		}
	}
	/*************************************************************************
	Sub(MatrixType otherOperand, MatrixType& result)
	Function: subtracts two matrices and saves the result
	Precondition: the MatrixType object param otherOperand is initialized properly,
	the pass by reference MatrixType object param result is initialized properly
	Postcondition: the result object's matrix size is set to numRows and numCols,
	the resulting values from the sub are stored in the result object param
	*************************************************************************/
	void MatrixType::Sub(MatrixType otherOperand, MatrixType& result)
	{
		result.SetSize(numRows, numCols);		//initializing result matrix

		for (int i = 0; i < numRows; i++)
		{
			for (int j = 0; j < numCols; j++)
			{
				result.values[i][j] = values[i][j] - otherOperand.values[i][j];
			}
		}
	}
	/*************************************************************************
	Mult(MatrixType otherOperand, MatrixType& result)
	Function: multiplies two matrices and saves the result
	Precondition: the MatrixType object param otherOperand is initialized properly,
	the pass by reference MatrixType object param result is initialized properly
	Postcondition: the result object's matrix row size is set to numRows and the 
	col size is set to the numCols of the otherOperand object param,
	the resulting values from the mult are stored in the result object param
	*************************************************************************/
	void MatrixType::Mult(MatrixType otherOperand, MatrixType& result)
	{
		result.SetSize(numRows, numCols);		//initializing result matrix

		for (int i = 0; i < numRows; i++)
		{
			for (int j = 0; j < otherOperand.numCols; j++)
			{
				int sum = 0;

				for (int k = 0; k < numCols; k++)
				{
					sum += values[i][k] * otherOperand.values[k][j];
				}

				result.values[i][j] = sum;
			}
		}
	}
	/*************************************************************************
	void Print(ofstream& outfile)
	Function: Prints the values of matrix to an outfile.
	Precondition: the outfile param is properly initialized
	Postcondition: there will be an outfile that contains the values of the matrix
	*************************************************************************/
	void MatrixType::Print(ofstream& outfile)
	{
		for (int i = 0; i < numRows; i++)
		{
			for (int j = 0; j < numCols; j++)
			{
				outfile << values[i][j] << " ";
			}

			outfile << endl;
		}

		outfile << endl;
	}
	/*************************************************************************
	void PrintScr()
	Function: Prints values of the matrix to screen.
	Precondition: none
	Postcondition: the values of matrix are printed to screen
	*************************************************************************/
	void MatrixType::PrintScr()
	{
		for (int i = 0; i < numRows; i++)
		{
			cout << "[ ";
			for (int j = 0; j < numCols; j++)
			{
				cout << values[i][j] << " ";
			}

			cout << "]" << endl;
		}

		cout << endl;
	}
	/*************************************************************************
	AddSubCompatible(MatrixType otherOperand)
	Function: Checks to see if the two matrices are add/sub compatible
	Precondition: the MatrixType object param otherOperand is initialized properly
	Postcondition: returns true if the two objects numRows private vars are equal,
	else returns false.
	*************************************************************************/
	bool MatrixType::AddSubCompatible(MatrixType otherOperand)
	{
		if (numRows == otherOperand.numRows && numCols == otherOperand.numCols)
			return true;
		else
			return false;
	}
	/*************************************************************************
	bool MultCompatible(MatrixType otherOperand)
	Function: Checks to see if the two matrices are multi compatible
	Precondition: the MatrixType object param otherOperand is initialized properly
	Postcondition: returns true if the private vars numCols is equal to otherOperand's
	numRows, else returns false.
	*************************************************************************/
	bool MatrixType::MultCompatible(MatrixType otherOperand)
	{
		if (numCols == otherOperand.numRows)
			return true;
		else
			return false;
	}