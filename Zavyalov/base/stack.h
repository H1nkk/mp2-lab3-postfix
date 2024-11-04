#ifndef __STACK_H__
#define __STACK_H__

const int MaxStackSize = 100;

template <class T>
class TStack
{
	T* pMem;
	int size;
	int top;
public:
	TStack(): size(0), top(-1), pMem(nullptr) {}

	TStack(int _size)
	{
		size = _size;
		top = -1;
		if ((size < 1) || (size > MaxStackSize))
		throw size;
		pMem = new T[size];
	}

	bool full() const noexcept {
		return top == size - 1; // условие правильное???
	}

	void push(T val) { // not T& because char uses 1 byte, while & uses 4 or 8 bytes
		if (full()) throw "StackOverflow"; 
		pMem[++top] = val;
	}

	bool empty() const noexcept {
		return top == -1;
	}

	T pop() {
		if (empty()) throw "Cannot pop from empty stack";
		return pMem[top--];
	}

	int getsize() const {
		return top + 1;
	}

	~TStack()
	{
		delete [] pMem;	
	}
};

#endif
