#ifndef __MSGTLV_H_20180906__
#define __MSGTLV_H_20180906__
#include <stdint.h>
#include <assert.h>
#include <string.h>
#pragma pack (push,1)   /*ָ��1�ֽڶ���*/
namespace protocol
{	
	class TLV
	{
	public:
		short m_tag;
		unsigned short m_length;
		char m_value[0];
	public:
		char* push_back(int count)
		{
			char* r = m_value + m_length;
			m_length += count;
			return r;
		}
		int tag() { return m_tag; }
		int size()const { return sizeof(TLV) + m_length; }	
		int length()const { return m_length;}	
		char* value(){return m_value;}
		void push_back(const char* other, int count)
		{
			if (count + (int)m_length < 0x10000)
			{
				memcpy(m_value + m_length, other, count);
				m_length += count;
			}
		}
		TLV(short t) : m_tag(t), m_length(0) {}		
	};

	template<class _Type, short _Tag>
	class PTLV
	{	
		TLV* tlv;			
	public:		
		PTLV() :tlv(NULL){  
			std::cout << "PTLV::PTLV()" << std::endl;
		}
		void operator<<(TLV* t) { 
			std::cout << "PTLV::void operator<<(TLV* t)" << std::endl;
			tlv = t; 
		}
		operator _Type*() { 
			std::cout << "PTLV::operator _Type*()" << std::endl;
			return (_Type*)tlv->m_value; 
		}
		_Type& operator[](int pos){
			std::cout << "PTLV::_Type& operator[](int pos)" << std::endl;
			if (tlv != NULL)
			{
				if (pos >=0 && pos < count())
				{
					_Type* buf = (_Type*)tlv->value();
					return buf[pos];
				}
			}
			throw(-1);
		}
 		int size()const { 
			std::cout << "PTLV::int size()const" << std::endl;
			return tlv != NULL ? tlv->size() : 0; 
		}
		int count()const { 
			std::cout << "PTLV::int count()const" << std::endl;
			return tlv != NULL ? tlv->length() / sizeof(_Type) : 0;
		}	

		static int tag() { 
			std::cout << "PTLV::static int tag()" << std::endl;
			return _Tag; 
		}
		void push_back(const _Type* other, int count)
		{
			std::cout << "PTLV::void push_back(const _Type* other, int count)" << std::endl;
			if (tlv != NULL)
			{
				tlv->push_back((const char*)other, count * sizeof(_Type));				
			}				
		}
		void push_back(const _Type& other)
		{
			std::cout << "PTLV::void push_back(const _Type& other)" << std::endl;
			if (tlv != NULL)
			{
				tlv->push_back((const char*)&other, sizeof(_Type));				
			}
		}
		_Type* push_back()
		{		
			std::cout << "PTLV::_Type* push_back()" << std::endl;
			if (tlv != NULL)
				return (_Type*)tlv->push_back(sizeof(_Type));
			static _Type error_protected;
			return &error_protected;
		}
	};

	template<short _Tag>
	struct String : public PTLV<char, _Tag> {};	
		
	
}
#pragma pack (pop)  

#endif