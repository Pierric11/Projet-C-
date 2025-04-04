#include <LiquidCrystal.h>
#include "timer.h"
#include "scores.h"
#define UP 8
#define DOWN 9
#define LEFT 10
#define RIGHT 11


enum States
{
    START_GAME,
    D_ENI_1,
    ENIGME_1,
    D_ENI_2,
    ENIGME_2,
    D_ENI_3,
    ENIGME_3,
    D_ENI_4,
    ENIGME_4,
    UP_PRESSED,
    DOWN_PRESSED,
    LEFT_PRESSED,
    RIGHT_PRESSED
};

enum States state = START_GAME;

void setup()
{

}

void loop()
{
    switch(state)
    {
        case START_GAME:
            {
                
            }
        break;

        case D_ENI_1:   
            if(digitalRead(DOWN)== HIGH && timer_elapsed(timer, 2000))
            {
               
            }
        break;

        case ENIGME_1:
            if(digitalRead(UP)== HIGH && timer_elapsed(timer, 1000))
                {

                }
        break;

        case D_ENI_2:   
            if(digitalRead(DOWN)== HIGH && timer_elapsed(timer, 2000))
            {
               state = ENIGME_2;
            }
        break;

        case D_ENI_3:   
            if(digitalRead(DOWN)== HIGH && timer_elapsed(timer, 2000))
            {
               state = ENIGME_3;
            }
        break;

        case D_ENI_4:   
            if(digitalRead(DOWN)== HIGH && timer_elapsed(timer, 2000))
            {
               state = ENIGME_4;
            }
        break;
    }
}