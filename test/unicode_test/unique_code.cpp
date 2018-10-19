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
	int temp = m_max - m_min;
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
	if (m_index == UINT32_MAX)
	{
		m_index = index;
	}
}

bool unique_code::empty()
{
	return (m_index == UINT32_MAX);
}

void unique_code::change_index()
{
	std::size_t max_index = m_max - m_min;
	std::size_t unit_index = m_index / bitset_unit_len;
	std::size_t unit_max = max_index / bitset_unit_len;
	auto it_index = m_bitset.find(unit_index);
	it_index->second.set(m_index % bitset_unit_len);
	bool is_find = false;
	auto fn = [&, this](decltype(it_index) it_begin, decltype(it_index) it_end)
	{
		for (auto it = it_begin; it != it_end; ++it, ++unit_index)
		{
			if (unit_index == unit_max)
			{
				int end = max_index % bitset_unit_len;
				for (int i = 0; i <= end; ++i)
				{
					if (!it->second.test(i))
					{
						m_index = unit_index * bitset_unit_len + i;
						return true;
					}
				}
			} else if (!it->second.all())
			{
				for (std::size_t i = 0; i < bitset_unit_len; ++i)
				{
					if (!it->second.test(i))
					{
						m_index = unit_index * bitset_unit_len + i;
						return true;
					}
				}
			}
		}
		return false;
	};
	if (!fn(it_index, m_bitset.end()))
	{
		if (unit_index > 1)
		{
			unit_index = 0;
			if (!fn(m_bitset.begin(), it_index))
			{
				m_index = UINT32_MAX;
			}
		}
		else {
			m_index = UINT32_MAX;
		}
	}
}
