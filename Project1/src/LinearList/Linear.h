#pragma once
#include <iostream>
#include <string>
#include "Linear.h"
#include "../Exception/Exception.h"
template<typename T>
class LinearList
{
public:
	virtual ~LinearList() {};
	virtual bool empty() const = 0;
	virtual int size() const = 0;
	virtual T& get(int index) const = 0;
	virtual int indexOf(const T& element) const = 0;
	virtual void erase(int index) = 0;
	virtual void insert(int index, const T& element) = 0;
	virtual void output(std::ostream& out) const = 0;


	// Extended
	virtual void trimToSize() { };
	virtual int capacity() const = 0;
};

template<typename T>
class ArrayList : public LinearList<T>
{
public:

	ArrayList();
	ArrayList(int initial_capacity);
	ArrayList(const ArrayList<T>&);
	~ArrayList();
	class Iterator;


	// ADT
	bool empty() const;
	int size() const;
	T& get(int index) const;
	int indexOf(const T& element) const;
	void erase(int index);
	void insert(int index, const T& element);
	void update(int index, const T& element);
	void output(std::ostream& out) const;

	// others
	int capacity() const;
	Iterator begin() { return Iterator(m_list); }
	Iterator end() { return Iterator(m_list + listSize); }

	// Extended
	void trimToSize();
	T& operator[](int index) const;
	void push_back(const T& element);
	void pop_back();
	void swap(ArrayList<T>& list);

protected:
	void checkIndex(int index) const;

	T* m_list;
	int arrayLength;
	int listSize;
private:
	int m_initial_capacity;
};

template<typename T>
class ChainNode
{
public:
	ChainNode() {}
	ChainNode(const T& element) { this->m_element = element; }
	ChainNode(const T& element, ChainNode<T>* nextNode) 
	{
		this->m_element = element;
		this->m_nextNode = nextNode;
	}

	T& get() { return m_element; }
	void set(const T& element) { this->m_element = element; }
	ChainNode<T>* next() const { return m_nextNode; }
	void setNext(ChainNode<T>* nextNode) { this->m_nextNode = nextNode; }

private:
	T m_element;
	ChainNode<T>* m_nextNode;
};

template<typename T>
class Chain : public LinearList<T>
{
public:
	Chain();
	Chain(int initial_capacity);
	Chain(const Chain<T>&);
	~Chain();
	class Iterator;

	// ADT
	bool empty() const { return this->m_listSize == 0; }
	int size() const { return this->m_listSize; }
	T& get(int) const;
	int indexOf(const T&) const;
	void erase(int);
	void insert(int, const T&);
	void output(std::ostream&) const;

	ChainNode<T>* first() const { return this->m_firstNode; }
	void setFirst(ChainNode<T>* firstNode) { this->m_firstNode = firstNode; }
	void setSize(const int& size) { this->m_listSize = size; }
	Iterator begin() { return Iterator(m_firstNode); }
	Iterator end() { return Iterator(nullptr); }

	// Extended
	void clear();
	void push_back(const T& element);
	int capacity() const { return INT_MAX; }

private:
	void checkIndex(int index) const;

private:
	int m_listSize;
	ChainNode<T>* m_firstNode;
	ChainNode<T>* m_lastNode;
};



/*

Definition of ArrayList

*/

template<typename T>
class ArrayList<T>::Iterator
{
public:

	typedef std::bidirectional_iterator_tag iterator_category;
	typedef T value_type;
	typedef std::ptrdiff_t difference_type;
	typedef T* pointer;
	typedef T& reference;

	Iterator() { m_pointer = nullptr; };
	Iterator(T* pointer) { m_pointer = pointer; };

	T& operator*() const { return *m_pointer; };
	T* operator->() const { return &*m_pointer; };
	Iterator& operator++ () {
		++m_pointer;
		return *this;
	};
	Iterator operator++ (int) {
		Iterator old = *this;
		++m_pointer;
		return old;
	};
	Iterator& operator-- () {
		--m_pointer;
		return *this;
	};
	Iterator operator-- (int) {
		Iterator old = *this;
		--m_pointer;
		return old;
	};

	bool operator!=(const Iterator right) const { return m_pointer != right.m_pointer; };
	bool operator==(const Iterator right) const { return m_pointer == right.m_pointer; };

private:
	T* m_pointer;
};


