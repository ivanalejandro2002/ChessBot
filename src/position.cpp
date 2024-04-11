#ifndef position_Cabecera
#define position_Cabecera
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

vector<vector<char> > position(9,vector<char>(9));
// 0 blancas, 1 negras
bool turn;
bool possibleWhiteKingCastling;
bool possibleBlackKingCastling;
bool possibleWhiteQueenCastling;
bool possibleBlackQueenCastling;
bool enpassant;
int rowEnpassant,columnEnpassant;
int halfmove;
int fullmove;
bool valid(char co){
    if((co>='0' && co<='9') || co=='r' || co=='R' || co=='k'
                            || co=='K' || co=='q' || co=='Q'
                            || co=='n' || co=='N' || co=='b'
                            || co=='B' || co=='p' || co=='P')return true;
    return false;
}
bool verif(string &cad){
    int i=0;
    int bk,wk;
    bk = wk = 0;
    int levels = 0;
    int perRow;
    while(i<cad.size() && cad[i]!=' '){
        perRow = 0;
        levels++;
        while(i<cad.size() && cad[i]!='/' && cad[i]!=' '){
            perRow++;
            if(!valid(cad[i]))return false;
            if(cad[i]>='1' && cad[i]<='8')perRow+=cad[i]-'1';
            if(cad[i]=='k')bk++;
            if(cad[i]=='K')wk++;
            i++;
        }
        if(perRow!=8)return false;
        if(i<cad.size() && cad[i]=='/')i++;
    }
    

    if(levels!=8)return false;
    if(bk!=1 || wk!=1)return false;
    
    i++;
    if(i >= cad.size())return false;
    if(cad[i] != 'w' && cad[i] != 'b' && cad[i]!='-')return false;
    if(cad[i]!='-'){
        if(cad[i] == 'w')turn = 0;
        else turn = 1;
    }
    i+=2;
    if(i>=cad.size())return false;
    
    if(cad[i]!='-'){
        if(cad[i]=='k' || cad[i]=='K' || cad[i]=='q' || cad[i]=='Q'){
            while(i<cad.size() && cad[i]!=' '){
                if(!(cad[i]=='k' || cad[i]=='K' || cad[i]=='q' || cad[i]=='Q'))return false;
                i++;
            }
        }
        i++;
    }else{
        i+=2;
    }

    if(i>=cad.size())return false;
    
    if(cad[i]!='-'){
        if(cad[i]>='a' || cad[i]<='h'){
            if(i>=cad.size()-1)return false;
            if(cad[i+1]<'1' || cad[i+1]>'8')return false;
            if(i<cad.size()-3 && cad[i+2]!=' ')return false;
            i+=3;
        }
    }else{
        i+=2;
    }
    if(i>=cad.size())return false;
    
    while(i<cad.size() && cad[i]!=' '){
        if(cad[i]<'0' || cad[i]>'9')return false;
        i++;
    }
    i++;
    if(i>=cad.size())return false;
    
    while(i<cad.size() && cad[i]!=' '){
        if(cad[i]<'0' || cad[i]>'9')return false;
        i++;
    }
    if(i<cad.size()-1)return false;
    return true;
}
void arrangeBoard(string &cad){
    possibleBlackKingCastling = possibleBlackQueenCastling = possibleWhiteKingCastling = possibleWhiteQueenCastling = 0;
    enpassant = 0;
    halfmove = fullmove = 0;
    int i=0;
    int boardRow,boardColumn;
    boardRow = 1;
    boardColumn = 1;
    while(i<cad.size() && cad[i]!=' '){
        boardColumn = 1;
        while(cad[i]!='/' && cad[i]!=' '){
            if(cad[i]>='1' && cad[i]<='8')boardColumn+=cad[i]-'1';
            else position[boardRow][boardColumn]=cad[i];
            boardColumn++;
            i++;
        }
        boardRow++;
        if(cad[i]=='/')
        i++;
    }
    i++;

    if(cad[i]=='w')turn=0;
    else turn=1;
    i+=2;
    
    if(cad[i]!='-'){
        if(cad[i]=='k' || cad[i]=='K' || cad[i]=='q' || cad[i]=='Q'){
            while(i<cad.size() && cad[i]!=' '){
                switch(cad[i]){
                    case 'K':
                        possibleWhiteKingCastling = 1;
                        break;
                    case 'Q':
                        possibleWhiteQueenCastling = 1;
                        break;
                    case 'k':
                        possibleBlackKingCastling = 1;
                        break;
                    case 'q':
                        possibleBlackQueenCastling = 1;
                }
                i++;
            }
        }
        i++;
    }else{
        i+=2;
    }
    i++;

    if(cad[i]!='-'){
        enpassant = 1;
        columnEnpassant = cad[i]-'a'+1;
        rowEnpassant = cad[i+1]-'0';
        i+=3;
    }else{
        i+=2;
    }

    while(i<cad.size() && cad[i]!=' '){
        halfmove*=10;
        halfmove+=cad[i]-'0';
        i++;
    }
    i++;

    while(i<cad.size() && cad[i]!=' '){
        fullmove*=10;
        fullmove+=cad[i]-'0';
        i++;
    }
}
void lectura(){
    ifstream datos;
    datos.open("data/FEN.txt");
    string cad;
    getline(datos,cad);
    if(!verif(cad)){
        cout<<"Error: La FEN ingresada es incorrecta";
        return;
    }
    arrangeBoard(cad);
}
#endif