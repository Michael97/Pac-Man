#pragma once
#include <iostream>
#include <assert.h>


//////////////////////////////////////////////////////////////////////////
//Define a bit of a better assert that gives us some better information
//back when something goes oops.
//////////////////////////////////////////////////////////////////////////
#ifdef _WIN32
#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#elif
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#endif // _WIN32



#ifndef NDEBUG
#   define ASSERT(condition, message, file, line) \
	do { \
		if (! (condition)) { \
			std::cerr << "Assertion: `" message "`\nFailed in " << file \
					  << " line " << line << ": " << std::endl; \
					  abort();\
				} \
		} while (false)
#else
#   define ASSERT(condition, message, file, line) do { } while (false)
#endif
