#include <iostream>
#include <cassert>
#include <cstdint>

template <class _Type, int _Count = 1>
struct MsgValue
{
	_Type* value;
	int size()const { return sizeof(_Type) * _Count; }
	char* end()const { return (char*)(value + _Count); }
	operator _Type()const { return *value; }
	operator _Type*()const { return value; }
	void operator = (const _Type&other) {
		std::cout << "void operator = (const _Type&other)" << std::endl;
		assert(_Count == 1);
		*value = other;
	}
	_Type& operator[](int pos) {
		assert(pos >= 0);
		if (pos < _Count)
			return value[pos];
		throw(-1);
	}
};

typedef MsgValue<uint32_t> Int;

int main(int argc, char* argv[])
{
	char buff[100] = { 0 };
	Int myInt;
	myInt = 100;
	if (myInt == 100)
	{
		std::cout << "if (myInt == 100)" << std::endl;
	}

	system("pause");
}