template<typename T>
ArrayList<T>::ArrayList()
	: m_initial_capacity(16)
{
	arrayLength = m_initial_capacity;
	m_list = new T[arrayLength];
	listSize = 0;
}

template<typename T>
ArrayList<T>::ArrayList(int initial_capacity)
{
	if (initial_capacity < 1)
	{
		std::string s;
		s.append("Initial capacity = ")
			.append(initial_capacity)
			.append("Must be > 0");
		throw illegalParameterValue(s);
	}

	m_initial_capacity = initial_capacity;
	arrayLength = initial_capacity;
	m_list = new T[arrayLength];
	listSize = 0;
}

template<typename T>
ArrayList<T>::ArrayList(const ArrayList<T>& arraylist)
{
	m_initial_capacity = 16;
	arrayLength = arraylist.arrayLength;
	listSize = arraylist.listSize;
	m_list = new T[arrayLength];
	for (int i = 0; i < listSize; i++)
	{
		m_list[i] = arraylist.m_list[i];
	}
}

template<typename T>
ArrayList<T>::~ArrayList()
{
	delete[] m_list;
}

template<typename T>
bool ArrayList<T>::empty() const
{
	return listSize == 0;
}

template<typename T>
int ArrayList<T>::size() const
{
	return listSize;
}

template<typename T>
int ArrayList<T>::capacity() const
{
	return arrayLength;
}

template<typename T>
void ArrayList<T>::checkIndex(int index) const
{
	if (index < 0 || index >= listSize) {
		std::string s;
		s.append("index = ")
			.append(std::to_string(index))
			.append(" size = ")
			.append(std::to_string(listSize));
		throw illegalIndex(s);
	}
}

template<typename T>
T& ArrayList<T>::get(int index) const
{
	checkIndex(index);
	return m_list[index];
}

template<typename T>
int ArrayList<T>::indexOf(const T& element) const
{
	for (int i = 0; i < listSize; i++)
	{
		if (m_list[i] == element) {
			return i;
		}
	}

	return -1;
}

template<typename T>
void ArrayList<T>::erase(int index)
{
	checkIndex(index);

	for (int i = index + 1; i < listSize; i++)
	{
		m_list[i - 1] = m_list[i];
	}

	m_list[--listSize].~T();

	if (listSize < std::floor(arrayLength / 4))
	{
		int length = m_initial_capacity > std::floor(arrayLength / 2) ? 
			m_initial_capacity : std::floor(arrayLength / 2);
		T* temp = new T[length];
		for (int i = 0; i < listSize; i++)
		{
			temp[i] = m_list[i];
		}

		delete[] m_list;

		m_list = temp;
		arrayLength = length;
	}

}

template<typename T>
void ArrayList<T>::insert(int index, const T& element)
{
	if (index < 0 || index > listSize) {
		std::string s;
		s.append("index = ")
			.append(std::to_string(index))
			.append(" size = ")
			.append(std::to_string(listSize));
		throw illegalIndex(s);
	}

	if (listSize == arrayLength)
	{
		T* temp = new T[2 * arrayLength];
		for (int i = 0; i < arrayLength; i++)
		{
			temp[i] = m_list[i];
		}

		delete[] m_list;

		m_list = temp;
		arrayLength = arrayLength * 2;
	}


	for (int i = listSize - 1; i >= index; i--)
	{
		m_list[i + 1] = m_list[i];
	}

	m_list[index] = element;
	++listSize;

}

template<typename T>
void ArrayList<T>::update(int index, const T& element)
{
	checkIndex(index);
	
	m_list[index] = element;

}

template<typename T>
void ArrayList<T>::output(std::ostream& out) const
{
	out << "Current LinearList : " << std::endl;
	for (int i = 0; i < listSize; i++)
	{
		out << i << " : " << m_list[i] << std::endl;
	}
}



/*

	Extended of ArrayList

*/
template<typename T>
void ArrayList<T>::trimToSize()
{
	int length = listSize > 1 ? listSize : 1;

	T* temp = new T[length];
	for (int i = 0; i < length; i++)
	{
		temp[i] = m_list[i];
	}

	delete[] m_list;

	m_list = temp;
	arrayLength = length;

}

