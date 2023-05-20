#pragma once
#include <iostream>
#include "../Exception/Exception.h"
#include "../LinearList/Linear.h"
#include "../Const/const.h"

template<typename T>
class Stack
{
public:
	virtual ~Stack() {};
	virtual bool empty() const = 0;
	virtual int size() const = 0;
	virtual T& top() = 0;
	virtual void pop() = 0;
	virtual void push(const T& element) = 0;
};


template<typename T>
class ArrayStack : public Stack<T>
{
public:
	ArrayStack(int capacity = 10);
	~ArrayStack() { delete m_stack; }
	bool empty() const { return m_top == -1; }
	int size() const { return m_top + 1; }
	T& top();
	void pop();
	void push(const T& element);

private:
	int m_top;
	int m_capacity;
	T* m_stack;
};

template<typename T>
inline ArrayStack<T>::ArrayStack(int capacity)
{
	if (capacity < 1)
	{
		std::string s;
		s.append("capacity = ")
			.append(std::to_string(capacity))
			.append("must be > 0");
		throw illegalParameterValue(s);
	}

	m_capacity = capacity;
	m_stack = new T[m_capacity];
	m_top = -1;
}

template<typename T>
inline T& ArrayStack<T>::top()
{
	if (m_top == -1)
	{
		throw StackEmpty();
	}
	return m_stack[m_top];
}

template<typename T>
inline void ArrayStack<T>::pop()
{
	if (m_top == -1)
	{
		std::cout << "Can't pop from the stack! " << std::endl;
		throw StackEmpty();
	}
	m_stack[m_top--].~T();
}

template<typename T>
inline void ArrayStack<T>::push(const T& element)
{
	if (m_top == m_capacity - 1)
	{
		T* temp = new T[2 * m_capacity];
		for (int i = 0; i < m_capacity; i++)
		{
			temp[i] = m_stack[i];
		}

		delete[] m_stack;

		m_stack = temp;
		m_capacity = m_capacity * 2;
	}

	m_stack[++m_top] = element;
}



template<typename T>
class LinkedStack : public Stack<T>
{
public:
	LinkedStack(int capacity = 10) { m_top = nullptr; m_size = 0; }
	~LinkedStack();
	bool empty() const { return m_size == 0; }
	int size() const { return m_size; }
	T& top();
	void pop();
	void push(const T& element);

private:
	ChainNode<T>* m_top;
	int m_size;
};

template<typename T>
inline LinkedStack<T>::~LinkedStack()
{
	while (m_top != nullptr)
	{
		ChainNode<T>* nextNode = m_top->next();
		delete m_top;
		m_top = nextNode;
	}
}

template<typename T>
inline T& LinkedStack<T>::top()
{
	if (m_size == 0)
	{
		throw StackEmpty();
	}

	return m_top->get();
}

template<typename T>
inline void LinkedStack<T>::pop()
{
	if (m_size == 0)
	{
		throw StackEmpty();
	}

	ChainNode<T>* nextNode = m_top->next();
	delete m_top;
	m_top = nextNode;
	--m_size;
}

template<typename T>
inline void LinkedStack<T>::push(const T& element)
{
	m_top = new ChainNode<T>(element, m_top);
	++m_size;
}



/*

  match pairs ( and )

*/
void PrintMatchedPairs(std::string expr);

void PrintHanoi(int n_disk);

bool Railroad(int input[], int num_cars, int num_tracks);

bool CheckBox(int net[], int n);

void OfflineEquivalenceClass();

struct Position
{
	int row;
	int col;
};

bool findPath(int** matrix, int n_size);