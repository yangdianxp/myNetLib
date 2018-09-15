#ifndef __ARISTOTLE_H__ 
#define __ARISTOTLE_H__


template<class _Type, int _Size>
class aristotle
{	
public:
	typedef _Type* __ptr;
	typedef __ptr* __pptr;
	aristotle() 
	{
		m_begin = m_end = m_ptr;
	}
	void push_back(__ptr ptr)
	{
		*m_end++ = ptr;
	}
	void pop_front(__pptr ptr)
	{
		if (m_begin != ptr)			
		{
			for (__pptr it = begin(); it != end(); ++it)
			{
				if (it == ptr)
				{
					*it = NULL;
					break;
				}
			}
		}
		else
		{		
			while (m_begin != m_end)
			{
				*m_begin++ = NULL;				
				if ( *m_begin != NULL)
					break;
			}
		}
	}
	__pptr begin()const { return m_begin; }
	__pptr end()const { return m_end; }
private:
	__pptr m_begin;
	__pptr m_end;
	__ptr m_ptr[_Size];
};
#endif