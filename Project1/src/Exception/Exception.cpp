#include "Exception.h"
#include <string>

illegalParameterValue::illegalParameterValue()
	: m_message("Illegal Paramter Value")
{
	
}

illegalParameterValue::illegalParameterValue(std::string& message)
{
	m_message = message;
}

void illegalParameterValue::outputMessage()
{
	std::cout << m_message << std::endl;
}

illegalIndex::illegalIndex()
	: m_message("Illegal Index")
{
}

illegalIndex::illegalIndex(std::string& message)
{
	m_message = message;
}

void illegalIndex::outputMessage()
{
	std::cout << m_message << std::endl;
}

undefinedSearchMethod::undefinedSearchMethod()
	: m_message("Undefined Search Method")
{
}

undefinedSearchMethod::undefinedSearchMethod(std::string& message)
{
	m_message = message;
}

void undefinedSearchMethod::outputMessage()
{
	std::cout << m_message << std::endl;
}

MatrixIndexOutOgBounds::MatrixIndexOutOgBounds(int i, int j)
{
	m_message = std::string("Matrix index ")
		.append(std::to_string(i))
		.append(" ")
		.append(std::to_string(j))
		.append(" ")
		.append("is out of bounds !");
}

void MatrixIndexOutOgBounds::outputMessage()
{
	std::cout << m_message << std::endl;
}

MatrixSizeMisMatch::MatrixSizeMisMatch(Matrix_Pair& matrix1, Matrix_Pair& matrix2, MatrixOperator _operator)
{
	switch (_operator)
	{
	case MATRIX_PLUS:
		m_message = std::string("Matrix1 can not plus with Matrix2 ")
			.append("because first dimension ")
			.append(std::to_string(matrix1.m_rows))
			.append(" != ")
			.append(std::to_string(matrix2.m_rows))
			.append(" or second dimension ")
			.append(std::to_string(matrix1.m_cols))
			.append(" != ")
			.append(std::to_string(matrix2.m_cols));
		break;
	case MATRIX_MINUS:
		m_message = std::string("Matrix1 can not minus Matrix2 ")
			.append("because first dimension ")
			.append(std::to_string(matrix1.m_rows))
			.append(" != ")
			.append(std::to_string(matrix2.m_rows))
			.append(" or second dimension ")
			.append(std::to_string(matrix1.m_cols))
			.append(" != ")
			.append(std::to_string(matrix2.m_cols));
		break;
	case MATRIX_MULTIPLY:
		m_message = std::string("Matrix1 can not multiply Matrix2 ")
			.append("because ths last dimension  of matrix1 ")
			.append(std::to_string(matrix1.m_cols))
			.append(" != ")
			.append("the first dimension of matrix2 ")
			.append(std::to_string(matrix2.m_rows));
		break;
	default:
		m_message = std::string("Error for matrix operator");
		break;
	}
}

void MatrixSizeMisMatch::outputMessage()
{
	std::cout << m_message << std::endl;
}

StackEmpty::StackEmpty()
{
	m_message = std::string("Stack is Empty !");
}

void StackEmpty::outputMessage()
{
	std::cout << m_message << std::endl;
}
