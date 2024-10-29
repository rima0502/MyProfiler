#include <random>
#include "Profiler.h"

int Test1()
{
	DEBUG_PROFILER_START(__FUNCTION_NAME__);

	int r = std::rand() / 2;

	DEBUG_PROFILER_END;

	return r;
}

int Test2()
{
	DEBUG_PROFILER_START(__FUNCTION_NAME__);

	int r = std::rand();

	for (int i = 0; i < r; i++)
	{
		r = std::rand();
	}

	DEBUG_PROFILER_END;

	return r;
}

int main()
{
	DEBUG_PROFILER_START(__FUNCTION_NAME__);

	for (int i = 0; i < 100; i++)
	{
		DEBUG_PROFILER_START("Loop iteration " + std::to_string(i));

		Test1();
		Test2();

		DEBUG_PROFILER_END;
	}

	DEBUG_PROFILER_END;

	DEBUG_PROFILER_DUMP;
	DEBUG_PROFILER_DELETE;

	return 0;
}