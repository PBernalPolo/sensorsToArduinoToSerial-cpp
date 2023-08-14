
#include "SimpleChecksum.h"



////////////////////////////////////////////////////////////////
// PUBLIC CONSTRUCTORS
////////////////////////////////////////////////////////////////
    
SimpleChecksum::SimpleChecksum( int numberOfBytes )
{
    this->checksum = StaticArray<int8_t,CHECKSUM_MAX_SIZE>::ofSize( numberOfBytes );
}



////////////////////////////////////////////////////////////////
// PUBLIC METHODS
////////////////////////////////////////////////////////////////

void SimpleChecksum::setByte( const int index , const int8_t newByte )
{
    this->checksum.set( index , newByte );
}


int8_t* SimpleChecksum::data() const
{
    return this->checksum.data();
}


int SimpleChecksum::size() const
{
    return this->checksum.size();
}


// computes the checksum from the provided message
void SimpleChecksum::computeFrom( const int8_t* message , const int messageLength )
{
    this->initialize();
    for( int n=0; n<messageLength; n++ ) {
        this->checksum.set( 0 , this->checksum[0] + message[n] );
        for( int i=1; i<this->checksum.size(); i++ ) {
            this->checksum.set( i , this->checksum[i] + this->checksum[i-1] );
        }
    }
}


bool SimpleChecksum::equals( const SimpleChecksum& other ) const
{
    for( int i=0; i<this->checksum.size(); i++ ) {
        if( this->checksum[i] != other.checksum[i] ) {
            return false;
        }
    }
    return true;
}



////////////////////////////////////////////////////////////////
// PRIVATE METHODS
////////////////////////////////////////////////////////////////

void SimpleChecksum::initialize()
{
    this->checksum.set( 0 , 1 );
    for( int i=1; i<this->checksum.size(); i++ ) {
        this->checksum.set( i , 0 );
    }
}
