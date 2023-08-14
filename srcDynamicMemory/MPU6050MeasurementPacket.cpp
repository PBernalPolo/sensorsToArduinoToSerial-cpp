
#include "MPU6050MeasurementPacket.h"


////////////////////////////////////////////////////////////////
// PUBLIC CONSTRUCTORS
////////////////////////////////////////////////////////////////

MPU6050MeasurementPacket::MPU6050MeasurementPacket( int8_t sensorID )
    : MeasurementPacket( sensorID , MeasurementPacket::MPU6050_ID , 14 )
{
}



////////////////////////////////////////////////////////////////
// PUBLIC METHODS
////////////////////////////////////////////////////////////////

double MPU6050MeasurementPacket::xGyroscope()
{
    return this->int16Decode( 0 );
}


double MPU6050MeasurementPacket::yGyroscope()
{
    return this->int16Decode( 2 );
}


double MPU6050MeasurementPacket::zGyroscope()
{
    return this->int16Decode( 4 );
}


double MPU6050MeasurementPacket::xAccelerometer()
{
    return this->int16Decode( 6 );
}


double MPU6050MeasurementPacket::yAccelerometer()
{
    return this->int16Decode( 8 );
}


double MPU6050MeasurementPacket::zAccelerometer()
{
    return this->int16Decode( 10 );
}


double MPU6050MeasurementPacket::temperature()
{
    return this->int16Decode( 12 );
}


double MPU6050MeasurementPacket::temperatureGyroscope()
{
    return this->temperature();
}


double MPU6050MeasurementPacket::temperatureAccelerometer()
{
    return this->temperature();
}


void MPU6050MeasurementPacket::printMeasurement()
{
    Serial.print( "gx: " );
    Serial.print( (int16_t)this->xGyroscope() );
    Serial.print( "  gy: " );
    Serial.print( (int16_t)this->yGyroscope() );
    Serial.print( "  gz: " );
    Serial.print( (int16_t)this->zGyroscope() );
    Serial.print( "    ax: " );
    Serial.print( (int16_t)this->xAccelerometer() );
    Serial.print( "  ay: " );
    Serial.print( (int16_t)this->yAccelerometer() );
    Serial.print( "  az: " );
    Serial.print( (int16_t)this->zAccelerometer() );
    Serial.print( "    temp: " );
    Serial.println();
}


void MPU6050MeasurementPacket::setGyroscopeMeasurement( int16_t gx , int16_t gy , int16_t gz )
{
    this->int16Encode( gx , 0 );
    this->int16Encode( gy , 2 );
    this->int16Encode( gz , 4 );
}


void MPU6050MeasurementPacket::setAccelerometerMeasurement( int16_t ax , int16_t ay , int16_t az )
{
    this->int16Encode( ax , 6 );
    this->int16Encode( ay , 8 );
    this->int16Encode( az , 10 );
}


void MPU6050MeasurementPacket::setTemperatureGyroscopeAccelerometerMeasurement( int16_t temp )
{
    this->int16Encode( temp , 12 );
}
