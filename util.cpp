#include <cstdio>
#include <cmath>
#include <ctime>
#include <fstream>
#include "util.h"

float util::max( float *vals, int size ) {

	float maxval = vals[ 0 ];
	for (int i = 1; i < size; i++) {
		maxval = vals[i] > maxval ? vals[ i ] : maxval;
	}
	return maxval;
}

float util::min( float *vals, int size ) {

	float minval = vals[ 0 ];
	for (int i = 1; i < size; i++) {
		minval = vals[i] < minval ? vals[ i ] : minval;
	}
	return minval;
}

std::string util::timeAsString(double d) {
    time_t temptime = (time_t)d;
    tm* uttime = std::gmtime( &temptime );
    double ipart, fpart;
    fpart = std::modf( d, &ipart);

    char* holder = new char[ 28 ];
    std::sprintf(holder,"%4d-%02d-%02d %02d:%02d:%02d.%03d GMT",
            uttime->tm_year+1900, uttime->tm_mon+1, uttime->tm_mday,
            uttime->tm_hour, uttime->tm_min, uttime->tm_sec,
            (int)(round(fpart * 1000)) );
    std::string s = holder;
    return s;
}

bool util::fexists( const char *filename ) {
	std::ifstream ifile( filename );
	return ifile.good();
}

std::string util::deblank( std::string orig ) {
        int index = orig.length();
        while (orig[(int)--index] == ' ') ;
        std::string temp = orig.substr(0,index+1);
        index = -1;
        while (temp[++index] == ' ') ;
        return temp.substr(index);
}

