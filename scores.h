#ifndef _SCORES_H
#define _SCORES_H
/**
 * scores max 10
 */
#define SCORES_MAX 10
/**
 * initialisation du scores
 */
void scores_init();
/**
 * ?
 */
void scores_shut();
/**
 * sauver scores
 * @param name nom du tableau scores à sauvegarder
 * @param scores scores à sauvegarder
 */
int scores_add(char name[], int score);
/**
 * scores 
 */
int scores_get_value(int index);

#endif