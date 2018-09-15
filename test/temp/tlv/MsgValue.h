#ifndef __MSGVALUE_H__
#define __MSGVALUE_H__
#include <iostream>
#include <stdint.h>
#include<assert.h>
#pragma pack (push,1)   /*ָ��1�ֽڶ���*/
namespace protocol
{
	template <class _Type, int _Count = 1>
	struct MsgValue
	{
		_Type* value;
		int size()const { 
			std::cout << "int size()" << std::endl;
			return sizeof(_Type) * _Count; 
		}
		char* end()const { 
			std::cout << "char* end()" << std::endl;
			return (char*)(value + _Count); 
		}
		operator _Type()const { 
			std::cout << "operator _Type()" << std::endl;
			return *value; 
		}
		operator _Type*()const {
			std::cout << "operator _Type*()" << std::endl;
			return value; 
		}
		void operator = (const _Type&other) { 
			std::cout << "operator = (const _Type&other)" << std::endl;
			assert(_Count == 1);
			*value = other;
		}
		_Type& operator[](int pos) {
			std::cout << "operator[](int pos)" << std::endl;
			assert(pos >= 0);
			if (pos < _Count)
				return value[pos];
			throw(-1);
		}
	};

	typedef MsgValue<uint32_t> Int;
	typedef MsgValue<uint16_t> Short;
	typedef MsgValue<uint64_t> Long;
	typedef MsgValue<char, 20> IP;
	//typedef MsgValue<char> Char;
};
#pragma pack (pop)  
#endif