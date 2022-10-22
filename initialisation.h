#ifndef INITIALISATION_H
#define INITIALISATION_H

#include "general.h"

/** // faire / ** + entrée pour générer ça
 * @brief 
 * 
 * @param window 
 * @param renderer 
 * @param tabPolices 
 * @param spritesDebase 
 */

void init(SDL_Window *window, SDL_Renderer *renderer, spriteBase_t *spritesDebase[NBRTEXTURES], spriteCourant_t *listeCourants[tailleMaxSpritesCourants], perso_t *listePersos[NBRMAXPERSOS]);
void end_sdl(char ok, char const *msg, SDL_Window *window, SDL_Renderer *renderer,spriteBase_t *spritesDebase[NBRTEXTURES], spriteCourant_t *listeCourants[tailleMaxSpritesCourants]);
//void initSprite()

#endif