#include <iostream>
#include "include/SDL.h"
#include "include/SDL_image.h"
#include "src/printing.cpp"
#include "src/position.cpp"

#undef main
using namespace std;
int main(){
    SDL_Event event;
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer;
    SDL_Renderer *tablero;
    SDL_Init(SDL_INIT_AUDIO);
    SDL_CreateWindowAndRenderer(640,480,0,&window,&renderer);
    SDL_RenderSetScale(renderer,1,1);
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_RenderClear(renderer);
    /*SDL_SetRenderDrawColor(renderer,255,255,255,255);
    SDL_RenderDrawPoint(renderer,30,30);
    SDL_RenderPresent(renderer);
    */
    newPieces("classic",renderer);
    newBoard("classic",renderer);
    lectura();
    impTablero(renderer,event);

    return 0;
}