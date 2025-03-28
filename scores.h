#ifndef _SCORES_H
#define _SCORES_H
/**
 * score max = 10
 */
#define SCORES_MAX 10
/**
 * initialisation du score
 */
void scores_init();
/**
 * ?
 */
void scores_shut();
/**
 * sauver scores
 * @param name nom du tableau où est sauvgarder le score
 * @param scores score à sauvegarder
 */
int scores_add(char name[], int score);
/**
 * retourne le score d'un joueur
 */
int scores_get_value(int index);

#endif