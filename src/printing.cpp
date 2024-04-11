#ifndef impresion_Cabecera
#define impresion_Cabecera
#include "../include/SDL.h"
#include "../include/SDL_image.h"
#include <iostream>
#include "headers/parameters.h"
#include "customation.cpp"
#include "position.cpp"
using namespace std;
void impTablero(SDL_Renderer *renderer,SDL_Event &event){
    
    SDL_Rect pieza;
    pieza.x = 0;
    pieza.y = 0;
    pieza.w = SIDECELL;
    pieza.h = SIDECELL;
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            pieza.y = SIDECELL*i+50;
            pieza.x = SIDECELL*j+50;
            if(((i&1)^(j&1)))SDL_RenderCopy(renderer,cblanca,NULL,&pieza);
            else SDL_RenderCopy(renderer,cnegra,NULL,&pieza);
        }
    }

    pieza.h = SIDECELL-8;
    pieza.w = SIDECELL-8;
    for(int i=1;i<=8;i++){
        for(int j=1;j<=8;j++){
            if(pieceTranslator.count(actualPosition.position[i][j])){
                pieza.y = SIDECELL*(i-1)+54;
                pieza.x = SIDECELL*(j-1)+54;
                SDL_RenderCopy(renderer,pieceSprites[pieceTranslator[actualPosition.position[i][j]]],NULL,&pieza);
            }
        }
    }

    while(1){
        SDL_RenderPresent(renderer);
        if(SDL_PollEvent(&event) && event.type == SDL_QUIT)break;
    }
}
#endif