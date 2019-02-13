#include <iostream>
#include <string>
#include "boost/any.hpp" // for any
#include <assert.h>      // for assert
namespace bo = boost;
int main() {
	//  1. --- ���캯�� ---
	bo::any a;                      // default constructor
	bo::any b(a);                   // copy constructor
	bo::any c(11);                  // copy constructor
	bo::any d(std::string("hello"));
	bo::any m(std::move(std::string("world")));// move constructor
	bo::any f = 1;// int �� // assignment constructor

	// 2. ----- ��Ա���� --------
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
	b = std::string("Boost.Any��");
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

	// any_cast ȡֵ
	f = 3;
	std::cout << bo::any_cast<int> (f) << std::endl;

	try {
		// double�ʹ��󣬻��׳��쳣
		std::cout << bo::any_cast<double> (f) << std::endl;
	}
	catch (bo::bad_any_cast &e) {
		std::cout << e.what() << std::endl;
	}

	std::cout << "����Ǵ����ã���ʹ�����Ͳ�ƥ��ʱ��Ҳ����ʹ���������" << std::endl;
	// ���Ͳ�ƥ�䣬��passed-by-reference�����׳��쳣��ָ��Ϊ��ָ��
	if (bo::any_cast<double>(&f) == nullptr) {
		std::cout << "bad any cast! any_cast<double> (&f)��ֵΪ�� " << bo::any_cast<double> (&f) << std::endl;
	}

	std::cin.get();
}