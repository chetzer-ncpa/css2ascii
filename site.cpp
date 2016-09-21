#include <sstream>
#include <iostream>
#include <map>
#include <vector>
#include <cstring>
#include "css_base.h"
#include "site.h"




using NCPA::CSS::deblank;

NCPA::CSS::Site::Site() {
	initialize();
	this->LOAD_ERROR = false;
}

void NCPA::CSS::Site::initialize() {
	_contents["sta"] = new NCPA::CSS::CSSField("sta","",6);
	_contents["ondate"] = new NCPA::CSS::CSSIntField("ondate",-1,8);
	_contents["offdate"] = new NCPA::CSS::CSSIntField("offdate",-1,8);
	_contents["lat"] = new NCPA::CSS::CSSFloatField("lat",-999.0,9,4);
	_contents["lon"] = new NCPA::CSS::CSSFloatField("lon",-999.0,9,4);
	_contents["elev"] = new NCPA::CSS::CSSFloatField("elev",-999.0,9,4);
	_contents["staname"] = new NCPA::CSS::CSSField("staname","",50);
	_contents["statype"] = new NCPA::CSS::CSSField("statype","",4);
	_contents["refsta"] = new NCPA::CSS::CSSField("refsta","-",6);
	_contents["dnorth"] = new NCPA::CSS::CSSFloatField("dnorth",0.0,9,4);
	_contents["deast"] = new NCPA::CSS::CSSFloatField("deast",0.0,9,4);
	_contents["lddate"] = new NCPA::CSS::CSSField("lddate","",17);
}

NCPA::CSS::Site::Site( std::string s ) {
        initialize();
    LOAD_ERROR = !(this->parseLine( s ));
}

NCPA::CSS::Site::Site( char *line ) {
        initialize();
        LOAD_ERROR = !(this->parseLine( line ));
}

NCPA::CSS::Site::Site( std::istream *instream, int i ) {
        initialize();
    LOAD_ERROR = !(this->readLine( instream, i ));
}

NCPA::CSS::Site::Site( std::istream *instream ) {
        initialize();
    LOAD_ERROR = !(this->readLine( instream ));
}

std::vector< std::string > NCPA::CSS::Site::fieldNames() const {
        std::vector< std::string > v;
        v.reserve(12);
	v.push_back("sta");
	v.push_back("ondate");
	v.push_back("offdate");
	v.push_back("lat");
	v.push_back("lon");
	v.push_back("elev");
	v.push_back("staname");
	v.push_back("statype");
	v.push_back("refsta");
	v.push_back("dnorth");
	v.push_back("deast");
	v.push_back("lddate");
	return v;
}

unsigned int NCPA::CSS::Site::getLineSize() { return 159; }

bool NCPA::CSS::Site::operator==( const Site &other) const {
    if (getField("sta")->asString().compare( other.getField("sta")->asString() ) != 0)
        return false;
    if (getField("ondate")->asFloat() != other.getField("ondate")->asFloat() )
        return false;
    return true;
}

bool NCPA::CSS::Site::operator!=( const Site &other ) const {
    return !(*this == other);
}

