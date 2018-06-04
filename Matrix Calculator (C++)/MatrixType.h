/****************************************************************************************************************
Project Name: MatrixMenu
File Name: MatrixType.h
Programmed By: Derek Chan
IDE/Compiler: Microsoft Visual Studio Community
Date: 10/9/16
Project Description: This is the class header file for MatrixType.
****************************************************************************************************************/
#ifndef __MATRIXTYPE_H_INCLUDED__
#define __MATRIXTYPE_H_INCLUDED__

#include <iostream>
#include <fstream>
using namespace std;

const int MAX_ROWS = 10;
const int MAX_COLS = 10;

class MatrixType
{
public:
	MatrixType();
	void MakeEmpty();
	void SetSize(int rowSize, int colSize);
	void StoreItem(int item, int row, int col);
	void Add(MatrixType otherOperand, MatrixType& result);
	void Sub(MatrixType otherOperand, MatrixType& result);
	void Mult(MatrixType otherOperand, MatrixType& result);
	void Print(ofstream& outfile);
	void PrintScr();
	bool AddSubCompatible(MatrixType otherOperand);
	bool MultCompatible(MatrixType otherOperand);
private:
	int values[MAX_ROWS][MAX_COLS];
	int numRows;
	int numCols;
};

#endif