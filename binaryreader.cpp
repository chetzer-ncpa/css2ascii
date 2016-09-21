#include "binaryreader.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
/*
    BinaryReader.cpp: Reads binary data from files and returns arrays of
    numbers.
*/

/*
    Typedef shortcut for unsigned chars
*/
typedef unsigned char byte;

bool BinaryReader::bigEndianNative = false;
bool BinaryReader::endianChecked = false;

/**
 * BinaryReader(): Default constructor
 * Checks the endian-ness of the native system and stores it for later reference.
 */
BinaryReader::BinaryReader()
{
        if (!endianChecked) {
                // Cute test for the endian-ness of the system.  Big thanks to a program
                // by Promit Roy, who credits the source code for Quake 2.
                byte SwapTest[2] = { 1, 0 };

                if( *(short *) SwapTest == 1 )
                {
                        bigEndianNative = false;
                } else {
                        bigEndianNative = true;
                }
                endianChecked = true;
        }
        // InitEndian();
}

void BinaryReader::readFloatArray( istream* infile, int samples, float* buffer, bool bigEndian ) const {
	if (bigEndian) {
		readBigFloatArray( infile, samples, buffer );
	} else {
		readLittleFloatArray( infile, samples, buffer );
	}
}

void BinaryReader::readBigFloatArray( istream* infile, int samples, float* buffer ) const {
        int nBytes = samples * 4;
        infile->read((char*)buffer,nBytes);
        if (!bigEndianNative) {
            for (int i = 0; i < samples; i++) {
                    buffer[i] = swap( buffer[i] );
                }
        }
}

void BinaryReader::readLittleFloatArray( istream* infile, int samples, float* buffer ) const {
        int nBytes = samples * 4;
        infile->read((char*)buffer,nBytes);
        if (bigEndianNative) {
            for (int i = 0; i < samples; i++) {
                    buffer[i] = swap( buffer[i] );
                }
        }
}

float BinaryReader::swap( float f ) const {
        union {
                byte b[4];
                float f;
        } u1,u2;

        u1.f = f;
        u2.b[0] = u1.b[3];
        u2.b[1] = u1.b[2];
        u2.b[2] = u1.b[1];
        u2.b[3] = u1.b[0];
        return u2.f;
}



void BinaryReader::readIntArray( istream* infile, int samples, int* buffer, bool bigEndian ) const {
        if (bigEndian) {
                readBigIntArray( infile, samples, buffer );
        } else {
                readLittleIntArray( infile, samples, buffer );
        }
}


void BinaryReader::readBigIntArray( istream* infile, int samples, int* buffer ) const {
        int nBytes = samples * 4;
        infile->read((char*)buffer,nBytes);
        if (!bigEndianNative) {
            for (int i = 0; i < samples; i++) {
                    buffer[i] = swap( buffer[i] );
                }
        }
}

 void BinaryReader::readLittleIntArray( istream* infile, int samples, int* buffer ) const {
        int nBytes = samples * 4;
        infile->read((char*)buffer,nBytes);
        if (bigEndianNative) {
            for (int i = 0; i < samples; i++) {
                    buffer[i] = swap( buffer[i] );
                }
        }
}

int BinaryReader::swap( int i ) const
{
        union {
                byte b[4];
                int i;
        } u1,u2;

        u1.i = i;
        u2.b[0] = u1.b[3];
        u2.b[1] = u1.b[2];
        u2.b[2] = u1.b[1];
        u2.b[3] = u1.b[0];

        return u2.i;
}

uint BinaryReader::swap( uint i ) const
{
        union {
                byte b[4];
                uint i;
        } u1,u2;

        u1.i = i;
        u2.b[0] = u1.b[3];
        u2.b[1] = u1.b[2];
        u2.b[2] = u1.b[1];
        u2.b[3] = u1.b[0];

        return u2.i;
}



void BinaryReader::readUnsignedIntArray( istream* infile, int samples, uint* buffer, bool bigEndian ) const {
	if (bigEndian) {
		readBigUnsignedIntArray( infile, samples, buffer );
	} else {
		readLittleUnsignedIntArray( infile, samples, buffer );
	}
}

void BinaryReader::readBigUnsignedIntArray( istream *infile, int samples, uint *buffer ) const {
	int nBytes = samples * 4;
	infile->read((char*)buffer, nBytes);
	if (!bigEndianNative) {
		for (int i = 0; i < samples; i++) {
			buffer[i] = swap( buffer[i] );
		}
	}
}

void BinaryReader::readLittleUnsignedIntArray( istream *infile, int samples, uint *buffer ) const {
        int nBytes = samples * 4;
        infile->read((char*)buffer, nBytes);
        if (bigEndianNative) {
                for (int i = 0; i < samples; i++) {
                        buffer[i] = swap( buffer[i] );
                }
        }
}

