#include "affichage.h"


/*
void creationTexte(char texte[], char style[], char police[], SDL_Renderer *renderer, int taille, int x, int y, int opacite)
{

    TTF_Font *font = NULL;               // la variable 'police de caractère'
    font = TTF_OpenFont(police, taille); // La police à charger, la taille désirée
    if (font == NULL)
        fprintf(stderr, "Can't load font  %s\n", SDL_GetError());

    if (strcmp(style, "normal") == 0)
    { // si on veut le texte en style normal
        TTF_SetFontStyle(font, TTF_STYLE_NORMAL);
    }

    if (strcmp(style, "surligne") == 0)
    { // si on veut le texte surligné
        TTF_SetFontStyle(font, TTF_STYLE_UNDERLINE);
    }

    if (strcmp(style, "italique") == 0)
    { // si on veut le texte en italique
        TTF_SetFontStyle(font, TTF_STYLE_ITALIC);
    }

    if (strcmp(style, "gras") == 0)
    { // si on veut le texte en gras
        TTF_SetFontStyle(font, TTF_STYLE_BOLD);
    }

    SDL_Color color = {0, 0, 0, opacite};
    SDL_Surface *text_surface = NULL;                          // la surface  (uniquement transitoire)
    text_surface = TTF_RenderText_Blended(font, texte, color); // création du texte dans la surface
    if (text_surface == NULL)
        fprintf(stderr, "Can't create text surface %s\n", SDL_GetError());

    SDL_Texture *text_texture = NULL;                                    // la texture qui contient le texte
    text_texture = SDL_CreateTextureFromSurface(renderer, text_surface); // transfert de la surface à la texture
    if (text_texture == NULL)
        fprintf(stderr, "Can't create texture from surface %s\n", SDL_GetError());
    SDL_FreeSurface(text_surface); // la texture ne sert plus à rien

    SDL_Rect pos = {x, y, 1000, 1000};                          // rectangle où le texte va être prositionné
    SDL_QueryTexture(text_texture, NULL, NULL, &pos.w, &pos.h); // récupération de la taille (w, h) du texte
    SDL_RenderCopy(renderer, text_texture, NULL, &pos);
    SDL_DestroyTexture(text_texture);
}
*/

void animation(SDL_Rect window_dimensions, SDL_Renderer *renderer, spriteCourant_t *listeCourants[tailleMaxSpritesCourants])
{
    // SDL_Rect window_dimensions = {0}, source = {0}, destination = {0};
    // SDL_GetWindowSize(window, &window_dimensions.w, &window_dimensions.h); // Récupération des dimensions de la fenêtre
    SDL_Rect source = {0}, destination = {0};

    // printf("debut animation\n");
    for (int i = 0; i < tailleMaxSpritesCourants; i++)
    {
        if (listeCourants[i] != NULL)
        {
            source.x = (listeCourants[i]->numImageEnCours % listeCourants[i]->spriteDeBase->nbrImagesHorizontales) * listeCourants[i]->spriteDeBase->wImageSprite;
            source.y = (listeCourants[i]->numImageEnCours / listeCourants[i]->spriteDeBase->nbrImagesHorizontales) * listeCourants[i]->spriteDeBase->hImageSprite;
            source.w = listeCourants[i]->spriteDeBase->wImageSprite;
            source.h = listeCourants[i]->spriteDeBase->hImageSprite;

            destination.x = (int)(((float)window_dimensions.w * listeCourants[i]->posXfenetreVirtuelle)/(float)wFenetreVirtuelle);
            destination.y = (int)(((float)window_dimensions.h * listeCourants[i]->posYfenetreVirtuelle)/(float)hFenetreVirtuelle);
            destination.w = window_dimensions.w * listeCourants[i]->spriteDeBase->wCoefReductionDestination;
            destination.h = window_dimensions.h * listeCourants[i]->spriteDeBase->hCoefReductionDestination;

            // printf("animation\n");
            if (listeCourants[i]->retardateurRalenti <= 0)
            {
                listeCourants[i]->numImageEnCours++;
                if (listeCourants[i]->numImageEnCours >= listeCourants[i]->spriteDeBase->nbrImagesHorizontales * listeCourants[i]->spriteDeBase->nbrImagesVerticales)
                {   
                    if(listeCourants[i]->spriteDeBase->animationInfinie == 0){
                        listeCourants[i]->animationTerminee = 1;
                    }
                    listeCourants[i]->numImageEnCours = 0;
                }
                listeCourants[i]->retardateurRalenti = listeCourants[i]->spriteDeBase->ralenti;
            }
            else
            {
                listeCourants[i]->retardateurRalenti--;
            }

            SDL_RenderCopy(renderer, listeCourants[i]->spriteDeBase->textureSprite, &source, &destination);
            // printf("apres copy\n");
            
        }
    }
}