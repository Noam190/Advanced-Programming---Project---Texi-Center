//
// Created by mei on 30/12/16.
//

#include "Clock.h"


//return the current time, if the time is over return -1
int Clock::getCurrentTime() {
    if (this->currentTime <= this->endTime) {
        return this->currentTime;
    }
    return -1;
}

//add 'addTime' to the current time
void Clock::addToCurrentTime(int addTime ) {
    this->currentTime += addTime;
}