
#import "MessageSerializerDeserializer.h"

    
MessageSerializerDeserializer::MessageSerializerDeserializer()
    : checksumReceived( MessageSerializerDeserializer::N_CHECKSUMS ) ,
      checksumComputed( MessageSerializerDeserializer::N_CHECKSUMS )
{
    this->messageIn = StaticArray<int8_t,MESSAGE_MAX_SIZE>::ofSize( 0 );
    this->messageOut = StaticArray<int8_t,MESSAGE_MAX_SIZE>::ofSize( 0 );
    this->state = 0;
    this->nReceivedBytes = 0;
}



////////////////////////////////////////////////////////////////
// PUBLIC METHODS
////////////////////////////////////////////////////////////////

// manages the bytes of the incoming message
int8_t* MessageSerializerDeserializer::manageInputByte( const int8_t newByte )
{
    int8_t* toReturn = NULL;
    // we act depending on the state of the finite-state machine,
    switch( this->state ) {
        case 0:  // we are not receiving a message,
            // we wait for the magic byte
            if( newByte == MessageSerializerDeserializer::MAGIC_BYTE ) {  // if we find the magic byte,
                this->nReceivedBytes = 0;  // we initialize the number of received bytes
                this->state = 1;  // and we go to the next state
            }
            break;
        case 1:  // in this state we obtain the message length
            if( newByte > 0 ) {  // the length of the message has to be positive
                this->messageIn.resize( newByte );
                this->state = 2;  // in the next state we will receive the message
            }else{
                this->state = 0;  // if newByte is negative, it can not be the length of the array
            }
            break;
        case 2:  // we know the size of the message, and we are receiving it
            this->messageIn.set( newByte , this->nReceivedBytes );  // we store the received bytes
            this->nReceivedBytes++;
            // if we complete the message,
            if( this->nReceivedBytes >= this->messageIn.size() ){
                // we go to receive the checksum
                this->nReceivedBytes = 0;
                this->state = 3;
            }
            break;
        case 3:  // we have finished receiving the message. Now we are receiving the checksum
            this->checksumReceived.setByte( newByte , this->nReceivedBytes );  // we store the received bytes
            this->nReceivedBytes++;
            // if we complete the checksum,
            if( this->nReceivedBytes >= MessageSerializerDeserializer::N_CHECKSUMS ){
                // we check if the message is correct
                this->checksumComputed.computeFrom( this->messageIn.data() , this->messageIn.size() );
                // if the checksum is correct,
                if( this->checksumReceived.equals( this->checksumComputed ) ) {
                    toReturn = this->messageIn.data();
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


int MessageSerializerDeserializer::receivedBytesLength() const
{
    return this->nReceivedBytes;
}


// prepares the bytes of an outgoing message
int8_t* MessageSerializerDeserializer::prepareBytesToWrite( const int8_t* message , const int messageLength )
{
    if( messageLength > 127 ) {
        Serial.print( "[MessageSerializerDeserializer.prepareBytesToWrite] Maximum message length is 127 bytes.\n" );
        return NULL;
    }
    // the prepared message will be: ( magicByte , message.length , (message) , (checksums) )
    this->messageOut.resize( 2 + messageLength + MessageSerializerDeserializer::N_CHECKSUMS );
    this->messageOut.set( 0 , MessageSerializerDeserializer::MAGIC_BYTE );
    this->messageOut.set( 1 , (int8_t)messageLength );
    // we copy the message bytes
    for( int i=0; i<messageLength; i++ ) {
        this->messageOut.set( 2+i , message[i] );
    }
    // we compute the checksums
    this->checksumComputed.computeFrom( message , messageLength );
    int8_t* cs = this->checksumComputed.data();
    for( int i=0; i<this->checksumComputed.size(); i++ ) {
        this->messageOut.set( 2+messageLength+i , cs[i] );
    }
    return this->messageOut.data();
}


int MessageSerializerDeserializer::preparedBytesToWriteLength() const
{
    return this->messageOut.size();
}
