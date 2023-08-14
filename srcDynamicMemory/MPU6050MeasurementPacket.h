#ifndef _MPU6050_MEASUREMENT_PACKET_H_
#define _MPU6050_MEASUREMENT_PACKET_H_


#include <HardwareSerial.h>
#include "MeasurementPacket.h"
#include "ImuMeasurementPacket.h"



class MPU6050MeasurementPacket
    : public MeasurementPacket,
    public ImuMeasurementPacket
{
    ////////////////////////////////////////////////////////////////
    // PUBLIC CONSTRUCTORS
    ////////////////////////////////////////////////////////////////
    public:
        MPU6050MeasurementPacket( int8_t sensorID );
    
    
    ////////////////////////////////////////////////////////////////
    // PUBLIC METHODS
    ////////////////////////////////////////////////////////////////
    public:
        double xGyroscope();
        double yGyroscope();
        double zGyroscope();
        double xAccelerometer();
        double yAccelerometer();
        double zAccelerometer();
        double temperature();
        double temperatureGyroscope();
        double temperatureAccelerometer();
        void printMeasurement();
        void setGyroscopeMeasurement( int16_t gx , int16_t gy , int16_t gz );
        void setAccelerometerMeasurement( int16_t ax , int16_t ay , int16_t az );
        void setTemperatureGyroscopeAccelerometerMeasurement( int16_t temp );

};


#endif  // #ifndef _MPU6050_MEASUREMENT_PACKET_H_
