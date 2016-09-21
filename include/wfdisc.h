/**
  * @title wfdisc.h
  * @description Class to deal with CSS3.0 .wfdisc records
  * @version 0.1.0
  * @author Claus Hetzer claus@olemiss.edu
  */
#ifndef WFDISC_H
#define WFDISC_H

#include <fstream>
#include "cssstructure.h"
#include "css_base.h"

namespace NCPA {
namespace CSS {
    class Wfdisc : public CSSStructure {

	protected:
		void initialize();

    public:

	std::vector< std::string > fieldNames() const;

        // Comparison operators, which compare on sta,chan,time,nsamp in that order
        bool operator<( const Wfdisc & ) const;
        bool operator>( const Wfdisc & ) const;
        bool operator==( const Wfdisc & ) const;
        bool operator!=( const Wfdisc & ) const;
        bool operator<=( const Wfdisc & ) const;
        bool operator>=( const Wfdisc & ) const;

        // Default constructor, sets fields to their default (possibly invalid) values
        Wfdisc();

        // Constructor to read line from file at construct time
        Wfdisc( std::istream*, int );
        Wfdisc( std::istream* );

        // Constructor to initialize with a line of text to be parsed
        Wfdisc( std::string );
	Wfdisc( char * );

        // How many characters should be in one line of a flatfile record
        unsigned int getLineSize();

        // Test another wfdisc to see if they are contiguous
        bool isContiguousWith( const Wfdisc & ) const;

	bool fieldNameIsValid( const std::string testname ) const;
    };
}
}
#endif // WFDISC_H
