#pragma once
#include "../connection/DebugSerial.h"

template <typename T>
class Vector
{
	template <typename T1>
	struct Node
	{
		T1 obj;
		Node<T1>* next = nullptr;
	};

	Node<T>* begin = nullptr;
	Node<T>* end = nullptr;
public:
	~Vector();
	
	void push(const T& t);
	T pop();

	bool isEmpty() const;
};

template <typename T>
Vector<T>::~Vector()
{
	while (!isEmpty())
	{
		pop();
	}
}

template <typename T>
void Vector<T>::push(const T& t)
{
	// creating new block
	Node<T> * newEnd = new Node<T>;
	if (!newEnd)
	{
		DEBUG_PRINTLN("Cannot allocate memory for new vector element");
		return;
	}

	newEnd->obj = t;

	// linking new block
	if (begin == nullptr)
	{
		begin = end = newEnd;
	}
	else
	{
		end->next = newEnd;
		end = newEnd;
	}
}

template <typename T>
T Vector<T>::pop()
{
	if (isEmpty())
	{
		return T();
	}

	// save pop result
	T result = begin->obj;

	// move begin pointer
	Node<T>* oldBegin = begin;
	begin = begin->next;

	// null end pointer if require
	if (oldBegin == end)
	{
		end = nullptr;
	}

	// clear old memory
	delete oldBegin;

	return result;
}

template <typename T>
bool Vector<T>::isEmpty() const
{
	return !begin;
}
