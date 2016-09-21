#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
//#include <cctype>
//#include <cmath>
#include <cstring>
//#include <ctime>
#include <map>
#include "cssstructure.h"
#include "css_base.h"

void NCPA::CSS::CSSStructure::appendToFile( std::ofstream* outstream ) {
    char* line = new char[this->getLineSize()+1];
    this->formatLine(line);
    outstream->write( line, this->getLineSize() );
    delete line;
}

void NCPA::CSS::CSSStructure::appendToFile(std::string filename) {
    std::ofstream outstream( filename.c_str(), std::ios_base::app | std::ios_base::out );
    this->appendToFile( &outstream );
}

bool NCPA::CSS::CSSStructure::readLine( std::istream* infile, int linesToSkip ) {
    std::string line;
    for (int i = 0; i < linesToSkip+1; i++) {
        std::getline(*infile,line);
    }

    if (line.length() == this->getLineSize()) {
        return parseLine(line);
    } else {
        return false;
    }
}

bool NCPA::CSS::CSSStructure::readLineFromFile( std::string filename, int linesToSkip ) {
    std::ifstream* infile = new std::ifstream( filename.c_str(), std::ios_base::in );
    bool tf = this->readLine( infile, linesToSkip );
    delete infile;
    return tf;
}

bool NCPA::CSS::CSSStructure::readLine(std::istream* infile) {
    return this->readLine(infile, 0);
}

bool NCPA::CSS::CSSStructure::readLineFromFile(std::string filename) {
    return this->readLineFromFile(filename,0);
}

bool NCPA::CSS::CSSStructure::error() {
    return LOAD_ERROR;
}

NCPA::CSS::CSSField * NCPA::CSS::CSSStructure::getField( std::string fieldName ) const {
	std::map<std::string,NCPA::CSS::CSSField *>::const_iterator it = _contents.find( fieldName );
	if (it == _contents.end()) {
		return (NCPA::CSS::CSSField *)0;
	} else {
		return it->second;
	}
}

NCPA::CSS::CSSField * NCPA::CSS::CSSStructure::getField( const char *fieldName ) const {
    std::string sss( fieldName );
    return this->getField( sss );
}

void NCPA::CSS::CSSStructure::printSummary( std::ostream* out ) const {

        std::vector< std::string > fields = fieldNames();

        std::ios_base::fmtflags oldflags = out->flags( std::ios::fixed );
        for (std::vector< std::string >::iterator i = fields.begin();
                        i != fields.end(); i++) {
                *out << *i << ":  " << this->getField(*i)->asString() << std::endl;
        }
        out->flags( oldflags );
}

void NCPA::CSS::CSSStructure::printSummary() const {
	this->printSummary( &std::cout );
}

bool NCPA::CSS::CSSStructure::parseLine( char *line ) {
        std::string s = line;
        return this->parseLine( s );
}

bool NCPA::CSS::CSSStructure::parseLine( std::string s ) {

        std::vector< std::string > fields = fieldNames();
        int runningTotal = 0;
        for (std::vector< std::string >::iterator i = fields.begin();
                        i != fields.end(); i++) {
                NCPA::CSS::CSSField *field = this->getField( *i );
                field->set( s.substr( runningTotal, field->size() ) );
                runningTotal += field->size() + 1;
        }

        return true;
}

void NCPA::CSS::CSSStructure::formatLine( char* line ) {

        std::vector< std::string > fields = fieldNames();
        std::ostringstream oss;

        for (std::vector< std::string >::iterator i = fields.begin();
                        i != fields.end(); i++) {
                oss << this->getField( *i )->format();
                if (i+1 != fields.end()) {
                        oss << " ";
                }
        }

        std::strncpy( line, oss.str().c_str(), this->getLineSize() );
        line[ this->getLineSize() ] = '\0';
}

NCPA::CSS::CSSStructure::~CSSStructure() {
        for (std::map<std::string,NCPA::CSS::CSSField *>::iterator i = _contents.begin();
                        i != _contents.end(); i++) {
                delete i->second;
        }
}

bool NCPA::CSS::CSSStructure::fieldNameIsValid( const std::string teststring ) const {

        std::vector< std::string > fields = fieldNames();

        for (std::vector< std::string >::iterator i = fields.begin(); i != fields.end(); i++) {
                if (*i == teststring) {
                        return true;
                }
        }
        return false;
}

