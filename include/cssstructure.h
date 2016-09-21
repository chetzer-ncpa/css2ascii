#ifndef CSSSTRUCTURE_H
#define CSSSTRUCTURE_H

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "css_base.h"
#include "cssfield.h"


namespace NCPA {
  namespace CSS {

    class CSSStructure
    {
    protected:
        virtual unsigned int getLineSize() = 0;
	virtual void initialize() = 0;

        bool LOAD_ERROR;
	std::map< std::string, fieldPtr > _contents;
    public:
        //CSSStructure();
        //virtual ~CSSStructure() = 0;
	virtual ~CSSStructure();

        void appendToFile( std::ofstream* const );
        void appendToFile( std::string const );
        bool readLine( std::istream* const );
        bool readLineFromFile( std::string const );
        bool readLine( std::istream* const, int );
        bool readLineFromFile( std::string const, int );
	virtual std::vector< std::string > fieldNames() const = 0;
	virtual void printSummary( std::ostream *out ) const;
	virtual void printSummary() const;
	virtual bool parseLine( char *line );
	virtual bool parseLine( std::string s );
	virtual void formatLine( char *line );
	virtual bool fieldNameIsValid( const std::string teststring ) const;

	NCPA::CSS::CSSField * getField( std::string fieldName ) const;
	NCPA::CSS::CSSField * getField( const char *fieldName ) const;	

        bool error();
    };
  }
}
#endif // CSSSTRUCTURE_H
