#ifndef _SERIAL_MESSAGE_MANAGER_H_
#define _SERIAL_MESSAGE_MANAGER_H_


#include <stdint.h>
#include <HardwareSerial.h>
#include "SimpleChecksum.h"



class SerialMessageManager
{
    ////////////////////////////////////////////////////////////////
    // PRIVATE CONSTANTS
    ////////////////////////////////////////////////////////////////
    private:
        static const int8_t MAGIC_BYTE = '\n';  // magic byte to indicate the start of a new package
        static const int N_CHECKSUMS = 2;  // number of checksums
    
    
    ////////////////////////////////////////////////////////////////
    // PRIVATE VARIABLES
    ////////////////////////////////////////////////////////////////
    private:
        // checksum that arrives with the incoming message
        const SimpleChecksum checksumReceived;
        // checksum computed with the incoming message
        const SimpleChecksum checksumComputed;
        int8_t* messageIn;  // pointer to array of bytes that will contain the message being received
        int8_t* messageOut;  // pointer to array of bytes to send
        int messageInLength;
        int messageOutLength;
        int nReceivedBytes;  // number of received bytes of the current incoming message
        int state;  // state in the management of the incoming message
    
    
    
    ////////////////////////////////////////////////////////////////
    // PUBLIC CONSTRUCTORS
    ////////////////////////////////////////////////////////////////
    public:
        SerialMessageManager();
    
    
    
    ////////////////////////////////////////////////////////////////
    // PUBLIC METHODS
    ////////////////////////////////////////////////////////////////
    public:
        // manages the bytes of the incoming message
        int8_t* manageInputByte( int8_t newByte );
        // prepares the bytes of an outgoing message
        int8_t* prepareBytesToWrite( int8_t* message , int messageLength );
        int bytesToWriteLength();
    
};


#endif  // #ifndef _SERIAL_MESSAGE_MANAGER_H_
