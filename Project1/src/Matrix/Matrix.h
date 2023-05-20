#pragma once
#include <iostream>
#include "../Exception/Exception.h"
#include "../LinearList/Linear.h"

template<typename T>
class Matrix
{
public:
	Matrix(int n_rows = 0, int n_cols = 0);
	Matrix(const Matrix<T>&);
	Matrix(const T*, int, int);
	~Matrix() { delete[] m_element; }

	int rows() const { return m_rows; }
	int cols() const { return m_cols; }
	T& operator() (int i, int j) const;
	Matrix<T>& operator= (const Matrix<T>&);
	void operator+ (T&);
	void operator+ (const Matrix<T>&);
	void operator- (T&);
	void operator- (const Matrix<T>&);
	Matrix<T> operator* (const Matrix<T>&) const;
	void operator+= (const T&);
	Matrix<T> tranpose();

private:
	int m_rows;
	int m_cols;
	T* m_element;
};

template<typename T>
class DiagonalMatrix
{
public:
	DiagonalMatrix(int n = 10);
	~DiagonalMatrix() { delete m_zero; delete[] m_element; }
	T& get(int, int) const;
	void set(int, int, const T&);

private:
	int m_dimension;
	T m_zero;
	T* m_element;
};

template<typename T>
class TridiagonalMatrix
{
public:
	TridiagonalMatrix(int n = 10);
	~TridiagonalMatrix() { delete m_zero; delete[] m_element; }
	T& get(int, int) const;
	void set(int, int, const T&);

private:
	int m_dimension;
	T m_zero;
	T* m_element;
};

template<typename T>
class LowerTriangularMatrix
{
public:
	LowerTriangularMatrix(int n = 10);
	~LowerTriangularMatrix() { delete m_zero; delete[] m_element; }
	T& get(int, int) const;
	void set(int, int, const T&);
private:
	int m_dimension;
	T m_zero;
	T* m_element;
};

template<typename T>
class UpperTriangularMatrix
{
public:
	UpperTriangularMatrix(int n = 10);
	~UpperTriangularMatrix() { delete m_zero; delete[] m_element; }
	T& get(int, int) const;
	void set(int, int, const T&);
private:
	int m_dimension;
	T m_zero;
	T* m_element;
};

template<typename T>
class MatrixTerm
{
public:
	MatrixTerm();
	MatrixTerm(int row, int col);
	MatrixTerm(int row, int col, const T& value);
	int row() const{ return m_row; }
	int col() const { return m_col; }
	const T& value() const { return m_value; }

	bool operator==(const MatrixTerm<T>& term);
	bool operator<(const MatrixTerm<T>& term);
	bool operator>(const MatrixTerm<T>& term);

private:
	int m_row;
	int m_col;
	T m_value;
};

template<typename T>
class SparseMatrix
{
public:
	SparseMatrix(int n_rows, int n_cols);
	const T& get(int, int) const;
	void set(int, int, const T&);
	SparseMatrix<T> transpose();
	void add(SparseMatrix<T>& matrix);
	int rows() const { return m_rows; }
	int cols() const { return m_cols; }
	ArrayList<MatrixTerm<T>>& data() { return m_elements; }

	SparseMatrix<T>& operator+(SparseMatrix<T>& matrix);
private:
	int m_rows;
	int m_cols;
	T m_zero;
	mutable ArrayList<MatrixTerm<T>> m_elements;
};


template<typename T>
inline Matrix<T>::Matrix(int n_rows, int n_cols)
{
	if (n_rows < 0 || n_cols < 0)
	{
		std::string s;
		s.append("Rows and Columns must be >= 0");
		throw illegalParameterValue(s);
	}
	if ((n_rows == 0 || n_cols == 0) && (n_rows != 0 || n_cols != 0))
	{
		std::string s;
		s.append("Either both or neither rows and columns should be zero");
		throw illegalParameterValue(s);
	}

	this->m_rows = n_rows;
	this->m_cols = n_cols;
	m_element = new T[n_rows * n_cols];
}

