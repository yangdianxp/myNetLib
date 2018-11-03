#ifndef __HASH_FUNCTION_H__
#define __HASH_FUNCTION_H__

#include<functional>

template<typename T>
inline void hash_combine(size_t &seed, const T& val) {
	seed ^= std::hash<T>()(val) + 0x9e3779b9 + (seed << 6) + (seed >> 2);  //0x9e3779b9
}
//auxiliary generic functions
template<typename T>
inline void hash_val(size_t &seed, const T & val) {
	hash_combine(seed, val);
}

template<typename T, typename... Types>
inline void hash_val(size_t & seed, const T& val, const Types &...args) //逐一取val改变seed（pass by reference）
{
	hash_combine(seed, val);
	hash_val(seed, args...);
}
//auxiliary generic function
template<typename... Types>
inline size_t hash_val(const Types& ...arg) //seed最终就被视为hash code
{
	size_t seed = 0;
	hash_val(seed, arg...);
	return seed;
}

#endif