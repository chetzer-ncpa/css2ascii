#ifndef BINARYREADER_H
#define BINARYREADER_H

#include <iostream>
#include <cstring>

typedef long long int64;
typedef unsigned int uint;

class BinaryReader {

private:
        static bool bigEndianNative;
        static bool endianChecked;
        float swap( float ) const;
        int swap( int ) const;
        double swap( double ) const;
        short swap( short ) const;
        int64 swap( int64 ) const;
	uint swap( uint ) const;

public:
        void readBigFloatArray( std::istream*, int, float* ) const;
        void readLittleFloatArray( std::istream*, int, float* ) const;
        void readFloatArray( std::istream*, int, float*, bool ) const;
        void readBigIntArray( std::istream*, int, int* ) const;
        void readLittleIntArray( std::istream*, int, int* ) const;
        void readIntArray( std::istream*, int, int*, bool ) const;
        void readBigDoubleArray( std::istream*, int, double* ) const;
        void readLittleDoubleArray( std::istream*, int, double* ) const;
        void readDoubleArray( std::istream*, int, double*, bool ) const;
        void readBigShortArray( std::istream*, int, short* ) const;
        void readLittleShortArray( std::istream*, int, short* ) const;
        void readShortArray( std::istream*, int, short*, bool ) const;
        void readBigLongArray( std::istream*, int, int64* ) const;
        void readLittleLongArray( std::istream*, int, int64* ) const;
        void readLongArray( std::istream*, int, int64*, bool ) const;
        void readBig3ByteIntArray( std::istream*, int, int* ) const;
        void readLittle3ByteIntArray( std::istream*, int, int* ) const;
	void readBigUnsignedIntArray( std::istream*, int, uint* ) const;
	void readLittleUnsignedIntArray( std::istream*, int, uint* ) const;
	void readUnsignedIntArray( std::istream*, int, uint*, bool ) const;

        void readFromCSSCode( std::istream*, int, const char*, double* ) const;
	void readFromCSSCode( std::istream*, int, const std::string, double* ) const;
	int getSampleSize( const std::string ) const;
	int getSampleSize( const char * ) const;

        BinaryReader();
	bool nativeIsBigEndian() const;

};

#endif // BINARYREADER_H
