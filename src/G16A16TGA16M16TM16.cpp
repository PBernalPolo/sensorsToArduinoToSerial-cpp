
#include "G16A16TGA16M16TM16.h"


////////////////////////////////////////////////////////////////
// PUBLIC CONSTRUCTORS
////////////////////////////////////////////////////////////////

G16A16TGA16M16TM16::G16A16TGA16M16TM16( int8_t sensorID )
    : MeasurementPacket( sensorID , MeasurementPacket::G16A16TGA16M16TM16_ID , 22 )
{
}



////////////////////////////////////////////////////////////////
// PUBLIC METHODS
////////////////////////////////////////////////////////////////

double G16A16TGA16M16TM16::xGyroscope()
{
    return this->int16Decode( 0 );
}


double G16A16TGA16M16TM16::yGyroscope()
{
    return this->int16Decode( 2 );
}


double G16A16TGA16M16TM16::zGyroscope()
{
    return this->int16Decode( 4 );
}


double G16A16TGA16M16TM16::xAccelerometer()
{
    return this->int16Decode( 6 );
}


double G16A16TGA16M16TM16::yAccelerometer()
{
    return this->int16Decode( 8 );
}


double G16A16TGA16M16TM16::zAccelerometer()
{
    return this->int16Decode( 10 );
}


double G16A16TGA16M16TM16::temperatureGyroscopeAccelerometer()
{
    return this->int16Decode( 12 );
}


double G16A16TGA16M16TM16::temperatureGyroscope()
{
    return this->temperatureGyroscopeAccelerometer();
}


double G16A16TGA16M16TM16::temperatureAccelerometer()
{
    return this->temperatureGyroscopeAccelerometer();
}


double G16A16TGA16M16TM16::xMagnetometer()
{
    return this->int16Decode( 14 );
}


double G16A16TGA16M16TM16::yMagnetometer()
{
    return this->int16Decode( 16 );
}


double G16A16TGA16M16TM16::zMagnetometer()
{
    return this->int16Decode( 18 );
}


double G16A16TGA16M16TM16::temperatureMagnetometer()
{
    return this->int16Decode( 20 );
}


void G16A16TGA16M16TM16::printMeasurement()
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


void G16A16TGA16M16TM16::setGyroscopeMeasurement( int16_t gx , int16_t gy , int16_t gz )
{
    this->int16Encode( gx , 0 );
    this->int16Encode( gy , 2 );
    this->int16Encode( gz , 4 );
}


void G16A16TGA16M16TM16::setAccelerometerMeasurement( int16_t ax , int16_t ay , int16_t az )
{
    this->int16Encode( ax , 6 );
    this->int16Encode( ay , 8 );
    this->int16Encode( az , 10 );
}


void G16A16TGA16M16TM16::setTemperatureGyroscopeAccelerometerMeasurement( int16_t temp )
{
    this->int16Encode( temp , 12 );
}


void G16A16TGA16M16TM16::setMagnetometerMeasurement( int16_t mx , int16_t my , int16_t mz )
{
    this->int16Encode( mx , 14 );
    this->int16Encode( my , 16 );
    this->int16Encode( mz , 18 );
}


void G16A16TGA16M16TM16::setTemperatureMagnetometerMeasurement( int16_t temp )
{
    this->int16Encode( temp , 20 );
}
