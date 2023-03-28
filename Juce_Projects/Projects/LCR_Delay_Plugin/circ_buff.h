//
// Created by Dean on 05/02/2023.
//
#include "utilities.h"
#ifndef _CIRCBUFF_H_
#define _CIRCBUFF_H_

#pragma once

class CircBuffer{
    using uint = unsigned int; //make "unsigned int" shorter

public:
    CircBuffer(uint size); // constructor of the CircBuffer class that expects the size of the buffer, giving that value to currentSize
    ~CircBuffer(); // deconstructor of the CircBuffer class, deleting the buffer

    void input (float value); //function for adding the input to the buffer (write)
    float output(); //function for returning a value from the buffer (read)
    float interpolatedOutput(); //function for returning an interpolated value from the buffer
    void incrementHeads(); // increment both heads with a value

    //setters and getters
    void setDistance (float distance);// set the difference in a number between writehead and readhead (delay)
    void getResetSize(uint size); //function for getting what the "new" size is, but waiting to execute when readHead is 0
    float getCurrentSize(); //get the current size of the buffer

    void resetSize(uint size);//function for actually resetting the size
    bool resize { false }; //boolean for resizing the buffer when readhead is 0

protected:
    inline void wrapHeader (float& head); // function for "wrapping" an index for a header
    inline void incrementWrite(); // add a value to the writeHead
    inline void incrementRead(); // add a value to the readHead
    void deleteBuffer(); // functions for deleting the buffer
    void deleteResizedBuffer(); //function for deleting resized buffer

    float newSizeBuffer { 0 }; //buffer for saving what the new size is but waiting to make it the current size till readHead is 0
    float wrapValue { 0 }; //value for wrapping
    float currentDistance { 0 }; //the distance between the write and readHead
    float currentSize { 0 }; // variable for the size of the buffer
    float writeHead { 0 };
    float readHead { 0 }; //variables for the index of a header
    Util util;
    float* buffer; // empty pointer for a buffer
    float* resizedBuffer; //empty pointer for a buffer if you want to resize
};

#endif