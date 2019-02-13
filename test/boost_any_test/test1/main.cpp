#include <iostream>
#include <string>
#include "boost/any.hpp" // for any
#include <assert.h>      // for assert
namespace bo = boost;
int main() {
	//  1. --- 构造函数 ---
	bo::any a;                      // default constructor
	bo::any b(a);                   // copy constructor
	bo::any c(11);                  // copy constructor
	bo::any d(std::string("hello"));
	bo::any m(std::move(std::string("world")));// move constructor
	bo::any f = 1;// int 型 // assignment constructor

	// 2. ----- 成员函数 --------
	// empty
	assert(a.empty());
	assert(b.empty());
	assert(!c.empty());
	assert(!d.empty());
	assert(!m.empty());
	assert(!f.empty());

	std::cout << "empty passed" << std::endl;

	// clear
	a.clear();
	b.clear();
	c.clear();
	d.clear();
	m.clear();
	f.clear();

	assert(a.empty());
	assert(b.empty());
	assert(c.empty());
	assert(d.empty());
	assert(m.empty());
	assert(f.empty());

	std::cout << "clear passed" << std::endl;

	std::cout << "-----------------------------" << std::endl;
	// swap
	a = 3;
	b = std::string("Boost.Any库");
	std::cout
		<< "a: " << bo::any_cast<int>(a) << '\n'
		<< "b: " << bo::any_cast<std::string>(b) << std::endl;

	a.swap(b);

	std::cout
		<< "--->after swap\n"
		<< "a: " << bo::any_cast<std::string>(a) << '\n'
		<< "b: " << bo::any_cast<int>(b) << std::endl;

	std::cout << "-----------------------------" << std::endl;
	// type
	std::cout << "a.type(): " << a.type().name() << std::endl;
	std::cout << "b.type(): " << b.type().name() << std::endl;
	std::cout << "-----------------------------" << std::endl;

	// any_cast 取值
	f = 3;
	std::cout << bo::any_cast<int> (f) << std::endl;

	try {
		// double型错误，会抛出异常
		std::cout << bo::any_cast<double> (f) << std::endl;
	}
	catch (bo::bad_any_cast &e) {
		std::cout << e.what() << std::endl;
	}

	std::cout << "如果是传引用，即使是类型不匹配时，也不会使程序崩溃！" << std::endl;
	// 类型不匹配，但passed-by-reference不会抛出异常，指定为空指针
	if (bo::any_cast<double>(&f) == nullptr) {
		std::cout << "bad any cast! any_cast<double> (&f)的值为： " << bo::any_cast<double> (&f) << std::endl;
	}

	std::cin.get();
}