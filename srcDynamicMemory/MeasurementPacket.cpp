
#include "MeasurementPacket.h"
//#include "MPU6050AndHMC5883LMeasurementPacket.h"
#include "MPU6050MeasurementPacket.h"



////////////////////////////////////////////////////////////////
// PUBLIC CONSTRUCTORS
////////////////////////////////////////////////////////////////

MeasurementPacket::MeasurementPacket( int8_t sensorId , int16_t sensorTypeId , int numberOfBytesNeeded )
{
    this->nBytes = numberOfBytesNeeded +
                   MeasurementPacket::NUMBER_OF_BYTES_FOR_SENSOR_TYPE +
                   MeasurementPacket::NUMBER_OF_BYTES_FOR_SENSOR_ID;
    this->b = new int8_t[ this->nBytes ];
    this->setSensorTypeId( sensorTypeId );
    this->setSensorId( sensorId );
}
    
    
    
////////////////////////////////////////////////////////////////
// PUBLIC METHODS
////////////////////////////////////////////////////////////////
    
void MeasurementPacket::setBytes( int8_t* theBytes )
{
    this->b = theBytes;
}


int8_t* MeasurementPacket::bytes()
{
    return this->b;
}


int MeasurementPacket::bytesLength()
{
    return this->nBytes;
}


int16_t MeasurementPacket::sensorTypeId()
{
    return MeasurementPacket::sensorTypeIdDecode( this->b );
}


int8_t MeasurementPacket::sensorId()
{
    return MeasurementPacket::sensorIdDecode( this->b );
}


void MeasurementPacket::print()
{
    Serial.print( "[TID] " );
    Serial.print( this->sensorTypeId() );
    Serial.print( "      [SID] " );
    Serial.print( this->sensorId() );
    Serial.print( "      " );
    this->printMeasurement();
}



////////////////////////////////////////////////////////////////
// PUBLIC STATIC METHODS
////////////////////////////////////////////////////////////////

MeasurementPacket* MeasurementPacket::fromBytes( int8_t* b )
{
    if( b == NULL ) return NULL;
    int16_t sensorTypeId = MeasurementPacket::sensorTypeIdDecode( b );
    int8_t sensorId = MeasurementPacket::sensorIdDecode( b );
    MeasurementPacket* mp;
    switch( sensorTypeId ) {
        case MeasurementPacket::MPU6050_AND_HMC5883L_ID:
            mp = NULL; //MPU6050AndHMC5883LMeasurementPacket( sensorId );
            break;
        case MeasurementPacket::MPU6050_ID:
            mp = new MPU6050MeasurementPacket( sensorId );
            break;
        default:
            mp = NULL;
    }
    if( mp != NULL ) {
        mp->setBytes( b );
    }
    return mp;
}


int16_t MeasurementPacket::sensorTypeIdDecode( int8_t* b )
{
    return MeasurementPacket::int16Decode( b , 0 );
}


int8_t MeasurementPacket::sensorIdDecode( int8_t* b )
{
    return MeasurementPacket::int8Decode( b , MeasurementPacket::NUMBER_OF_BYTES_FOR_SENSOR_TYPE );
}


void MeasurementPacket::int8Encode( int8_t value , int8_t* b , int index )
{
    b[index] = value;
}


int8_t MeasurementPacket::int8Decode( int8_t* b , int index )
{
    return b[index];
}


void MeasurementPacket::int16Encode( int16_t value , int8_t* b , int index )
{
    // we create a int8_t pointer pointing to the address of the int16
    int8_t* packets = (int8_t*) &value;
    b[index] = packets[0];
    b[index+1] = packets[1];
}


int16_t MeasurementPacket::int16Decode( int8_t* b , int index )
{
    // we create a int16 pointer pointing to the first byte
    int16_t* valuePointer = (int16_t*) &b[index];
    // we return the value of the int16 pointed by the pointer
    return *valuePointer;
}


void MeasurementPacket::int32Encode( int32_t value , int8_t* b , int index )
{
    // we create a int8_t pointer pointing to the address of the int32
    int8_t* packets = (int8_t*) &value;
    b[index] = packets[0];
    b[index+1] = packets[1];
    b[index+2] = packets[2];
    b[index+3] = packets[3];
}


int32_t MeasurementPacket::int32Decode( int8_t* b , int index )
{
    // we create a int32 pointer pointing to the first byte
    int32_t* valuePointer = (int32_t*) &b[index];
    // we return the value of the int32 pointed by the pointer
    return *valuePointer;
}


void MeasurementPacket::int64Encode( int64_t value , int8_t* b , int index )
{
    // we create a int8_t pointer pointing to the address of the int64
    int8_t* packets = (int8_t*) &value;
    b[index] = packets[0];
    b[index+1] = packets[1];
    b[index+2] = packets[2];
    b[index+3] = packets[3];
    b[index+4] = packets[4];
    b[index+5] = packets[5];
    b[index+6] = packets[6];
    b[index+7] = packets[7];
}


