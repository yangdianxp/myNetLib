#define BOOST_TEST_MODULE example
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(test_suite)

BOOST_AUTO_TEST_CASE(test_case1)
{
	BOOST_ERROR("some error 1");
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_CASE(test_case_on_file_scope)
{
	BOOST_TEST(true);
}

BOOST_AUTO_TEST_SUITE(test_suite)

BOOST_AUTO_TEST_CASE(test_case2)
{
	BOOST_ERROR("some error 2");
}

BOOST_AUTO_TEST_SUITE_END()



#if 0

#define BOOST_TEST_MODULE example
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(test_suite1)

BOOST_AUTO_TEST_CASE(test_case1)
{
	BOOST_TEST_WARN(sizeof(int) < 4U);
}

BOOST_AUTO_TEST_CASE(test_case2)
{
	BOOST_TEST_REQUIRE(1 == 2);
	BOOST_FAIL("Should never reach this line");
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(test_suite2)

BOOST_AUTO_TEST_CASE(test_case3)
{
	BOOST_TEST(true);
}

BOOST_AUTO_TEST_CASE(test_case4)
{
	BOOST_TEST(false);
}

BOOST_AUTO_TEST_SUITE_END()

#endif

#if 0
#define BOOST_TEST_MODULE example
#include <boost/test/included/unit_test.hpp>
#include <boost/mpl/list.hpp>

typedef boost::mpl::list<int, long, unsigned char> test_types;

BOOST_AUTO_TEST_CASE_TEMPLATE(my_test, T, test_types)
{
	BOOST_TEST(sizeof(T) == (unsigned)4);
}

typedef std::tuple<int, long, unsigned char> test_types_w_tuples;

BOOST_AUTO_TEST_CASE_TEMPLATE(my_tuple_test, T, test_types_w_tuples)
{
	BOOST_TEST(sizeof(T) == (unsigned)4);
}

#endif


#if 0

#define BOOST_TEST_MODULE example67
#include <boost/test/included/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>
#include <sstream>

namespace bdata = boost::unit_test::data;

// Generates a Fibonacci sequence
std::vector<float> fibonacci() {
	std::vector<float> ret(8);
	ret[0] = 0;
	ret[1] = 1;

	for (std::size_t s(2); s < ret.size(); s++)
	{
		ret[s] = ret[s - 1] + ret[s - 2];
	}
	return ret;
}

BOOST_DATA_TEST_CASE(
	test1,
	bdata::make(fibonacci()),
	array_element)
{
	std::cout << "test 1: "
		<< array_element
		<< std::endl;
	BOOST_TEST(array_element <= 13);
}


// Generates a map from a vector
std::map<std::string, float> vect_2_str(std::vector<float> v)
{
	std::map<std::string, float> out;
	for (std::size_t s(0); s < v.size(); s++)
	{
		std::ostringstream o;
		o << v[s];
		out[o.str()] = v[s];
	}
	return out;
}

typedef std::pair<const std::string, float> pair_map_t;
BOOST_TEST_DONT_PRINT_LOG_VALUE(pair_map_t)

BOOST_DATA_TEST_CASE(
	test2,
	bdata::make(vect_2_str(fibonacci())),
	array_element)
{
	std::cout << "test 2: \""
		<< array_element.first << "\", "
		<< array_element.second
		<< std::endl;
	BOOST_TEST(array_element.second <= 13);
}

#endif
