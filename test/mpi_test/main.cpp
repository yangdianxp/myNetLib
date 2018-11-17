#include <boost/mpi.hpp>
#include <iostream>
#include <string>
#include <functional>
#include <boost/serialization/string.hpp>
namespace mpi = boost::mpi;

int main()
{
	mpi::environment env;
	mpi::communicator world;

	std::string names[10] = { "zero ", "one ", "two ", "three ",
							  "four ", "five ", "six ", "seven ",
							  "eight ", "nine " };

	std::string result;
	reduce(world,
		world.rank() < 10 ? names[world.rank()]
		: std::string("many "),
		result, std::plus<std::string>(), 0);

	if (world.rank() == 0)
		std::cout << "The result is " << result << std::endl;

	return 0;
}
#if 0
#include <boost/mpi.hpp>
#include <iostream>
#include <cstdlib>
namespace mpi = boost::mpi;

int main()
{
	mpi::environment env;
	mpi::communicator world;

	std::srand(time(0) + world.rank());
	int my_number = std::rand();

	if (world.rank() == 0) {
		int minimum;
		reduce(world, my_number, minimum, mpi::minimum<int>(), 0);
		std::cout << "The minimum value is " << minimum << std::endl;
	}
	else {
		reduce(world, my_number, mpi::minimum<int>(), 0);
	}

	return 0;
}
#endif
#if 0
#include <boost/mpi.hpp>
#include <boost/mpi/collectives.hpp>
#include <iostream>
#include <cstdlib>
#include <vector>

namespace mpi = boost::mpi;

int main(int argc, char* argv[])
{
	mpi::environment env(argc, argv);
	mpi::communicator world;

	std::srand(time(0) + world.rank());
	std::vector<int> all;
	int mine = -1;
	if (world.rank() == 0) {
		all.resize(world.size());
		std::generate(all.begin(), all.end(), std::rand);
	}
	mpi::scatter(world, all, mine, 0);
	for (int r = 0; r < world.size(); ++r) {
		world.barrier();
		if (r == world.rank()) {
			std::cout << "Rank " << r << " got " << mine << '\n';
		}
	}
	return 0;
}
#endif
#if 0
#include <boost/mpi.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
namespace mpi = boost::mpi;

int main()
{
	mpi::environment env;
	mpi::communicator world;

	std::srand(time(0) + world.rank());
	int my_number = std::rand();
	if (world.rank() == 0) {
		std::vector<int> all_numbers;
		gather(world, my_number, all_numbers, 0);
		for (int proc = 0; proc < world.size(); ++proc)
			std::cout << "Process #" << proc << " thought of "
			<< all_numbers[proc] << std::endl;
	}
	else {
		gather(world, my_number, 0);
	}

	return 0;
}
#endif
#if 0
#include <boost/mpi.hpp>
#include <iostream>
#include <string>
#include <boost/serialization/string.hpp>
namespace mpi = boost::mpi;

int main()
{
	mpi::environment env;
	mpi::communicator world;

	std::string value;
	if (world.rank() == 0) {
		value = "Hello, World!";
	}

	broadcast(world, value, 0);

	std::cout << "Process #" << world.rank() << " says " << value
		<< std::endl;
	return 0;
}
#endif
#if 0
#include <boost/mpi.hpp>
#include <iostream>
#include <string>
#include <boost/serialization/string.hpp>
namespace mpi = boost::mpi;

int main()
{
	mpi::environment env;
	mpi::communicator world;

	if (world.rank() == 0) {
		mpi::request reqs[2];
		std::string msg, out_msg = "Hello";
		reqs[0] = world.isend(1, 0, out_msg);
		reqs[1] = world.irecv(1, 1, msg);
		mpi::wait_all(reqs, reqs + 2);
		std::cout << msg << "!" << std::endl;
	}
	else {
		mpi::request reqs[2];
		std::string msg, out_msg = "world";
		reqs[0] = world.isend(0, 1, out_msg);
		reqs[1] = world.irecv(0, 0, msg);
		mpi::wait_all(reqs, reqs + 2);
		std::cout << msg << ", ";
	}

	return 0;
}
#endif

#if 0
#include <boost/mpi.hpp>
#include <iostream>
#include <string>
#include <boost/serialization/string.hpp>
namespace mpi = boost::mpi;

int main()
{
	mpi::environment env;
	mpi::communicator world;

	if (world.rank() == 0) {
		world.send(1, 0, std::string("Hello"));
		std::string msg;
		world.recv(1, 1, msg);
		std::cout << msg << "!" << std::endl;
  }
	else {
		std::string msg;
		world.recv(0, 0, msg);
		std::cout << msg << ", ";
		std::cout.flush();
		world.send(0, 1, std::string("world"));
	}

	return 0;
}
#endif

#if 0
#include <boost/mpi/environment.hpp>
#include <boost/mpi/communicator.hpp>
#include <iostream>
namespace mpi = boost::mpi;

int main()
{
	mpi::environment env;
	mpi::communicator world;
	std::cout << "I am process " << world.rank() << " of " << world.size()
		<< "." << std::endl;
	return 0;
}
#endif

#if 0

#include <mpi.h>
#include <iostream>

int main(int argc, char* argv[])
{
	MPI_Init(&argc, &argv);

	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	if (rank == 0) {
		int value = 17;
		int result = MPI_Send(&value, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
		if (result == MPI_SUCCESS)
			std::cout << "Rank 0 OK!" << std::endl;
	}
	else if (rank == 1) {
		int value;
		int result = MPI_Recv(&value, 1, MPI_INT, 0, 0, MPI_COMM_WORLD,
			MPI_STATUS_IGNORE);
		if (result == MPI_SUCCESS && value == 17)
			std::cout << "Rank 1 OK!" << std::endl;
	}
	MPI_Finalize();
	return 0;
}

#endif