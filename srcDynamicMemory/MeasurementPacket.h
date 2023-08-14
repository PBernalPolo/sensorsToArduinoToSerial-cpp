#ifndef _MEASUREMENT_PACKET_H_
#define _MEASUREMENT_PACKET_H_


#include <stdint.h>
#include <HardwareSerial.h>



class MeasurementPacket
{
    ////////////////////////////////////////////////////////////////
    // PUBLIC CONSTANT PARAMETERS
    ////////////////////////////////////////////////////////////////
    public:
        static const int16_t MPU6050_AND_HMC5883L_ID = 0;
        static const int16_t MPU6050_ID = 1;
    

    ////////////////////////////////////////////////////////////////
    // PRIVATE CONSTANT PARAMETERS
    ////////////////////////////////////////////////////////////////
    private:
        static const int NUMBER_OF_BYTES_FOR_SENSOR_TYPE = 2;
        static const int NUMBER_OF_BYTES_FOR_SENSOR_ID = 1;
    


    ////////////////////////////////////////////////////////////////
    // PROTECTED VARIABLES
    ////////////////////////////////////////////////////////////////
    protected:
        int nBytes;  // number of bytes in the buffer
        int8_t* b;  // buffer of bytes
    
    
    
    ////////////////////////////////////////////////////////////////
    // PUBLIC ABSTRACT METHODS
    ////////////////////////////////////////////////////////////////
    public:
        virtual void printMeasurement() = 0;
    
    
    
    ////////////////////////////////////////////////////////////////
    // PUBLIC CONSTRUCTORS
    ////////////////////////////////////////////////////////////////
    public:
        MeasurementPacket( int8_t sensorId , int16_t sensorTypeId , int numberOfBytesNeeded );
    
    
    
    ////////////////////////////////////////////////////////////////
    // PUBLIC METHODS
    ////////////////////////////////////////////////////////////////
    public:
        void setBytes( int8_t* theBytes );
        int8_t* bytes();
        int bytesLength();  // size of bytes buffer
        int16_t sensorTypeId();
        int8_t sensorId();
        void print();
    

    
    ////////////////////////////////////////////////////////////////
    // PUBLIC STATIC METHODS
    ////////////////////////////////////////////////////////////////
    public:
        static MeasurementPacket* fromBytes( int8_t* b );
        static int16_t sensorTypeIdDecode( int8_t* b );
        static int8_t sensorIdDecode( int8_t* b );
        static void int8Encode( int8_t value , int8_t* b , int index );
        static int8_t int8Decode( int8_t* b , int index );
        static void int16Encode( int16_t value , int8_t* b , int index );
        static int16_t int16Decode( int8_t* b , int index );
        static void int32Encode( int32_t value , int8_t* b , int index );
        static int32_t int32Decode( int8_t* b , int index );
        static void int64Encode( int64_t value , int8_t* b , int index );
        static int64_t int64Decode( int8_t* b , int index );
        static void floatEncode( float value , int8_t* b , int index );
        static float floatDecode( int8_t* b , int index );
        static void doubleEncode( double value , int8_t* b , int index );
        static double doubleDecode( int8_t* b , int index );

    
    ////////////////////////////////////////////////////////////////
    // PROTECTED METHODS
    ////////////////////////////////////////////////////////////////
    protected:
        void int8Encode( int8_t value , int index );
        int8_t int8Decode( int index );
        void int16Encode( int16_t value , int index );
        int16_t int16Decode( int index );
        void int32Encode( int value , int index );
        int int32Decode( int index );
        void int64Encode( long value , int index );
        long int64Decode( int index );
        void floatEncode( float value , int index );
        float floatDecode( int index );
        void doubleEncode( double value , int index );
        double doubleDecode( int index );
    

    ////////////////////////////////////////////////////////////////
    // PRIVATE METHODS
    ////////////////////////////////////////////////////////////////
    private:
        void setSensorTypeId( int16_t value );
        void setSensorId( int8_t value );


    ////////////////////////////////////////////////////////////////
    // PRIVATE STATIC METHODS
    ////////////////////////////////////////////////////////////////
    private:
        static int indexShifted( int index );

};


#endif  // #ifndef _MEASUREMENT_PACKET_H_