template<typename T>
inline Matrix<T>::Matrix(const Matrix<T>& matrix)
{
	this->m_rows = matrix.m_rows;
	this->m_cols = matrix.m_cols;
	this->m_element = new T[this->m_rows * this->m_cols];

	for (int i = 0; i < this->m_rows * this->m_cols; i++)
	{
		this->m_element[i] = matrix.m_element[i];
	}
}

template<typename T>
inline Matrix<T>::Matrix(const T* elements, int n_rows, int n_cols)
	: m_rows(n_rows), m_cols(n_cols)
{
	this->m_element = new T[this->m_rows * this->m_cols];

	for (int i = 0; i < this->m_rows * this->m_cols; i++)
	{
		this->m_element[i] = elements[i];
	}
}

template<typename T>
inline T& Matrix<T>::operator()(int i, int j) const
{
	if (i < 1 || i > this->m_rows || j < 1 || j > this->m_cols)
	{
		throw MatrixIndexOutOgBounds(i, j);
	}

	return this->m_element[(i - 1) * this->m_cols + j - 1];
}

template<typename T>
inline Matrix<T>& Matrix<T>::operator=(const Matrix<T>& matrix)
{
	if (this != &matrix)
	{
		delete[] this->m_element;
		this->m_rows = matrix.m_rows;
		this->m_cols = matrix.m_cols;
		this->m_element = new T[this->m_rows * this->m_cols];

		for (int i = 0; i < this->m_rows * this->m_cols; i++)
		{
			this->m_element[i] = matrix.m_element[i];
		}
	}

	return *this;
}

template<typename T>
inline void Matrix<T>::operator+(T& element) 
{
	for (int i = 0; i < this->m_rows * this->m_cols; i++)
	{
		this->m_element[i] += element;
	}
}

template<typename T>
inline void Matrix<T>::operator+(const Matrix<T>& matrix)
{
	if (this->m_rows != matrix.m_rows || this->m_cols != matrix.m_cols)
	{
		Matrix_Pair this_pair = { this->m_rows, this->m_cols };
		Matrix_Pair matrix_pair = { matrix.m_rows, matrix.m_cols };
		throw MatrixSizeMisMatch(
			this_pair,
			matrix_pair,
			MATRIX_PLUS);
	}

	for (int i = 0; i < this->m_rows * this->m_cols; i++)
	{
		this->m_element[i] += matrix.m_element[i];
	}
}

template<typename T>
inline void Matrix<T>::operator-(T& element)
{
	for (int i = 0; i < this->m_rows * this->m_cols; i++)
	{
		this->m_element[i] -= element;
	}
}

template<typename T>
inline void Matrix<T>::operator-(const Matrix<T>& matrix)
{
	if (this->m_rows != matrix.m_rows || this->m_cols != matrix.m_cols)
	{
		Matrix_Pair this_pair = { this->m_rows, this->m_cols };
		Matrix_Pair matrix_pair = { matrix.m_rows, matrix.m_cols };
		throw MatrixSizeMisMatch(
			this_pair,
			matrix_pair,
			MATRIX_MINUS);
	}

	for (int i = 0; i < this->m_rows * this->m_cols; i++)
	{
		this->m_element[i] -= matrix.m_element[i];
	}
}

template<typename T>
inline Matrix<T> Matrix<T>::operator*(const Matrix<T>& matrix) const
{
	if (this->m_cols != matrix.m_rows)
	{
		Matrix_Pair this_pair = { this->m_rows, this->m_cols };
		Matrix_Pair matrix_pair = { matrix.m_rows, matrix.m_cols };

		throw MatrixSizeMisMatch(
			this_pair,
			matrix_pair,
			MATRIX_MULTIPLY);
	}

	Matrix<T> result(this->m_rows, matrix.m_cols);

	int idx_this = 0, idx_matrix = 0, idx_result = 0;

	for (int i = 1; i <= matrix.m_rows; i++)
	{
		for (int j = 1; j <= matrix.m_cols; j++) 
		{
			T sum = this->m_element[idx_this] * matrix.m_element[idx_matrix];

			for (int k = 2; k <= this->m_cols; k++)
			{
				++idx_this;
				idx_matrix += matrix.m_cols;
				sum += this->m_element[idx_this] * matrix.m_element[idx_matrix];
			}

			result.m_element[idx_result++] = sum;

			idx_this -= this->m_cols - 1;
			idx_matrix = j;

		}

		idx_this += this->m_cols;
		idx_matrix = 0;

	}

	return result;

}