template<typename T>
void ArrayList<T>::push_back(const T& element)
{
	if (listSize == arrayLength)
	{
		T* temp = new T[2 * arrayLength];
		for (int i = 0; i < arrayLength; i++)
		{
			temp[i] = m_list[i];
		}

		delete[] m_list;

		m_list = temp;
		arrayLength = arrayLength * 2;
	}

	m_list[listSize++] = element;
}

template<typename T>
void ArrayList<T>::pop_back()
{
	if (listSize == 0)
	{
		std::cout << "The arraylist has nothing to pop " << std::endl;
		return;
	}

	m_list[listSize - 1].~T();
	--listSize;

}

template<typename T>
void ArrayList<T>::swap(ArrayList<T>& list)
{
	int length = this->size() < list.size() ? this->size() : list.size();
	for (int i = 0; i < length; i++)
	{
		T temp = this->get(i);
		this->update(i, list.get(i));
		list.update(i, temp);
	}

	if (this->size() < list.size())
	{
		for (int i = length; i < list.size(); i++)
		{
			this->push_back(list.get(i));
		}

		for (int i = 0; i < list.size() - length; i++)
		{
			list.pop_back();
		}
	}
	else if (this->size() > list.size())
	{
		for (int i = length; i < this->size(); i++)
		{
			list.push_back(this->get(i));
		}

		for (int i = 0; i < this->size() - length; i++)
		{
			this->pop_back();
		}
	}

}

/*

	Override operator of ArrayList

*/

template<typename T>
T& ArrayList<T>::operator[](int index) const
{
	return this->get(index);
}

template<typename T>
bool operator==(const ArrayList<T> listA, const ArrayList<T> listB)
{
	if (listA.size() != listB.size())
	{
		return false;
	}

	for (int i = 0; i < listA.size(); i++)
	{
		if (listA.get(i) != listB.get(i))
		{
			return false;
		}
	}

	return true;
}

template<typename T>
bool operator!=(const ArrayList<T> listA, const ArrayList<T> listB)
{
	return !(listA == listB);
}

template<typename T>
bool operator<(const ArrayList<T> listA, const ArrayList<T> listB)
{
	int length = listA.size() > listB.size() ? listB.size() : listA.size();
	for (int i = 0; i < length; i++)
	{
		if (listA.get(i) < listB.get(i))
			return true;
		else if (listA.get(i) > listB.get(i))
		{
			return false;
		}
		else {
			continue;
		}
	}

	return listA.size() < listB.size();
}



/*

	Definition of LinkedList

*/

template<typename T>
class Chain<T>::Iterator
{
public:

	typedef std::bidirectional_iterator_tag iterator_category;
	typedef T value_type;
	typedef std::ptrdiff_t difference_type;
	typedef T* pointer;
	typedef T& reference;

	Iterator() { m_node = nullptr; }
	Iterator(ChainNode<T>* node) { m_node = node; }

	T& operator*() const { return m_node->get(); }
	T* operator->() const { return &(m_node->get()); }
	Iterator& operator++ () {
		m_node = m_node->next();
		return *this;
	};
	Iterator operator++ (int) {
		Iterator old = *this;
		m_node = m_node->next();
		return old;
	};

	bool operator!=(const Iterator right) const { return m_node != right.m_node; }
	bool operator==(const Iterator right) const { return m_node == right.m_node; }

private:
	ChainNode<T>* m_node;
};


template<typename T>
Chain<T>::Chain()
	: m_listSize(0), m_firstNode(nullptr), m_lastNode(nullptr)
{

}

template<typename T>
Chain<T>::Chain(int initial_capacity)
	: m_firstNode(nullptr), m_lastNode(nullptr)
{
	if (initial_capacity < 1)
	{
		std::string s;
		s.append("Initial capacity = ")
			.append(initial_capacity)
			.append("Must be > 0");
		throw illegalParameterValue(s);
	}

	m_listSize = 0;
}

template<typename T>
Chain<T>::Chain(const Chain<T>& chain)
{
	m_listSize = chain.size();

	if (m_listSize == 0)
	{
		m_firstNode = nullptr;
		return;
	}

	ChainNode<T>* node = chain.first();
	m_firstNode = new ChainNode<T>(node->get());
	node = node->next();
	ChainNode<T>* targetNode = m_firstNode;

	while (node != nullptr)
	{
		targetNode->setNext(new ChainNode<T>(node->get()));
		targetNode = targetNode->next();
		node = node->next();

		if (node == nullptr)
		{
			m_lastNode = targetNode;
		}

	}

	targetNode->setNext(nullptr);
}