int64_t MeasurementPacket::int64Decode( int8_t* b , int index )
{
    // we create a int64 pointer pointing to the first byte
    int64_t* valuePointer = (int64_t*) &b[index];
    // we return the value of the int64 pointed by the pointer
    return *valuePointer;
}


void MeasurementPacket::floatEncode( float value , int8_t* b , int index )
{
    // we create a int8_t pointer pointing to the address of the float
    int8_t* packets = (int8_t*) &value;
    b[index] = packets[0];
    b[index+1] = packets[1];
    b[index+2] = packets[2];
    b[index+3] = packets[3];
}


float MeasurementPacket::floatDecode( int8_t* b , int index )
{
    // we create a float pointer pointing to the first byte
    float* valuePointer = (float*) &b[index];
    // we return the value of the float pointed by the pointer
    return *valuePointer;
}


void doubleEncode( double value , int8_t* b , int index )
{
    // we create a int8_t pointer pointing to the address of the double
    int8_t* packets = (int8_t*) &value;
    b[index] = packets[0];
    b[index+1] = packets[1];
    b[index+2] = packets[2];
    b[index+3] = packets[3];
    b[index+4] = packets[4];
    b[index+5] = packets[5];
    b[index+6] = packets[6];
    b[index+7] = packets[7];
}


double doubleDecode( int8_t* b , int index )
{
    // we create a double pointer pointing to the first byte
    double* valuePointer = (double*) &b[index];
    // we return the value of the double pointed by the pointer
    return *valuePointer;
}



////////////////////////////////////////////////////////////////
// PROTECTED METHODS
////////////////////////////////////////////////////////////////

void MeasurementPacket::int8Encode( int8_t value , int index )
{
    MeasurementPacket::int8Encode( value , this->b , MeasurementPacket::indexShifted( index ) );
}


int8_t MeasurementPacket::int8Decode( int index )
{
    return MeasurementPacket::int8Decode( this->b , MeasurementPacket::indexShifted( index ) );
}


void MeasurementPacket::int16Encode( int16_t value , int index )
{
    MeasurementPacket::int16Encode( value , this->b , MeasurementPacket::indexShifted( index ) );
}


int16_t MeasurementPacket::int16Decode( int index )
{
    return MeasurementPacket::int16Decode( this->b , MeasurementPacket::indexShifted( index ) );
}


void MeasurementPacket::int32Encode( int value , int index )
{
    MeasurementPacket::int32Encode( value , this->b , MeasurementPacket::indexShifted( index ) );
}


int MeasurementPacket::int32Decode( int index )
{
    return MeasurementPacket::int32Decode( this->b , MeasurementPacket::indexShifted( index ) );
}


void MeasurementPacket::int64Encode( long value , int index )
{
    MeasurementPacket::int64Encode( value , this->b , MeasurementPacket::indexShifted( index ) );
}


long MeasurementPacket::int64Decode( int index )
{
    return MeasurementPacket::int64Decode( this->b , MeasurementPacket::indexShifted( index ) );
}


void MeasurementPacket::floatEncode( float value , int index )
{
    MeasurementPacket::floatEncode( value , this->b , MeasurementPacket::indexShifted( index ) );
}


float MeasurementPacket::floatDecode( int index )
{
    return MeasurementPacket::floatDecode( this->b , MeasurementPacket::indexShifted( index ) );
}


void MeasurementPacket::doubleEncode( double value , int index )
{
    MeasurementPacket::doubleEncode( value , this->b , MeasurementPacket::indexShifted( index ) );
}


double MeasurementPacket::doubleDecode( int index )
{
    return MeasurementPacket::doubleDecode( this->b , MeasurementPacket::indexShifted( index ) );
}



////////////////////////////////////////////////////////////////
// PRIVATE METHODS
////////////////////////////////////////////////////////////////

void MeasurementPacket::setSensorTypeId( int16_t value )
{
    MeasurementPacket::int16Encode( value , this->b , 0 );
}


void MeasurementPacket::setSensorId( int8_t value )
{
    MeasurementPacket::int8Encode( value , this->b , MeasurementPacket::NUMBER_OF_BYTES_FOR_SENSOR_TYPE );
}



////////////////////////////////////////////////////////////////
// PRIVATE STATIC METHODS
////////////////////////////////////////////////////////////////

int MeasurementPacket::indexShifted( int index )
{
    return ( MeasurementPacket::NUMBER_OF_BYTES_FOR_SENSOR_TYPE + MeasurementPacket::NUMBER_OF_BYTES_FOR_SENSOR_ID + index );
}
