
#import "SerialMessageManager.h"


    
SerialMessageManager::SerialMessageManager()
    : checksumReceived( SerialMessageManager::N_CHECKSUMS ) ,
      checksumComputed( SerialMessageManager::N_CHECKSUMS )
{
    this->state = 0;
    this->nReceivedBytes = 0;
    this->messageIn = new int8_t[0];
    this->messageOut = new int8_t[0];
}



////////////////////////////////////////////////////////////////
// PUBLIC METHODS
////////////////////////////////////////////////////////////////

// manages the bytes of the incoming message
int8_t* SerialMessageManager::manageInputByte( int8_t newByte )
{
    int8_t* toReturn = NULL;
    // we act depending on the state of the finite-state machine,
    switch( this->state ) {
        case 0:  // we are not receiving a message,
            // we wait for the magic byte
            if( newByte == SerialMessageManager::MAGIC_BYTE ) {  // if we find the magic byte,
                this->nReceivedBytes = 0;  // we initialize the number of received bytes
                this->state = 1;  // and we go to the next state
            }
            break;
        case 1:  // in this state we obtain the message length
            if( newByte > 0 ) {  // the length of the message has to be positive
                this->messageInLength = newByte;
                delete[] this->messageIn;
                this->messageIn = new int8_t[ newByte ];
                this->state = 2;  // in the next state we will receive the message
            }else{
                this->state = 0;  // if newByte is negative, it can not be the length of the array
            }
            break;
        case 2:  // we know the size of the message, and we are receiving it
            this->messageIn[this->nReceivedBytes] = newByte;  // we store the received bytes
            this->nReceivedBytes++;
            // if we complete the message,
            if( this->nReceivedBytes >= this->messageInLength ){
                // we go to receive the checksum
                this->nReceivedBytes = 0;
                this->state = 3;
            }
            break;
        case 3:  // we have finished receiving the message. Now we are receiving the checksum
            this->checksumReceived.setByte( newByte , this->nReceivedBytes );  // we store the received bytes
            this->nReceivedBytes++;
            // if we complete the checksum,
            if( this->nReceivedBytes >= SerialMessageManager::N_CHECKSUMS ){
                // we check if the message is correct
                this->checksumComputed.computeFrom( this->messageIn , this->messageInLength );
                // if the checksum is correct,
                if( this->checksumReceived.equals( this->checksumComputed ) ) {
                    toReturn = this->messageIn;
                }
                // after receiving the checksum, the next state is the initial state
                this->state = 0;
            }
            break;
        default:
            // if we are in some other state, we go back to the initial one
            this->state = 0;
            break;
    }  // end switch( this->state )
    return toReturn;
}  // end manageInputByte( byte newByte )


// prepares the bytes of an outgoing message
int8_t* SerialMessageManager::prepareBytesToWrite( int8_t* message , int messageLength )
{
    if( messageLength > 127 ) {
        Serial.print( "[SerialMessageManager.prepareBytesToWrite] Maximum message length is 127 bytes.\n" );
        return NULL;
    }
    // the prepared message will be: ( magicByte , message.length , (message) , (checksums) )
    this->messageOutLength = 2 + messageLength + SerialMessageManager::N_CHECKSUMS;
    delete[] this->messageOut;
    this->messageOut = new int8_t[ this->messageOutLength ];
    this->messageOut[0] = SerialMessageManager::MAGIC_BYTE;
    this->messageOut[1] = (int8_t)messageLength;
    // we copy the message bytes
    for( int i=0; i<messageLength; i++ ) {
        this->messageOut[2+i] = message[i];
    }
    // we compute the checksums
    this->checksumComputed.computeFrom( message , messageLength );
    int8_t* checksum = this->checksumComputed.getBytes();
    for( int i=0; i<this->checksumComputed.getBytesLength(); i++ ) {
        this->messageOut[2+messageLength+i] = checksum[i];
    }
    return this->messageOut;
}  // end prepareBytesToWrite( int8_t* message )


int SerialMessageManager::bytesToWriteLength()
{
    return this->messageOutLength;
}