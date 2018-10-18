#include "unique_code.h"

unique_code::unique_code()
{
	init(m_min, m_max);
}

unique_code::unique_code(uint32_t min, uint32_t max)
{
	init(min, max);
}

void unique_code::init(uint32_t min, uint32_t max)
{
	m_min = min;
	m_max = max;
	int temp = m_max - m_min + 1;
	int unit_cnt = temp / bitset_unit_len;
	for (int i = 0; i <= unit_cnt; i++)
	{
		m_bitset.insert(make_pair(i, std::bitset<bitset_unit_len>()));
	}
}

uint32_t unique_code::get()
{
	if (m_index > m_max)
	{
		return 0;
	}
	uint32_t ret_value = m_index + m_min;
	change_index();
	return ret_value;
}

void unique_code::del(uint32_t value)
{
	int index = value - m_min;
	m_bitset[index / bitset_unit_len].reset(index % bitset_unit_len);
}

bool unique_code::empty()
{
	auto it_end = m_bitset.end();
	for (auto it = m_bitset.begin(); it != it_end; ++it)
	{
		if (!it->second.all())
		{
			return false;
		}
	}
	return true;
}

void unique_code::change_index()
{
	m_bitset[m_index / bitset_unit_len].set(m_index % bitset_unit_len);
	std::size_t unit_cnt = 0;
	auto it_end = m_bitset.end();
	for (auto it = m_bitset.begin(); it != it_end; ++it, ++unit_cnt)
	{
		if (!it->second.all())
		{
			for (std::size_t i = 0; i < bitset_unit_len; ++i)
			{
				if (!it->second.test(i))
				{
					m_index = unit_cnt * bitset_unit_len + i;
					return;
				}
			}
		}
	}
}
