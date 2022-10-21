#include "initialisation.h"
#include "affichage.h"
// #include "general.h"
#include "gestionObjets.h"
// #include "riposte.h"
// #include "resolutionNulle.h"
// #include "apprentissage.h"
// #include "analyseVague.h"

int main()
{
    srand(time(NULL));

    // int listeCompo[20][3] = {{BUGFIRE, -1, -1}, {FLY, -1, -1}, {MANTIS, -1, -1}, {BUGFIRE, BUGFIRE, -1}, {FLY, FLY, -1}, {MANTIS, MANTIS, -1}, {BUGFIRE, FLY, -1}, {BUGFIRE, MANTIS, -1}, {FLY, MANTIS, -1}, {BUGFIRE, BUGFIRE, BUGFIRE}, {FLY, FLY, FLY}, {MANTIS, MANTIS, MANTIS}, {BUGFIRE, BUGFIRE, FLY}, {BUGFIRE, BUGFIRE, MANTIS}, {BUGFIRE, FLY, FLY}, {FLY, FLY, MANTIS}, {BUGFIRE, MANTIS, MANTIS}, {FLY, MANTIS, MANTIS}, {BUGFIRE, FLY, MANTIS}};
    // // int listeCompo[34][4] = {{BUGFIRE, -1, -1, -1}, {FLY, -1, -1, -1}, {MANTIS, -1, -1, -1}, {BUGFIRE, BUGFIRE, -1, -1}, {FLY, FLY, -1, -1}, {MANTIS, MANTIS, -1, -1}, {BUGFIRE, FLY, -1, -1}, {BUGFIRE, MANTIS, -1, -1}, {FLY, MANTIS, -1, -1}, {BUGFIRE, BUGFIRE, BUGFIRE, -1}, {FLY, FLY, FLY, -1}, {MANTIS, MANTIS, MANTIS, -1}, {BUGFIRE, BUGFIRE, FLY, -1}, {BUGFIRE, BUGFIRE, MANTIS, -1}, {BUGFIRE, FLY, FLY, -1}, {FLY, FLY, MANTIS, -1}, {BUGFIRE, MANTIS, MANTIS, -1}, {FLY, MANTIS, MANTIS, -1}, {BUGFIRE, FLY, MANTIS, -1}, {BUGFIRE, BUGFIRE, BUGFIRE, BUGFIRE}, {FLY, FLY, FLY, FLY}, {MANTIS, MANTIS, MANTIS, MANTIS}, {BUGFIRE, BUGFIRE, BUGFIRE, FLY}, {BUGFIRE, BUGFIRE, BUGFIRE, MANTIS}, {BUGFIRE, FLY, FLY, FLY}, {FLY, FLY, FLY, MANTIS}, {BUGFIRE, MANTIS, MANTIS, MANTIS}, {FLY, MANTIS, MANTIS, MANTIS}, {BUGFIRE, BUGFIRE, MANTIS, MANTIS}, {BUGFIRE, BUGFIRE, FLY, FLY}, {BUGFIRE, BUGFIRE, FLY, MANTIS}, {FLY, FLY, MANTIS, MANTIS}, {BUGFIRE, FLY, FLY, MANTIS}, {BUGFIRE, FLY, MANTIS, MANTIS}};



    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    SDL_DisplayMode screen;
    SDL_Rect tailleFenetre;

    // TTF_Font *tabPolices[nbrPolices];

    spriteBase_t *spritesDeBase[NBRTEXTURES];
    spriteCourant_t *listeCourants[tailleMaxSpritesCourants]; // le maximum de sprites courants à afficher
    // combattant_t *listeCombattants[NBRMAXCOMBATTANTS];

    // int listeCompo[20][3] = {{BUGFIRE, NULL, NULL}, {FLY, NULL, NULL}, {MANTIS, NULL, NULL}, {BUGFIRE, BUGFIRE, NULL}, {FLY, FLY, NULL}, {MANTIS, MANTIS, NULL}, {BUGFIRE, FLY, NULL}, {BUGFIRE, MANTIS, NULL}, {FLY, MANTIS, NULL}, {BUGFIRE, BUGFIRE, BUGFIRE}, {FLY, FLY, FLY}, {MANTIS, MANTIS, MANTIS}, {BUGFIRE, BUGFIRE, FLY}, {BUGFIRE, BUGFIRE, MANTIS}, {FLY, FLY, BUGFIRE}, {FLY, FLY, MANTIS}, {MANTIS, MANTIS, BUGFIRE}, {MANTIS, MANTIS, FLY}, {BUGFIRE, FLY, MANTIS}};

    // ************** Initialisation de la SDL  + gestion de l'échec possible *********
    // ********************************************************************************

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
    {
        SDL_Log("Error : SDL initialisation - %s\n", SDL_GetError()); // l'initialisation de la SDL a échoué
        exit(EXIT_FAILURE);
    }

    //************************ Chargement musique *************************************

    // Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    /* Chargement musique */
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    Mix_Music *accueil = Mix_LoadMUS("./Musiques/accueil.mp3");
    Mix_Music *lore1 = Mix_LoadMUS("./Musiques/lore1.mp3");
    Mix_Music *lore2 = Mix_LoadMUS("./Musiques/lore2.mp3");
    Mix_Music *lore3 = Mix_LoadMUS("./Musiques/lore3.mp3");
    Mix_Music *jeu = Mix_LoadMUS("./Musiques/jeu.mp3");

    // ***************************** Texte ********************************************

    // if (TTF_Init() < 0)
    //     fprintf(stderr, "Unable to initialize TTF:  %s\n", SDL_GetError());

    // *************************  Gestion des fenetres   *****************************

    SDL_GetCurrentDisplayMode(0, &screen);
    tailleFenetre.w = screen.w * coefReducEcran; // réduction fenetre
    tailleFenetre.h = screen.h * coefReducEcran;

    //  ************************* Création de la fenêtre *************************

    window = SDL_CreateWindow("Insects_VS_Mechas", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, tailleFenetre.w, tailleFenetre.h, SDL_WINDOW_RESIZABLE);
    if (window == NULL)
        end_sdl(0, "ERROR WINDOW CREATION", window, renderer, spritesDeBase, listeCourants);

    //  ************************* Création du renderer *************************

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
        end_sdl(0, "ERROR RENDERER CREATION", window, renderer, spritesDeBase, listeCourants);

    // ********************************************************************************
    // ********************************************************************************

    init(window, renderer, spritesDeBase, listeCourants);

    SDL_bool program_on = SDL_TRUE; // Booléen pour dire que le programme doit continuer
    SDL_Event event;                // c'est le type IMPORTANT !!

    // ETATJEU = ACCUEIL;
    int ETATJEU = ACCUEIL;
    int changermusique = 1;
    // int compteurAnimationMort = 0;
    // int nombreInsectesMorts = 0;
    // int numeroDeVague = 0;
    // int compteurDeCoups = 0;
    // int modeAffichage = 1;



    creerSpriteCourant(spritesDeBase, listeCourants, indiceFondAccueil, 0.0, 0.0);

    while (program_on)
    {
        // Voilà la boucle des évènements
        int interessant = 0;
        // int choixFait = 0;

        // *************************  Gestion des evenements *****************************
        //
        // *******************************************************************************

        while ((interessant == 0) && (SDL_PollEvent(&event)))
        { // tant que la file d'évènements n'est pas vide : défiler l'élément en tête et l'on a pas d'évènements interessants à traiter
            // de file dans 'event'
            switch (event.type)
            {
            case SDL_QUIT:
                interessant = 1;        // Un évènement simple, on a cliqué sur la x de la fenêtre
                program_on = SDL_FALSE; // Il est temps d'arrêter le programme
                break;
            case SDL_KEYUP: // Le type de event est : une touche relâchée

                switch (event.key.keysym.sym)
                { // la touche appuyée est ...
                case SDLK_ESCAPE:
                    interessant = 1;
                    program_on = SDL_FALSE;
                    break;
                case SDLK_SPACE:
                    if (ETATJEU == ACCUEIL)
                    {
                        cleanListeCourants(listeCourants);
                        creerSpriteCourant(spritesDeBase, listeCourants, indiceLore1, 0.0, 0.0);
                        // numeroDeVague = 0;
                        ETATJEU = LORE1;
                    }
                    else if (ETATJEU == LORE1)
                    {
                        cleanListeCourants(listeCourants);
                        creerSpriteCourant(spritesDeBase, listeCourants, indiceLore2, 0.0, 0.0);
                        ETATJEU = LORE2;
                    }
                    else if (ETATJEU == LORE2)
                    {
                        cleanListeCourants(listeCourants);
                        creerSpriteCourant(spritesDeBase, listeCourants, indiceLore3, 0.0, 0.0);
                        ETATJEU = LORE3;
                    }
                    else if (ETATJEU == LORE3)
                    {
                        cleanListeCourants(listeCourants);
                        // cleanListeCombattants(listeCombattants);
                        creerSpriteCourant(spritesDeBase, listeCourants, indiceFond3, 0.0, 0.0);
                        creerSpriteCourant(spritesDeBase, listeCourants, indiceFond2, 0.0, 0.0);
                        creerSpriteCourant(spritesDeBase, listeCourants, indiceFond1, 0.0, 0.0);
                        // creerSpriteCourant(spritesDeBase, listeCourants, indiceBatiment2coupe, 0.0, 0.0);
                        // creerSpriteCourant(spritesDeBase, listeCourants, indiceFond, 0.0, 0.0);
                        creerSpriteCourant(spritesDeBase, listeCourants, indicePasserelleAnimee, 0.0, 0.0);
                        creerSpriteCourant(spritesDeBase, listeCourants, indiceBatiment2, -0.12*wFenetreVirtuelle, 0.27*hFenetreVirtuelle);
                        // creationVague(spritesDeBase, listeCombattants, listeCourants, modeAffichage);
                        // numeroDeVague++;
                        ETATJEU = ARRIVEEVAGUE;
                    }
                    interessant = 1;
                    changermusique = 1;
                    break;
                case SDLK_q:

                    if (ETATJEU != ACCUEIL)
                    {
                        cleanListeCourants(listeCourants);
                        creerSpriteCourant(spritesDeBase, listeCourants, indiceFondAccueil, 0.0, 0.0);
                        ETATJEU = ACCUEIL;
                    }
                    interessant = 1;
                    changermusique = 1;
                    break;
                case SDLK_g:
                       
                    break;
                case SDLK_p:
                       
                    break;
                case SDLK_m:
                       
                    break;
                case SDLK_t:

                    break;
                default: // L'évènement défilé ne nous intéresse pas
                    break;
                }
            default:
                break;
            }
        }

        switch (ETATJEU)
        {
        case ERREUR:
            // printf("ETATJEU == ERREUR\n");
            break;
        case ACCUEIL:
            // printf("Accueil\n");
            if (changermusique == 1)
            {
                Mix_PlayMusic(accueil, -1);
            }
            animation(window, renderer, listeCourants);
            break;
        case LORE1:
            // printf("lore1\n");
            if (changermusique == 1)
            {
                Mix_PlayMusic(lore1, 0);
            }
            animation(window, renderer, listeCourants);
            break;
        case LORE2:
            // printf("lore2\n");
            if (changermusique == 1)
            {
                Mix_PlayMusic(lore2, 0);
            }
            animation(window, renderer, listeCourants);

            break;
        case LORE3:
            // printf("lore3\n");
            if (changermusique == 1)
            {
                Mix_PlayMusic(lore3, 0);
            }
            animation(window, renderer, listeCourants);

            break;
        case ARRIVEEVAGUE:
            // printf("ARRIVEEVAGUE\n");
            // printf("vague\n");
            // if (changermusique == 1)
            // {
            //     Mix_PlayMusic(jeu, -1);
            // }
          animation(window, renderer, listeCourants);
            break;
        case ATTENTECHOIXRIPOSTE:
            // printf("attente riposte\n");
            animation(window, renderer, listeCourants);
            break;
        case ARRIVEERIPOSTE:
            // printf("ARRIVEERIPOSTE\n");
           
            break;
        case ATTAQUESDEFENSEUR:
            // printf("attaques défenseur\n");
           
            break;
        case ANIMATIONMORT:
            
            break;
        case FINDEVAGUE:
            // printf("fin de vague\n");
            animation(window, renderer, listeCourants);
            ETATJEU = FINJEU;
            break;
        case FINJEU:
            // printf("fin du jeu\n");
            cleanListeCourants(listeCourants);
            creerSpriteCourant(spritesDeBase, listeCourants, indiceEcranFin, 0.0, 0.0);
            animation(window, renderer, listeCourants);
            // printf("FIN");
            break;
        default:
            ETATJEU = ERREUR;
            break;
        }

        changermusique = 0;

        if((ETATJEU >= ARRIVEEVAGUE && ETATJEU <= ANIMATIONMORT) || (ETATJEU == ATTAQUESDEFENSEUR)){
            faireAvancerParalaxe(listeCourants);
        }

        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
        SDL_Delay(20);
        // printf(("hello\n"));
        // for (int i = 0; i < NBRMAXCOMBATTANTS; i++)
        // {
        //     printf("listeCombattants[%d] == %d\n", i, listeCombattants[i] == NULL);
        // }
    }

    // printf(" juste avant end_sdl\n");
    end_sdl(1, "FIN NORMALE", window, renderer, spritesDeBase, listeCourants);
    Mix_CloseAudio();
    return 0;
}