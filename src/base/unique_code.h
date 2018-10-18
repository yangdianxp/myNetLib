#ifndef __UNIQUE_CODE_H__
#define __UNIQUE_CODE_H__
#include <bitset>
#include <map>

class unique_code
{
	enum {
		bitset_unit_len = 1000
	};
public:
	unique_code();
	unique_code(uint32_t min, uint32_t max);
	void init(uint32_t min, uint32_t max);
	uint32_t get();
	void del(uint32_t value);
	bool empty();
	
private:
	void change_index();

	uint32_t m_min = 1;
	uint32_t m_max = bitset_unit_len;
	uint32_t m_index = 0;
	std::map<int, std::bitset<bitset_unit_len>> m_bitset;
};

#endif
