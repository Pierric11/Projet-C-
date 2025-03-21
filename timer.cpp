#include "timer.h"

#include <Arduino.h>

/**
* Reset the timer.
* @param timer The timer to reset.
*/
void timer_reset(timer_t& timer)
{
  timer = millis();
}

/**
* Check if the timer has elapsed the given duration and reset it if it did have.
* @param timer The timer to check.
* @param duration_ms The duration to check against.
* @return true if the timer has elapsed the given duration, false otherwise.
*/
bool timer_elapsed(timer_t& timer, long duration_ms)
{
  if(millis()-timer > duration) {
  	timer += duration;
    return true;
  }
  return false;
}