template<typename T>
inline void Matrix<T>::operator+=(const T& element)
{
	this->operator+(element);
}

template<typename T>
inline Matrix<T> Matrix<T>::tranpose()
{
	Matrix<T> tranposed(this->m_cols, this->m_rows);
	int idx_trans = 0;
	for (int j = 1; j <= this->m_cols; j++)
	{
		for (int i = 1; i <= this->m_rows; i++)
		{
			tranposed.m_element[idx_trans++] = this->operator()(i, j);
		}
	}
	
	return tranposed;

}

template<typename T>
std::ostream& operator<< (std::ostream& out, const Matrix<T>& matrix)
{
	out << "The Matrix is : \n";
	for (int i = 1; i <= matrix.rows(); i++)
	{
		for (int j = 1; j <= matrix.cols(); j++)
		{
			out << matrix(i, j) << " ";
		}
		out << "\n";
	}
	return out;
}

template<typename T>
inline DiagonalMatrix<T>::DiagonalMatrix(int n)
{
	if (n < 1)
	{
		std::string s;
		s.append("Matrix size must be > 0");
		throw illegalParameterValue(s);
	}

	m_dimension = n;
	m_zero = new T();
	m_element = new T[m_dimension];
}

template<typename T>
inline T& DiagonalMatrix<T>::get(int i, int j) const
{
	if (i < 1 || j < 1 || i > m_dimension || j > m_dimension)
	{
		throw MatrixIndexOutOgBounds(i, j);
	}

	if (i == j)
	{
		return m_element[i - 1];
	}
	else
	{
		return m_zero;
	}
}

template<typename T>
inline void DiagonalMatrix<T>::set(int i, int j, const T& element)
{
	if (i < 1 || j < 1 || i > m_dimension || j > m_dimension)
	{
		throw MatrixIndexOutOgBounds(i, j);
	}

	if (i == j)
	{
		m_element[i - 1] = element;
	}
	else
	{
		std::cout << "Can not set the value in diagonal matrix" << std::endl;
	}
}

template<typename T>
inline TridiagonalMatrix<T>::TridiagonalMatrix(int n)
{
	if (n < 1)
	{
		std::string s;
		s.append("Matrix size must be > 0");
		throw illegalParameterValue(s);
	}

	m_dimension = n;
	m_zero = new T();
	m_element = new T[3 * m_dimension - 2];
}

template<typename T>
inline T& TridiagonalMatrix<T>::get(int i, int j) const
{
	if (i < 1 || j < 1 || i > m_dimension || j > m_dimension)
	{
		throw MatrixIndexOutOgBounds(i, j);
	}

	switch (i - j)
	{
	case 1:
		return m_element[i - 2];
	case 0:
		return m_element[m_dimension + i - 2];
	case -1:
		return m_element[2 * m_dimension + i - 2];
	default:
		return m_zero;
	}
}

template<typename T>
inline void TridiagonalMatrix<T>::set(int i, int j, const T& element)
{
	if (i < 1 || j < 1 || i > m_dimension || j > m_dimension)
	{
		throw MatrixIndexOutOgBounds(i, j);
	}

	switch (i - j)
	{
	case 1:
		m_element[i - 2] = element;
	case 0:
		m_element[m_dimension + i - 2] = element;
	case -1:
		m_element[2 * m_dimension + i - 2] = element;
	default:
		std::cout << "Can not set the value in tri-diagonal matrix" << std::endl;
		break;
	}
}

