#ifndef _G16A16T16_H_
#define _G16A16T16_H_


#include <HardwareSerial.h>
#include "MeasurementPacket.h"
#include "ImuMeasurementPacket.h"



class G16A16T16
    : public MeasurementPacket,
    public ImuMeasurementPacket
{
    ////////////////////////////////////////////////////////////////
    // PUBLIC CONSTRUCTORS
    ////////////////////////////////////////////////////////////////
    public:
        G16A16T16( int8_t sensorID );
    
    
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
        double temperatureGyroscopeAccelerometer();
        double temperatureGyroscope();
        double temperatureAccelerometer();
        void printMeasurement();
        void setGyroscopeMeasurement( int16_t gx , int16_t gy , int16_t gz );
        void setAccelerometerMeasurement( int16_t ax , int16_t ay , int16_t az );
        void setTemperatureGyroscopeAccelerometerMeasurement( int16_t temp );

};


#endif  // #ifndef _G16A16T16_H_
