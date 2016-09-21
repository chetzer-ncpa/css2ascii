#ifndef _UTIL_H_
#define _UTIL_H_
#include <string>

namespace util {
	float min( float *, int );
	float max( float *, int );
	std::string timeAsString( double d );
	bool fexists( const char *filename );
	std::string deblank( std::string orig );
}




#endif
