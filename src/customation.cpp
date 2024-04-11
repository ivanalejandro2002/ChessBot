#ifndef custom_Cabecera
#define custom_Cabecera
#include <iostream>
#include <map>
#include "../include/SDL_image.h"
#include "../include/SDL.h"
using namespace std;

map<char,int> pieceTranslator;

SDL_Texture *cnegra = NULL;
SDL_Texture *cblanca = NULL;
SDL_Texture *pieceSprites[15];

string pieceType = "assets/pieces/classic/";
string boardType = "assets/sets/classic/";

void piecesSpriteInitialization(SDL_Renderer *renderer){
    
    pieceTranslator['p']=1;
    pieceTranslator['k']=2;
    pieceTranslator['b']=3;
    pieceTranslator['r']=4;
    pieceTranslator['q']=5;
    pieceTranslator['k']=6;
    pieceTranslator['P']=7;
    pieceTranslator['K']=8;
    pieceTranslator['B']=9;
    pieceTranslator['R']=10;
    pieceTranslator['Q']=11;
    pieceTranslator['K']=12;
    
    IMG_Init(IMG_INIT_PNG);
    pieceSprites[1]=IMG_LoadTexture(renderer,(pieceType+"b_pawn.png").c_str());
    pieceSprites[2]=IMG_LoadTexture(renderer,(pieceType+"b_knight.png").c_str());
    pieceSprites[3]=IMG_LoadTexture(renderer,(pieceType+"b_bishop.png").c_str());
    pieceSprites[4]=IMG_LoadTexture(renderer,(pieceType+"b_rook.png").c_str());
    pieceSprites[5]=IMG_LoadTexture(renderer,(pieceType+"b_queen.png").c_str());
    pieceSprites[6]=IMG_LoadTexture(renderer,(pieceType+"b_king.png").c_str());
    pieceSprites[7]=IMG_LoadTexture(renderer,(pieceType+"w_pawn.png").c_str());
    pieceSprites[8]=IMG_LoadTexture(renderer,(pieceType+"w_knight.png").c_str());
    pieceSprites[9]=IMG_LoadTexture(renderer,(pieceType+"w_bishop.png").c_str());
    pieceSprites[10]=IMG_LoadTexture(renderer,(pieceType+"w_rook.png").c_str());
    pieceSprites[11]=IMG_LoadTexture(renderer,(pieceType+"w_queen.png").c_str());
    pieceSprites[12]=IMG_LoadTexture(renderer,(pieceType+"w_king.png").c_str());
    for(int i=1;i<=12;i++){
        if(pieceSprites[i]==NULL)cout<<"Error en "<<i<<"\n";
    }
}

void boardSpriteInitialization(SDL_Renderer *renderer){
    IMG_Init(IMG_INIT_PNG);
    cnegra = IMG_LoadTexture(renderer,(boardType+"black.png").c_str());
    cblanca = IMG_LoadTexture(renderer,(boardType+"white.png").c_str());
    
    if(cnegra==NULL){
        cout<<"NO se cargo negro\n";
    }
    if(cnegra==NULL){
        cout<<"NO se cargo blanco\n";
    }
    if(!cnegra || !cblanca)return;
}

void newPieces(string nombre,SDL_Renderer *renderer){
    pieceType = "assets/pieces/"+nombre+'/';
    piecesSpriteInitialization(renderer);
}
void newBoard(string nombre,SDL_Renderer *renderer){
    pieceType = "assets/sets/"+nombre+'/';
    boardSpriteInitialization(renderer);
}

#endif