void BinaryReader::readDoubleArray( istream* infile, int samples, double* buffer, bool bigEndian ) const {
        if (bigEndian) {
                readBigDoubleArray( infile, samples, buffer );
        } else {
                readLittleDoubleArray( infile, samples, buffer );
        }
}


 void BinaryReader::readBigDoubleArray( istream* infile, int samples, double* buffer ) const {
        int nBytes = samples * 8;
        infile->read((char*)buffer,nBytes);
        if (!bigEndianNative) {
            for (int i = 0; i < samples; i++) {
                    buffer[i] = swap( buffer[i] );
                }
        }
}

 void BinaryReader::readLittleDoubleArray( istream* infile, int samples, double* buffer ) const {
        int nBytes = samples * 8;
        infile->read((char*)buffer,nBytes);
        if (bigEndianNative) {
            for (int i = 0; i < samples; i++) {
                    buffer[i] = swap( buffer[i] );
                }
        }
}

double BinaryReader::swap( double d ) const {
        union {
                byte b[8];
                double d;
        } u1,u2;
        u1.d = d;

        for (int k = 0; k < 8; k++) {
            u2.b[k] = u1.b[8-1-k];
        }

        return u2.d;
}

  void BinaryReader::readShortArray( istream* infile, int samples, short* buffer, bool bigEndian ) const {
        if (bigEndian) {
                readBigShortArray( infile, samples, buffer );
        } else {
                readLittleShortArray( infile, samples, buffer );
        }
}


 void BinaryReader::readBigShortArray( istream* infile, int samples, short* buffer ) const {
        int nBytes = samples * 2;
        infile->read((char*)buffer,nBytes);
        if (!bigEndianNative) {
            for (int i = 0; i < samples; i++) {
                    buffer[i] = swap( buffer[i] );
                }
        }
}

 void BinaryReader::readLittleShortArray( istream* infile, int samples, short* buffer ) const {
        int nBytes = samples * 2;
        infile->read((char*)buffer,nBytes);
        if (bigEndianNative) {
            for (int i = 0; i < samples; i++) {
                    buffer[i] = swap( buffer[i] );
                }
        }
}

short BinaryReader::swap( short s ) const
{
        union {
                byte b[2];
                short s;
        } u1,u2;
        u1.s = s;

        for (int k = 0; k < 2; k++) {
            u2.b[k] = u1.b[1-k];
        }

        return u2.s;
}

void BinaryReader::readLongArray( istream* infile, int samples, int64* buffer, bool bigEndian ) const {
        if (bigEndian) {
                readBigLongArray( infile, samples, buffer );
        } else {
                readLittleLongArray( infile, samples, buffer );
        }
}


 void BinaryReader::readBigLongArray( istream* infile, int samples, int64* buffer ) const {
        int nBytes = samples * 8;
        infile->read((char*)buffer,nBytes);
        if (!bigEndianNative) {
            for (int i = 0; i < samples; i++) {
                    buffer[i] = swap( buffer[i] );
                }
        }
}

 void BinaryReader::readLittleLongArray( istream* infile, int samples, int64* buffer ) const {
        int nBytes = samples * 8;
        infile->read((char*)buffer,nBytes);
        if (bigEndianNative) {
            for (int i = 0; i < samples; i++) {
                    buffer[i] = swap( buffer[i] );
                }
        }
}

int64 BinaryReader::swap( int64 s ) const {
        union {
                byte b[8];
                int64 s;
        } u1,u2;
        u1.s = s;

        for (int k = 0; k < 8; k++) {
            u2.b[k] = u1.b[7-k];
        }

        return u2.s;
}

void BinaryReader::readFromCSSCode( istream *in, int samples, const std::string datatype,
					double *data ) const {
	this->readFromCSSCode( in, samples, datatype.c_str(), data );
}

