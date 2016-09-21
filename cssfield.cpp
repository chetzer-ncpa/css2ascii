#include "cssfield.h"
#include <string>
#include <cstdlib>

NCPA::CSS::CSSField::CSSField( std::string key, std::string value, int fieldLength ) {
        _fieldName = key;
        _fieldContents = value;
        _fieldLength = fieldLength;
}

NCPA::CSS::CSSField::CSSField() {
        _fieldName = "";
        _fieldContents = "";
        _fieldLength = 0;
}

void NCPA::CSS::CSSField::set( std::string newValue ) {
        _fieldContents = newValue;
}

std::string NCPA::CSS::CSSField::key() const { return _fieldName; }
int NCPA::CSS::CSSField::size() const { return _fieldLength; }

std::string NCPA::CSS::CSSField::format() const {
        char formattedValue[ _fieldLength+1 ];
        sprintf(formattedValue,"%-*s",_fieldLength,_fieldContents.c_str());
        std::string s(formattedValue);
        return s;
}

std::string NCPA::CSS::CSSField::asString() const {
        return deblank( _fieldContents );
}

char NCPA::CSS::CSSField::asChar() const {
        return _fieldContents[0];
}

int NCPA::CSS::CSSField::asInt() const {
        return std::atoi( _fieldContents.c_str() );
}

double NCPA::CSS::CSSField::asFloat() const {
        return std::atof( _fieldContents.c_str() );
}

NCPA::CSS::CSSFloatField::CSSFloatField( std::string key, std::string value, int fieldLength, int precision ) {
        _fieldName = key;
        _value = std::atof( value.c_str() );
        _fieldLength = fieldLength;
        _precision = precision;
}

NCPA::CSS::CSSFloatField::CSSFloatField( std::string key, double value, int fieldLength, int precision ) {
        _fieldName = key;
        _value = value;
        _fieldLength = fieldLength;
        _precision = precision;
}

std::string NCPA::CSS::CSSFloatField::asString() const {
        std::string s( this->format() );
        return deblank(s);
}

double NCPA::CSS::CSSFloatField::asFloat() const { return _value; }
int NCPA::CSS::CSSFloatField::asInt() const { return (int)_value; }
char NCPA::CSS::CSSFloatField::asChar() const { return this->asString()[ 0 ]; }

std::string NCPA::CSS::CSSFloatField::format() const {
        char formattedValue[ _fieldLength+1 ];
        sprintf(formattedValue,"%*.*f",_fieldLength,_precision,_value);
        std::string s( formattedValue );
        return s;
}

void NCPA::CSS::CSSFloatField::set( std::string s ) { _value = std::atof( s.c_str() ); }
void NCPA::CSS::CSSFloatField::set( double d ) { _value = d; }

/*********************************************************************
 * CSSIntField
 *********************************************************************/
NCPA::CSS::CSSIntField::CSSIntField( std::string key, std::string value, int fieldLength ) {
        _fieldName = key;
        _value = std::atoi( value.c_str() );
        _fieldLength = fieldLength;
}

NCPA::CSS::CSSIntField::CSSIntField( std::string key, int value, int fieldLength ) {
        _fieldName = key;
        _value = value;
        _fieldLength = fieldLength;
}

std::string NCPA::CSS::CSSIntField::asString() const {
        std::string s( this->format() );
        return deblank(s);
}

double NCPA::CSS::CSSIntField::asFloat() const { return (double)_value; }
int NCPA::CSS::CSSIntField::asInt() const { return _value; }
char NCPA::CSS::CSSIntField::asChar() const { return this->asString()[ 0 ]; }

std::string NCPA::CSS::CSSIntField::format() const {
        char formattedValue[ _fieldLength + 1 ];
        sprintf(formattedValue,"%*d",_fieldLength,_value);
        std::string s( formattedValue );
        return s;
}

void NCPA::CSS::CSSIntField::set( std::string s ) { _value = std::atoi( s.c_str() ); }
void NCPA::CSS::CSSIntField::set( int d ) { _value = d; }

