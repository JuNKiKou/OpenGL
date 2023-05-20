#pragma once
#include<iostream>
enum MatrixOperator
{
	MATRIX_PLUS = 1,
	MATRIX_MINUS,
	MATRIX_MULTIPLY,
	MATRIX_TRANSPOSITION
};

enum MazeOption
{
	TO_RIGHT = 0,
	TO_DOWN = 1,
	TO_LEFT = 2,
	TO_UP = 3,
	NO_PATH = 4
};



MazeOption operator++(MazeOption& _option);

