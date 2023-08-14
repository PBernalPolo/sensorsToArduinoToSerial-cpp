#ifndef _IMU_MEASUREMENT_PACKET_H_
#define _IMU_MEASUREMENT_PACKET_H_



class ImuMeasurementPacket
{
    ////////////////////////////////////////////////////////////////
    // PUBLIC ABSTRACT METHODS
    ////////////////////////////////////////////////////////////////
    public:
        virtual double xGyroscope() = 0;
        virtual double yGyroscope() = 0;
        virtual double zGyroscope() = 0;
        virtual double temperatureGyroscope() = 0;
        virtual double xAccelerometer() = 0;
        virtual double yAccelerometer() = 0;
        virtual double zAccelerometer() = 0;
        virtual double temperatureAccelerometer() = 0;

};


#endif  // #ifndef _IMU_MEASUREMENT_PACKET_H_