template<typename T>
inline LowerTriangularMatrix<T>::LowerTriangularMatrix(int n)
{
	if (n < 1)
	{
		std::string s;
		s.append("Matrix size must be > 0");
		throw illegalParameterValue(s);
	}

	m_dimension = n;
	m_zero = new T();
	m_element = new T[m_dimension * (m_dimension + 1) / 2];
}

template<typename T>
inline T& LowerTriangularMatrix<T>::get(int i, int j) const
{
	if (i < 1 || j < 1 || i > m_dimension || j > m_dimension)
	{
		throw MatrixIndexOutOgBounds(i, j);
	}

	if (i >= j)
	{
		return m_element[i * (i - 1) / 2 + j - 1];
	}
	else
	{
		return m_zero;
	}
}

template<typename T>
inline void LowerTriangularMatrix<T>::set(int i, int j, const T& element)
{
	if (i < 1 || j < 1 || i > m_dimension || j > m_dimension)
	{
		throw MatrixIndexOutOgBounds(i, j);
	}

	if (i >= j)
	{
		m_element[i * (i - 1) / 2 + j - 1] = element;
	}
	else
	{
		std::cout << "Can not set the value in lower triangular matrix" << std::endl;
	}
}

template<typename T>
inline UpperTriangularMatrix<T>::UpperTriangularMatrix(int n)
{
	if (n < 1)
	{
		std::string s;
		s.append("Matrix size must be > 0");
		throw illegalParameterValue(s);
	}

	m_dimension = n;
	m_zero = new T();
	m_element = new T[m_dimension * (m_dimension + 1) / 2];
}

template<typename T>
inline T& UpperTriangularMatrix<T>::get(int i, int j) const
{
	if (i < 1 || j < 1 || i > m_dimension || j > m_dimension)
	{
		throw MatrixIndexOutOgBounds(i, j);
	}

	if (i <= j)
	{
		return m_element[(2 * m_dimension - i + 2) * (i - 1) / 2 + j - 1];
	}
	else
	{
		return m_zero;
	}
}

template<typename T>
inline void UpperTriangularMatrix<T>::set(int i, int j, const T& element)
{
	if (i < 1 || j < 1 || i > m_dimension || j > m_dimension)
	{
		throw MatrixIndexOutOgBounds(i, j);
	}

	if (i <= j)
	{
		m_element[(2 * m_dimension - i + 2) * (i - 1) / 2 + j - 1] = element;
	}
	else
	{
		std::cout << "Can not set the value in upper triangular matrix" << std::endl;
	}
}

template<typename T>
inline MatrixTerm<T>::MatrixTerm()
	:m_row(0), m_col(0)
{
	m_value = T();
}

template<typename T>
inline MatrixTerm<T>::MatrixTerm(int row, int col)
	:m_row(row), m_col(col)
{
	m_value = T();
}

template<typename T>
inline MatrixTerm<T>::MatrixTerm(int row, int col, const T& value)
	: m_row(row), m_col(col), m_value(value)
{
}

template<typename T>
bool MatrixTerm<T>::operator==(const MatrixTerm<T>& term)
{
	return m_row == term.row() && m_col == term.col();
}

template<typename T>
inline bool MatrixTerm<T>::operator<(const MatrixTerm<T>& term)
{
	if (m_row < term.row())
	{
		return true;
	}

	if (m_row > term.row())
	{
		return false;
	}

	if (m_col < term.col())
	{
		return true;
	}
	else
	{
		return false;
	}

}

template<typename T>
inline bool MatrixTerm<T>::operator>(const MatrixTerm<T>& term)
{
	if (m_row > term.row())
	{
		return true;
	}

	if (m_row < term.row())
	{
		return false;
	}

	if (m_col > term.col())
	{
		return true;
	}
	else
	{
		return false;
	}
}

template<typename T>
inline SparseMatrix<T>::SparseMatrix(int n_rows, int n_cols)
	:m_rows(n_rows), m_cols(n_cols)
{
}

