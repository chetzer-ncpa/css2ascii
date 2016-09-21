#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include <istream>
#include <sstream>
#include <cstring>
#include "css_base.h"
#include "wfdisc.h"
#include "util.h"

using NCPA::CSS::deblank;

NCPA::CSS::Wfdisc::Wfdisc()
{
	initialize();
	this->LOAD_ERROR = false;

}

void NCPA::CSS::Wfdisc::initialize() {
	_contents[ "sta" ] = new NCPA::CSS::CSSField("sta","",6);
        _contents[ "chan" ] = new NCPA::CSS::CSSField("chan","",8);
        _contents[ "time" ] = new NCPA::CSS::CSSFloatField("time",-9999999999.999,17,5);
        _contents[ "wfid" ] = new NCPA::CSS::CSSIntField("wfid",-1,8);
        _contents[ "chanid" ] = new NCPA::CSS::CSSIntField("chanid",-1,8);
        _contents[ "jdate" ] = new NCPA::CSS::CSSIntField("jdate",-1,8);
        _contents[ "endtime" ] = new NCPA::CSS::CSSFloatField("endtime",9999999999.999,17,5);
        _contents[ "nsamp" ] = new NCPA::CSS::CSSIntField("nsamp",0,8);
        _contents[ "samprate" ] = new NCPA::CSS::CSSFloatField("samprate",0.0,11,7);
        _contents[ "calib" ] = new NCPA::CSS::CSSFloatField("calib",1.0,16,6);

        _contents[ "calper" ] = new NCPA::CSS::CSSFloatField("calper",1.0,16,6);

        _contents[ "instype" ] = new NCPA::CSS::CSSField( "instype", "-", 6 );
        _contents[ "segtype" ] = new NCPA::CSS::CSSField( "segtype", "-", 1 );
        _contents[ "datatype" ] = new NCPA::CSS::CSSField( "datatype", "", 2 );
        _contents[ "clip" ] = new NCPA::CSS::CSSField( "clip", "-", 1 );
        _contents[ "dir" ] = new NCPA::CSS::CSSField( "dir", "", 64 );
        _contents[ "dfile" ] = new NCPA::CSS::CSSField( "dfile", "", 32 );
        _contents[ "foff" ] = new NCPA::CSS::CSSIntField("foff",0,10);
        _contents[ "commid" ] = new NCPA::CSS::CSSIntField("commid",-1,8);
        _contents[ "lddate" ] = new NCPA::CSS::CSSField("lddate","",17);
}

NCPA::CSS::Wfdisc::Wfdisc( std::string s ) {
	initialize();
    LOAD_ERROR = !(this->parseLine( s ));
}

NCPA::CSS::Wfdisc::Wfdisc( char *line ) {
	initialize();
	LOAD_ERROR = !(this->parseLine( line ));
}

NCPA::CSS::Wfdisc::Wfdisc( std::istream *instream, int i ) {
	initialize();
    LOAD_ERROR = !(this->readLine( instream, i ));
}

NCPA::CSS::Wfdisc::Wfdisc( std::istream *instream ) {
	initialize();
    LOAD_ERROR = !(this->readLine( instream ));
}

std::vector< std::string > NCPA::CSS::Wfdisc::fieldNames() const {
	std::vector< std::string > v;
	v.reserve(20);
	v.push_back("sta");
	v.push_back("chan");
	v.push_back("time");
	v.push_back("wfid");
	v.push_back("chanid");
	v.push_back("jdate");
	v.push_back("endtime");
	v.push_back("nsamp");
	v.push_back("samprate");
	v.push_back("calib");
	v.push_back("calper");
	v.push_back("instype");
	v.push_back("segtype");
	v.push_back("datatype");
	v.push_back("clip");
	v.push_back("dir");
	v.push_back("dfile");
	v.push_back("foff");
	v.push_back("commid");
	v.push_back("lddate");
	return v;
}

unsigned int NCPA::CSS::Wfdisc::getLineSize() { return 283; }

