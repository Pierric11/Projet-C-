#ifndef _TIMER_H
#define _TIMER_H

/** Second duration in milliseconds */
#define TIMER_1_SEC 1000

/** Minute duration in milliseconds */
#define TIMER_1_MIN  (60*TIMER_1_SEC)

/** Timer type. */
typedef unsigned long timer_t;

/**
* Reset the timer.
* @param timer The timer to reset.
*/
void timer_reset  (timer_t& timer);

/**
* Check if the timer has elapsed the given duration and reset it if it did have.
* @param timer The timer to check.
* @param duration The duration to check against.
* @return true if the timer has elapsed the given duration, false otherwise.
*/
bool timer_elapsed(timer_t& timer, long duration_ms);

#endif