template<typename T>
inline const T& SparseMatrix<T>::get(int i, int j) const
{
	if (i < 1 || j < 1 || i > m_rows || j > m_cols)
	{
		throw MatrixIndexOutOgBounds(i, j);
	}

	auto start = m_elements.begin();
	auto end = m_elements.end();
	
	if (start == end)
	{
		return m_zero;
	}

	MatrixTerm<T> search(i, j);
	--end;

	if (search < (*start))
	{
		return m_zero;
	}

	if (search > (*end))
	{
		return m_zero;
	}

	++end;

	for (;start != end; start++)
	{
		if ((*start) < search)
		{
			continue;
		}

		if ((*start) > search)
		{
			return m_zero;
		}

		return (*start).value();
	}

	std::cout << "ERROR IN GET SPARSE MATRIX !" << std::endl;
}

template<typename T>
inline void SparseMatrix<T>::set(int i, int j, const T& value)
{
	if (i < 1 || j < 1 || i > m_rows || j > m_cols)
	{
		throw MatrixIndexOutOgBounds(i, j);
	}

	int index = 0;
	auto start = m_elements.begin();
	auto end = m_elements.end();
	MatrixTerm<T> term(i, j, value);

	if (start == end)
	{
		m_elements.insert(0, term);
		return;
	}

	--end;
	
	if (term < (*start))
	{
		m_elements.insert(0, term);
		return;
	}

	if (term > (*end))
	{
		m_elements.insert(m_elements.size(), term);
		return;
	}

	++end;

	for (; start != end; start++)
	{
		if ((*start) < term)
		{
			++index;
			continue;
		}

		if ((*start) > term)
		{
			m_elements.insert(index, term);
			return;
		}

		m_elements.update(index, term);
		return;
	}

}

template<typename T>
inline SparseMatrix<T> SparseMatrix<T>::transpose()
{
	SparseMatrix<T> matrix(m_cols, m_rows);
	for (auto iter = m_elements.begin(); iter != m_elements.end(); iter++)
	{
		int i = (*iter).col();
		int j = (*iter).row();
		T value = (*iter).value();
		matrix.set(i, j, value);
	}

	return matrix;
}

template<typename T>
inline void SparseMatrix<T>::add(SparseMatrix<T>& matrix)
{
	if (this->rows() != matrix.rows() || this->cols() != matrix.cols())
	{
		std::cout << "Matrix Plus Matrix should have same size " << std::endl;
		Matrix_Pair this_pair = { this->rows(), this->cols()};
		Matrix_Pair matrix_pair = { matrix.rows(), matrix.cols() };
		throw MatrixSizeMisMatch(
			this_pair,
			matrix_pair,
			MATRIX_PLUS);
	}

	for (auto iter = matrix.data().begin(); 
		iter != matrix.data().end(); 
		iter++)
	{
		int i = (*iter).row();
		int j = (*iter).col();
		T value = (*iter).value();
		this->set(i, j, this->get(i, j) + value);
	}
}

template<typename T>
inline SparseMatrix<T>& SparseMatrix<T>::operator+(SparseMatrix<T>& matrix)
{
	this->add(matrix);
	return *this;
}

template<typename T>
std::ostream& operator<<(std::ostream& out, MatrixTerm<T>& term)
{
	out << "matrix(" << term.row() << "," << term.col() << ")"
		<< " = " << term.value() << std::endl;
	return out;
}

template<typename T>
std::ostream& operator<<(std::ostream& out, SparseMatrix<T>& matrix)
{
	out << "rows = " << matrix.rows() << std::endl;
	out << "columns = " << matrix.cols() << std::endl;

	out << "The Sparse Matrix is : \n\n" << std::endl;

	for (int i = 0; i < matrix.rows(); i++)
	{
		for (int j = 0; j < matrix.cols(); j++) 
		{
			out << "  " << matrix.get(i + 1, j + 1) << "  ";
		}
		out << "\n";
	}

	return out;
}



