/**
  * @title wfdisc.h
  * @description Class to deal with CSS3.0 .wfdisc records
  * @version 0.1.0
  * @author Claus Hetzer claus@olemiss.edu
  */
#ifndef __SITE_H__
#define __SITE_H__

#include <fstream>
#include <map>
#include <vector>
#include "site.h"
#include "cssstructure.h"

namespace NCPA {
namespace CSS {
    class Site : public CSSStructure {

	protected:
		void initialize();

	public:

		std::vector< std::string > fieldNames() const;

        // Comparison operators, which compare on sta,ondate in that order
        bool operator==( const Site & ) const;
        bool operator!=( const Site & ) const;

        // Default constructor, sets fields to their default (possibly invalid) values
        Site();

        // Constructor to read line from file at construct time
        Site( std::istream*, int );
        Site( std::istream* );

        // Constructor to initialize with a line of text to be parsed
        Site( std::string );
	Site( char * );

        // How many characters should be in one line of a flatfile record
        inline unsigned int getLineSize();

    };
}
}
#endif // WFDISC_H
