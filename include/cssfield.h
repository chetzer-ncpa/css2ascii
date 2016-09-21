#ifndef __CSSFIELD_H__
#define __CSSFIELD_H__

#include <string>
#include <cstdio>
#include "css_base.h"

namespace NCPA {
  namespace CSS {

        class CSSField {
                protected:
                        std::string _fieldName, _fieldContents;
                        int _fieldLength;
                public:
                        virtual double asFloat() const;
                        virtual int asInt() const;
                        virtual char asChar() const;
                        virtual std::string asString() const;
                        virtual std::string format() const;
                        virtual int size() const;

                        std::string key() const;
                        virtual void set( std::string );

                        CSSField( std::string key, std::string value, int fieldLength );
                        CSSField();
        };
        typedef CSSField* fieldPtr;

        class CSSFloatField : public CSSField {
                protected:
                        int _precision;
                        double _value;

                public:
                        CSSFloatField( std::string key, std::string value, int fieldLength, int precision );
                        CSSFloatField( std::string key, double value, int fieldLength, int precision );
                        double asFloat() const;
                        int asInt() const;
                        char asChar() const;
                        std::string asString() const;
                        std::string format() const;

                        void set( std::string );
                        void set( double );
        };

        class CSSIntField : public CSSField {
                protected:
                        int _value;
                public:
                        CSSIntField( std::string key, std::string value, int fieldLength );
                        CSSIntField( std::string key, int value, int fieldLength );
                        std::string format() const;
                        double asFloat() const;
                        int asInt() const;
                        char asChar() const;
                        std::string asString() const;

                        void set( std::string );
                        void set( int );

        };

    }
}












#endif
