#pragma once
#include <iostream>
#include "../Const/const.h"

struct Matrix_Pair
{
	int m_rows;
	int m_cols;
};

class illegalParameterValue
{
public:
	illegalParameterValue();
	illegalParameterValue(std::string&);
	void outputMessage();

private:
	std::string m_message;
};

class illegalIndex
{
public:
	illegalIndex();
	illegalIndex(std::string&);
	void outputMessage();

private:
	std::string m_message;
};

class undefinedSearchMethod
{
public:
	undefinedSearchMethod();
	undefinedSearchMethod(std::string&);
	void outputMessage();
private:
	std::string m_message;
};

class MatrixIndexOutOgBounds
{
public:
	MatrixIndexOutOgBounds(int i, int j);
	void outputMessage();
private:
	std::string m_message;
};

class MatrixSizeMisMatch
{
public:
	MatrixSizeMisMatch(Matrix_Pair& matrix1, Matrix_Pair& matrix2, MatrixOperator _operator);
	void outputMessage();
private:
	std::string m_message;
};

class StackEmpty
{
public:
	StackEmpty();
	void outputMessage();
private:
	std::string m_message;
};




