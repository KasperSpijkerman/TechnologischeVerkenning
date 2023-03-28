#include "circ_buff.h"
#include <iostream>
#include <algorithm>
#include <iterator>
#include <cmath>
//////////PUBLIC//////////

CircBuffer::CircBuffer(uint size) : currentSize(size), buffer(new float[currentSize])

{ // constructor
    // std::cout << "THIS IS THE CONSTRUCTOR" << std::endl;
    wrapValue = currentSize;
    for (uint i = 0; i < sizeof(buffer); i++){
        buffer[i] = 0;
    }

}

CircBuffer::~CircBuffer() { // deconstructor
    // std::cout << "THIS IS THE DECONSTRUCTOR" << std::endl;
    deleteBuffer();
}

void CircBuffer::input(float value){
    int writeHeadBuffer; //make an variable of an int type to use as index for the buffer
    writeHeadBuffer = writeHead; //give the buffer the value of the writehead
    buffer[writeHeadBuffer] = value; // add value to buffer on the writeHead index
    // std::cout << value << " IS THE INPUT" << std::endl;
}

float CircBuffer::output(){ //function for returning a value from the buffer (read)
    // truncate index (remove everything after the decimal point)
    int i = (int) trunc (readHead);
    // subtract from the original value to find the remainder
    float indexDecimal = readHead - (float) i;
    // std::cout << linearMap(indexDecimal, buffer[i], buffer[i + 1]) << " IS THE OUTPUT" << std::endl;
    return util.linearMap(indexDecimal, buffer[i], buffer[i + 1]);
}

float CircBuffer::interpolatedOutput(){
    // truncate index (remove everything after the decimal point)
    int i = (int) trunc (readHead);
    // subtract from the original value to find the remainder
    float indexDecimal = readHead - (float) i;
    // std::cout << linearMap(indexDecimal, buffer[i], buffer[i + 1]) << " IS THE OUTPUT" << std::endl;
    return util.linearMap(indexDecimal, buffer[i], buffer[i + 1]);
}

void CircBuffer::setDistance (float distance){ // set the difference in a number between writehead and readhead (delay)
    currentDistance = distance;
    float readHeadBuffer = writeHead - distance;
    if(readHeadBuffer < 0){
        readHead = readHeadBuffer + currentSize;
    } else {
        readHead = readHeadBuffer;
    }

    // std::cout << "this is the readHead: " << readHead << std::endl;
    // std::cout << "this is the distance: " << currentDistance << std::endl;
}


void CircBuffer::incrementHeads(){  // increment both heads with a value
    incrementRead();
    incrementWrite();
    wrapHeader(readHead);
    wrapHeader(writeHead);
}

void CircBuffer::getResetSize(uint size){
    if (size > currentSize)
    {
        resize = true;
        newSizeBuffer = size;
    }
    else{
        currentSize = size;
    }
//    std::cout << "NEW SIZE BUFF: "<<  newSizeBuffer << std::endl;
}

void CircBuffer::resetSize(uint size){
//    std::cout << "Resetting size from " << currentSize << " to " << newSizeBuffer << " and distance " << currentDistance << std::endl;
    wrapValue = size;
    resizedBuffer = new float[size];
    for (uint i = 0; i < currentSize; i++){
        resizedBuffer[i] = buffer[i];
    }
    deleteBuffer();

    currentSize = newSizeBuffer;
    buffer = new float[currentSize];
    for (uint i = 0; i < sizeof(currentSize); i++){
        buffer[i] = resizedBuffer[i];
    }
    deleteResizedBuffer();

    setDistance(currentSize - 1);
//    std::cout << "Resetting size success. Size is now " << currentSize << " and distance " << currentDistance << std::endl;
    resize = false;
}


float CircBuffer::getCurrentSize(){
    return currentSize;
}

///////////PRIVATE//////////

inline void CircBuffer::wrapHeader(float& head){ // function for "wrapping" an index for a header
    if (head >= wrapValue) {
        head = head - wrapValue;
    };
}

inline void CircBuffer::incrementWrite(){ // add a value to the writeHead
    writeHead += 1;
}

inline void CircBuffer::incrementRead(){ // add a value to the readHead

    if(readHead == 0 && resize == true ){
//        std::cout << "RESIZE IS TRUUUUUEEEE "<<  std::endl;
        resetSize(newSizeBuffer);
    }
    readHead += 1;
}

void CircBuffer::deleteBuffer(){  // function for deleting the buffer
    delete[] buffer;
}

void CircBuffer::deleteResizedBuffer(){
    delete[] resizedBuffer;
}


//als writeHead groter is dan buffersize, wrapfunctie word writehead+1 totdat readHead 0 is,
//dan wordt wrapfunctie weer de buffersize