template<typename T>
Chain<T>::~Chain()
{
	while (m_firstNode != nullptr)
	{
		ChainNode<T>* nextNode = m_firstNode->next();
		delete m_firstNode;
		m_firstNode = nextNode;
	}
}

template<typename T>
void Chain<T>::checkIndex(int index) const 
{
	if (index < 0 || index >= m_listSize) {
		std::string s;
		s.append("index = ")
			.append(std::to_string(index))
			.append(" size = ")
			.append(std::to_string(m_listSize));
		throw illegalIndex(s);
	}
}

template<typename T>
T& Chain<T>::get(int index) const
{
	checkIndex(index);

	ChainNode<T>* currentNode = m_firstNode;
	for (int i = 0; i < index; i++)
	{
		currentNode = currentNode->next();
	}

	return currentNode->get();
}

template<typename T>
int Chain<T>::indexOf(const T& element) const
{
	ChainNode<T>* currentNode = m_firstNode;
	int currentIndex = 0;
	while (currentNode != nullptr && currentNode->get() != element)
	{
		currentNode = currentNode->next();
		++currentIndex;
	}

	return currentNode == nullptr ? -1 : currentIndex;
}

template<typename T>
void Chain<T>::erase(int index)
{
	checkIndex(index);

	ChainNode<T>* deleteNode;
	if (index == 0)
	{
		deleteNode = m_firstNode;
		m_firstNode = m_firstNode->next();

		if (m_listSize == 1)
		{
			m_lastNode = nullptr;
		}

	}
	else
	{
		ChainNode<T>* pre = m_firstNode;
		for (int i = 0; i < index - 1; i++)
		{
			pre = pre->next();
		}

		deleteNode = pre->next();

		if (index == m_listSize - 1)
		{
			m_lastNode = pre;
		}

		pre->setNext(deleteNode->next());
	}

	--m_listSize;
	delete deleteNode;
}

template<typename T>
void Chain<T>::insert(int index, const T& element)
{
	if (index < 0 || index > m_listSize)
	{
		std::string s;
		s.append("index = ")
			.append(std::to_string(index))
			.append(" size = ")
			.append(std::to_string(m_listSize));
		throw illegalIndex(s);
	}

	if (index == 0)
	{	
		m_firstNode = new ChainNode<T>(element, m_firstNode);
		
		if (m_listSize == 1)
		{
			m_lastNode = m_firstNode;
		}
	}
	else
	{
		ChainNode<T>* pre = m_firstNode;
		for (int i = 0; i < index - 1; i++)
		{
			pre = pre->next();
		}

		ChainNode<T>* insertNode = new ChainNode<T>(element, pre->next());

		if (index == m_listSize)
		{
			m_lastNode = insertNode;
		}

		pre->setNext(insertNode);
	}

	++m_listSize;

}

template<typename T>
void Chain<T>::output(std::ostream& out) const
{
	out << "Current LinearList : " << std::endl;
	int index = 0;
	ChainNode<T>* currentNode = m_firstNode;
	while (currentNode != nullptr)
	{
		out << index << " : " << currentNode->get() << std::endl;
		currentNode = currentNode->next();
		++index;
	}
}


/*

	Extended of LinkedList

*/
template<typename T>
void Chain<T>::clear() 
{
	while (m_firstNode != nullptr)
	{
		ChainNode<T>* nextNode = m_firstNode->next();
		delete m_firstNode;
		m_firstNode = nextNode;
	}

	m_listSize = 0;
	m_lastNode = nullptr;
}

template<typename T>
void Chain<T>::push_back(const T& element)
{
	ChainNode<T>* pushNode = new ChainNode<T>(element, nullptr);

	if (m_firstNode == nullptr)
	{
		m_firstNode = m_lastNode = pushNode;
	}
	else
	{
		m_lastNode->setNext(pushNode);
		m_lastNode = pushNode;
	}

	++m_listSize;

}


/*

	Override operator of LinkedList

*/



/*

	Override operator of LinearList

*/
template<typename T>
std::ostream& operator<<(std::ostream& out, const LinearList<T>& list)
{
	list.output(out);
	return out;
}