void BinaryReader::readFromCSSCode( istream *in, int samples, 
					const char *datatype, double *data ) const {
	
	int *idata;
	short *sdata;
	float *fdata;

	if (strncmp(datatype,"s4",2) == 0 || strncmp(datatype,"S4",2) == 0) {
		idata = new int[ samples ];
		this->readBigIntArray( in, samples, idata );
		for (int i = 0; i < samples; i++) {
			data[ i ] = (double)idata[ i ];
		}
		delete [] idata;
	} else if (strncmp(datatype,"i4",2) == 0 || strncmp(datatype,"I4",2) == 0) {
		idata = new int[ samples ];
                this->readLittleIntArray( in, samples, idata );
                for (int i = 0; i < samples; i++) {
                        data[ i ] = (double)idata[ i ];
                }
                delete [] idata;
	} else if (strncmp(datatype,"s2",2) == 0 || strncmp(datatype,"S2",2) == 0) {
                sdata = new short[ samples ];
                this->readBigShortArray( in, samples, sdata );
                for (int i = 0; i < samples; i++) {
                        data[ i ] = (double)sdata[ i ];
                }
                delete [] sdata;
        } else if (strncmp(datatype,"i2",2) == 0 || strncmp(datatype,"I2",2) == 0) {
                sdata = new short[ samples ];
                this->readLittleShortArray( in, samples, sdata );
                for (int i = 0; i < samples; i++) {
                        data[ i ] = (double)sdata[ i ];
                }
                delete [] sdata;
        } else if (strncmp(datatype,"s3",2) == 0 || strncmp(datatype,"S3",2) == 0) {
                idata = new int[ samples ];
                this->readBig3ByteIntArray( in, samples, idata );
                for (int i = 0; i < samples; i++) {
                        data[ i ] = (double)idata[ i ];
                }
                delete [] idata;
        } else if (strncmp(datatype,"i3",2) == 0 || strncmp(datatype,"I3",2) == 0) {
                idata = new int[ samples ];
                this->readLittle3ByteIntArray( in, samples, idata );
                for (int i = 0; i < samples; i++) {
                        data[ i ] = (double)idata[ i ];
                }
                delete [] idata;
        } else if (strncmp(datatype,"t4",2) == 0 || strncmp(datatype,"T4",2) == 0) {
                fdata = new float[ samples ];
                this->readBigFloatArray( in, samples, fdata );
                for (int i = 0; i < samples; i++) {
                        data[ i ] = (double)fdata[ i ];
                }
                delete [] fdata;
        } else if (strncmp(datatype,"f4",2) == 0 || strncmp(datatype,"F4",2) == 0) {
                fdata = new float[ samples ];
                this->readLittleFloatArray( in, samples, fdata );
                for (int i = 0; i < samples; i++) {
                        data[ i ] = (double)fdata[ i ];
                }
                delete [] fdata;
        } else if (strncmp(datatype,"t8",2) == 0 || strncmp(datatype,"T8",2) == 0) {
		this->readBigDoubleArray( in, samples, data );
        } else if (strncmp(datatype,"f8",2) == 0 || strncmp(datatype,"F8",2) == 0) {
		this->readLittleDoubleArray( in, samples, data );
	} else {
		std::cerr << "Unrecognized CSS datatype!" << std::endl;
	}
}

void BinaryReader::readBig3ByteIntArray( std::istream *in, int samples, int *data ) const {
	
        int nBytes = samples * 3;
	int temp = 0;
	byte *buffer = new byte[ nBytes ];
        in->read((char*)buffer,nBytes);
	for (int i = 0; i < samples; i++) {
		temp = 0;
		temp |= ((unsigned int)buffer[3*i]) << 24 
			| ((unsigned int)buffer[3*i+1]) << 16
			| ((unsigned int)buffer[3*i+2]) << 8;
		data[ i ] = temp >> 8;		
	}
	delete [] buffer;
}

void BinaryReader::readLittle3ByteIntArray( std::istream *in, int samples, int *data ) const  {
	int nBytes = samples * 3;
	int temp = 0;
	byte *buffer = new byte[ nBytes ];
	in->read((char*)buffer,nBytes);
	for (int i = 0; i < samples; i++) {
		temp = 0;
		temp |= ((unsigned int)buffer[3*i+2]) << 24
			| ((unsigned int)buffer[3*i+1]) << 16
			| ((unsigned int)buffer[3*i]) << 8;
		data[ i ] = temp >> 8;
	}
	delete [] buffer;
}

int BinaryReader::getSampleSize( const std::string datatype ) const {
	return this->getSampleSize( datatype.c_str() );
}

int BinaryReader::getSampleSize( const char *datatype ) const {
	
	if (strncmp(datatype,"s4",2) == 0 || strncmp(datatype,"S4",2) == 0) {
		return 4;
	} else if (strncmp(datatype,"i4",2) == 0 || strncmp(datatype,"I4",2) == 0) {
		return 4;
	} else if (strncmp(datatype,"s2",2) == 0 || strncmp(datatype,"S2",2) == 0) {
		return 2;
        } else if (strncmp(datatype,"i2",2) == 0 || strncmp(datatype,"I2",2) == 0) {
		return 2;
        } else if (strncmp(datatype,"s3",2) == 0 || strncmp(datatype,"S3",2) == 0) {
		return 3;
        } else if (strncmp(datatype,"i3",2) == 0 || strncmp(datatype,"I3",2) == 0) {
		return 3;
        } else if (strncmp(datatype,"t4",2) == 0 || strncmp(datatype,"T4",2) == 0) {
		return 4;
        } else if (strncmp(datatype,"f4",2) == 0 || strncmp(datatype,"F4",2) == 0) {
		return 4;
        } else if (strncmp(datatype,"t8",2) == 0 || strncmp(datatype,"T8",2) == 0) {
		return 8;
        } else if (strncmp(datatype,"f8",2) == 0 || strncmp(datatype,"F8",2) == 0) {
		return 8;
	} else {
		return 0;
	}
	
}

bool BinaryReader::nativeIsBigEndian() const {
	return bigEndianNative;
}
