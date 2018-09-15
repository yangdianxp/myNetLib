#ifndef __MSGPROTO_H_20180906__
#define __MSGPROTO_H_20180906__
#include <new>
#include "MsgValue.h"
#include "MsgTLV.h"
#include "Aristotle.h"

#pragma pack (push,1)
namespace protocol
{
#define MSG_BEGIN(_Class) struct _Class : protocol_common_function{	_Class(char* buffer, int count) : protocol_common_function(buffer, count) { init(); }
#define MSG_END() };
#define TLV_BEGIN(_Msg, _Tlv) _Msg._Tlv << _Msg.tlv_begin(_Msg._Tlv.tag())
#define TLV_END(_Msg) _Msg.tlv_end();
#define TLV_MEMBERS_MAX (64)

	class protocol_common_function 
	{		
		char* m_Buffer;		
		int m_Size;		
		aristotle<TLV, TLV_MEMBERS_MAX> m_aris;
	public:
		protocol_common_function(char* buffer, int size) : m_Buffer(buffer), m_Size(size) { }
		template<class _Type>
		bool loc(_Type& o)
		{
			int s = o.size();
			if (m_Size > s)
			{
				o.value = decltype(o.value)(m_Buffer);

				m_Buffer += s;
				m_Size -= s;				
				return true;
			}
			return false;
		}
		template<class _Type>
		bool pop(_Type& o)
		{
			for (auto it = m_aris.begin(); it != m_aris.end(); it++)
			{
				if ((*it)->tag() == o.tag())
				{
					o << *it;
					m_aris.pop_front(it);					
					return true;
				}
			}
			return false;	
		}
		TLV* tlv_begin(int t)
		{
			if (static_cast<size_t>(m_Size) >=  sizeof(TLV))
			{
				return  ::new (m_Buffer) TLV(t);
			}
			return NULL;
		}
		void tlv_end()
		{
			TLV* tlv = (TLV*)(m_Buffer);
			m_Buffer += tlv->size();
			m_Size -= tlv->size();
		}
		void analysis()
		{
			int pos = 0;
			while (m_Size - pos > 0)
			{
				TLV* tlv = (TLV*)(m_Buffer + pos);
				m_aris.push_back(tlv);
				pos += tlv->size();				
			}			
		}

	};	
};
#pragma pack (pop)  
#endif