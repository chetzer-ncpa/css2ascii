#include "css_base.h"
#include <ctime>
#include <cstdio>
#include <cmath>

std::string NCPA::CSS::deblank(std::string orig) {
	//cout << "Original String: " << orig << endl;
	int index = orig.length();
	while (orig[(int)--index] == ' ') ;
	std::string temp = orig.substr(0,index+1);
	index = -1;
	while (temp[++index] == ' ') ;
	return temp.substr(index);
}

std::string NCPA::CSS::formatLddate( double d ) {
	time_t temptime = (time_t)d;
	tm* uttime = std::gmtime( &temptime );

	char* holder = new char[ 18 ];
	std::sprintf(holder,"%02d/%02d/%02d %02d:%02d:%02d",
		uttime->tm_mon+1, uttime->tm_mday, (int)std::fmod((double)uttime->tm_year,100.0),
		uttime->tm_hour, uttime->tm_min, uttime->tm_sec );
	std::string s = holder;
	return s;
}

