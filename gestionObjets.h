#ifndef GESTIONOBJETS_H
#define GESTIONOBJETS_H

#include "general.h"
// #include "affichage.h"


// void creationVague(spriteBase_t *spritesDeBase[NBRTEXTURES], combattant_t *tableauCombattants[NBRMAXCOMBATTANTS], spriteCourant_t *listeCourant[tailleMaxSpritesCourants], int modeAffichage); // il faut bien que listeCombattants soit vide à l'execution de cette fonction

// void creerAttaquant(spriteBase_t *spritesDeBase[NBRTEXTURES], spriteCourant_t *listeCourants[tailleMaxSpritesCourants], combattant_t *tableauCombattants[NBRMAXCOMBATTANTS], typeCombattant_t typeCombattant, etatCombattant_t etatArrivee, int indiceEmplacement, float posX, float posY, int modeAffichage);
void creerPersonnage(spriteBase_t *spritesDeBase[NBRTEXTURES], spriteCourant_t *listeCourants[tailleMaxSpritesCourants], perso_t *listePersos[NBRMAXPERSOS], float posXfenetreVirtuelle, float posYfenetreVirtuelle);
int creerSpriteCourant(spriteBase_t *spritesDeBase[NBRTEXTURES], spriteCourant_t *listeCourants[tailleMaxSpritesCourants], indicesPNGs indicePNG, int posXfenetreVirtuelle, int posYfenetreVirtuelle);
void faireAvancerPersos(perso_t *listePersos[NBRMAXPERSOS]);
void cleanListeCourants(spriteCourant_t *listeCourants[tailleMaxSpritesCourants]);
bool collisionHitboxPoint(float XcentreHitbox, float YcentreHitbox, float Xpoint, float Ypoint, float rayon);
// void cleanCombattantsDeListeCourants(spriteCourant_t *listeCourants[tailleMaxSpritesCourants]);
// void cleanListeCombattants(combattant_t *tableauCombattants[NBRMAXCOMBATTANTS]);

// int switchEtatCombattants(spriteBase_t *spritesDeBase[NBRTEXTURES], spriteCourant_t *listeCourants[tailleMaxSpritesCourants], combattant_t *tableauCombattants[NBRMAXCOMBATTANTS], typeCombattant_t familleCombattants, etatCombattant_t etatArrivee, int modeAffichage);
// int retourIndicePNG(typeCombattant_t typeCombattants, etatCombattant_t etatArrivee);


// float positionArret(float borneGauche, float borneDroite);
// int faireAvancerCombattants(combattant_t *tableauCombattants[NBRMAXCOMBATTANTS], typeCombattant_t familleCombattants);
void faireAvancerParalaxe(spriteCourant_t *listeCourants[tailleMaxSpritesCourants]);


#endif