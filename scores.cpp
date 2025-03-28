#include "scores.h"

#include <string.h>
#include <stdio.h>

#define SCORES_NAME_MAX_LENGTH 100

struct _scores_entry
{
    char name[SCORES_NAME_MAX_LENGTH];
    int score;
};

typedef struct _scores_entry scores_entry;

scores_entry hall_of_fame[SCORES_MAX];

void scores_init()
{
    for (int i = 0; i < SCORES_MAX; i++)
    {
        hall_of_fame[i].score = 0;
        hall_of_fame[i].name[0] = '\0';
    }
}

void scores_shut()
{
    // Nothing to do
}

int scores_get_value(int index)
{
    return hall_of_fame[index].score;   
}

int scores_add(char name[], int score)
{
    if(score < hall_of_fame[SCORES_MAX - 1].score)
    {
        return -1;
    }
    int i;

    for(i = SCORES_MAX - 1; i > 0; i--)
    {
        if(score < hall_of_fame[i - 1].score)
        {
            break;
        }
        hall_of_fame[i] = hall_of_fame[i - 1];
    }
    hall_of_fame[i].score = score;
    strncpy(hall_of_fame[i].name, name, SCORES_NAME_MAX_LENGTH);
    return i;
}