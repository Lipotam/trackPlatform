#pragma once

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
	//TODO
}

template <typename T>
T Vector<T>::pop()
{
	//TODO
	return T();
}

template <typename T>
bool Vector<T>::isEmpty() const
{
	//TODO
	return false;
}