bool NCPA::CSS::Wfdisc::isContiguousWith( const Wfdisc &other ) const {

    // First, check to see whether they have the same sta, chan, and samprate values
    if (this->getField("sta")->asString().compare( other.getField("sta")->asString() ) != 0) {
        return false;
    }

    if (this->getField("chan")->asString().compare( other.getField("chan")->asString() ) != 0) {
        return false;
    }

    if ((int)floor(this->getField("samprate")->asFloat() * 1000000.0 + 0.5) !=
        (int)floor(other.getField("samprate")->asFloat() * 1000000.0 + 0.5)) {
        return false;
    }

    // Now we compare the starting time of one with the ending time of the other
    const Wfdisc *first, *second;
    if (this->getField("time")->asFloat() < other.getField("time")->asFloat()) {
        first = this;
        second = &other;
    } else {
        first = &other;
        second = this;
    }

    // If the endtime of the first wfdisc is invalid, calculate the correct one
    double firstEndTime = first->getField("endtime")->asFloat();
    if (firstEndTime >= 9999999999.0) {
        firstEndTime =  first->getField("time")->asFloat() + (first->getField("nsamp")->asFloat() - 1.0)
                           / first->getField("samprate")->asFloat();
    }

    double dt = second->getField("time")->asFloat() - first->getField("endtime")->asFloat();
    if (dt < 0) { return false; }    // segments overlap

    // Check agreement to the millisecond
    double dsamp = 1.0 / this->getField("samprate")->asFloat() + 0.001;  // add one millisecond slop factor
    if (dt > dsamp) {
        return false;
    }
    return true;
}

bool NCPA::CSS::Wfdisc::operator==( const Wfdisc &other) const {
    if (getField("sta")->asString().compare( other.getField("sta")->asString() ) != 0)
        return false;
    if (getField("chan")->asString().compare( other.getField("chan")->asString() ) != 0)
        return false;
    if (fabs(getField("time")->asFloat() - other.getField("time")->asFloat()) > 0.001)
        return false;
    if (fabs(getField("samprate")->asFloat() - other.getField("samprate")->asFloat()) > 0.01)
        return false;
    return true;
}

bool NCPA::CSS::Wfdisc::operator!=( const Wfdisc &other ) const {
    return !(*this == other);
}

bool NCPA::CSS::Wfdisc::operator>( const Wfdisc &other ) const {
    // First, test for equality
    if (*this == other)
        return false;
    if (getField("sta")->asString().compare( other.getField("sta")->asString() ) != 0)
        return getField("sta")->asString().compare( other.getField("sta")->asString() ) > 0 ? true : false;
    if (getField("chan")->asString().compare( other.getField("chan")->asString() ) != 0)
        return getField("chan")->asString().compare( other.getField("chan")->asString() ) > 0 ? true : false;
    if (fabs(getField("time")->asFloat() - other.getField("time")->asFloat()) > 0.001)
        return (getField("time")->asFloat() > other.getField("time")->asFloat());
    if (fabs(getField("samprate")->asFloat() - other.getField("samprate")->asFloat()) > 0.01)
        return (getField("samprate")->asFloat() > other.getField("samprate")->asFloat());
    return false;
}

bool NCPA::CSS::Wfdisc::operator<( const Wfdisc &other ) const {
    // First, test for equality
    if (*this == other)
        return false;
    if (getField("sta")->asString().compare( other.getField("sta")->asString() ) != 0)
        return getField("sta")->asString().compare( other.getField("sta")->asString() ) < 0 ? true : false;
    if (getField("chan")->asString().compare( other.getField("chan")->asString() ) != 0)
        return getField("chan")->asString().compare( other.getField("chan")->asString() ) < 0 ? true : false;
    if (fabs(getField("time")->asFloat() - other.getField("time")->asFloat()) > 0.001)
        return (getField("time")->asFloat() < other.getField("time")->asFloat());
    if (fabs(getField("samprate")->asFloat() - other.getField("samprate")->asFloat()) > 0.01)
        return (getField("samprate")->asFloat() < other.getField("samprate")->asFloat());
    return false;
}

bool NCPA::CSS::Wfdisc::operator>=( const Wfdisc &other ) const {
    return ((*this > other) || (*this == other));
}

bool NCPA::CSS::Wfdisc::operator<=( const Wfdisc &other ) const {
    return ((*this < other) || (*this == other));
}

bool NCPA::CSS::Wfdisc::fieldNameIsValid( const std::string teststring ) const {

	std::vector< std::string > fields = fieldNames();

	for (std::vector< std::string >::iterator i = fields.begin(); i != fields.end(); i++) {
		if (*i == teststring) {
			return true;
		}
	}
	return false;
}

