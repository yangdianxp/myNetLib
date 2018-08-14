#include <iostream>

int main(int argc, char* argv[])
{


	return 0;
}

#if 0
boost::asio::associated_executor_t<Handler> a = boost::asio::get_associated_executor(h);
class my_handler
{
public:
	// Custom implementation of Executor type requirements.
	typedef my_executor executor_type;

	// Return a custom executor implementation.
	executor_type get_executor() const noexcept
	{
		return my_executor();
	}

	void operator()() { ... }
};

struct my_handler
{
	void operator()() { ... }
};

namespace boost {
	namespace asio {

		template <class Executor>
		struct associated_executor<my_handler, Executor>
		{
			// Custom implementation of Executor type requirements.
			typedef my_executor type;

			// Return a custom executor implementation.
			static type get(const my_handler&,
				const Executor& = Executor()) noexcept
			{
				return my_executor();
			}
		};

	}
} // namespace boost::asio

#endif