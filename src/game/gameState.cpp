#ifndef juego_Cabecera
#define juego_Cabecera

#include <iostream>
#include "../headers/movements.h"
#include "../position.cpp"
/*
    Regresará:
        0 -> si no hay ganador actualmente
        1 -> si ganaron blancas
        2 -> si ganaron negras
        3 -> si hay tablas
        4 -> si hay doble mate :|
*/
char checkLine(pair<int,int> kingCoord,pair<int,int> dir,vector<vector<int> > &analysisPosition,vector<vector<bool> >&oncheckCells){
    if(kingCoord.first<1 || kingCoord.first>8 ||kingCoord.second<1 || kingCoord.second>8)return 0;
    oncheckCells[kingCoord.first][kingCoord.second]=1;
    if(analysisPosition[kingCoord.first][kingCoord.second]){
        oncheckCells[kingCoord.first][kingCoord.second]=1;
        return analysisPosition[kingCoord.first][kingCoord.second];
    }
    return checkLine({kingCoord.first+dir.first,kingCoord.second+dir.second},dir,analysisPosition,oncheckCells);
}
/*bool whiteStateAnalysis(vector<vector<int> > &analysisPosition,vector<vector<bool> > &uncheckCells){
    int xking,yking;
    for(int i=1;i<=8;i++){
        for(int j=1;j<=8;j++){
            if(analysisPosition[i][j] == 'K'){
                xking = j;
                yking = i;
            }
        }
    }
    for(auto z: kingMoves){
        char pieceElement = checkLine({yking,xking},z,analysisPosition,uncheckCells);
        if(!pieceElement)continue;
        if(!z.first || !z.second){
            if(pieceElement == 'r' || pieceElement == 'q'){
                
            }
        }
    }
}*/

void extendPieceMovement(vector<vector<short> > &actualDomain,pair<int,int> piecePositionEX,pair<int,int> &dir,chessPosition &analysisPositon){
    if(piecePositionEX.first<0 || piecePositionEX.second<0 || piecePositionEX.first>8 || piecePositionEX.second>8)return;
    actualDomain[piecePositionEX.first][piecePositionEX.second]++;
    if(analysisPositon.position[piecePositionEX.first][piecePositionEX.second])return;
    extendPieceMovement(actualDomain,{piecePositionEX.first+dir.first,piecePositionEX.second+dir.second},dir,analysisPositon);
}

void extendPieceMovementUnit(vector<vector<short> > &actualDomain,pair<int,int> piecePositionEX){
    if(piecePositionEX.first<0 || piecePositionEX.second<0 || piecePositionEX.first>8 || piecePositionEX.second>8)return;
    actualDomain[piecePositionEX.first][piecePositionEX.second]++;
}


void extendPieceMovementBool(vector<vector<bool> > &actualDomain,pair<int,int> piecePositionEX,pair<int,int> &dir,chessPosition &analysisPositon){
    if(piecePositionEX.first<0 || piecePositionEX.second<0 || piecePositionEX.first>8 || piecePositionEX.second>8)return;
    actualDomain[piecePositionEX.first][piecePositionEX.second]=1;
    if(analysisPositon.position[piecePositionEX.first][piecePositionEX.second])return;
    extendPieceMovementBool(actualDomain,{piecePositionEX.first+dir.first,piecePositionEX.second+dir.second},dir,analysisPositon);
}

void extendPieceMovementUnitBool(vector<vector<bool> > &actualDomain,pair<int,int> piecePositionEX){
    if(piecePositionEX.first<0 || piecePositionEX.second<0 || piecePositionEX.first>8 || piecePositionEX.second>8)return;
    actualDomain[piecePositionEX.first][piecePositionEX.second]=1;
}



vector<vector<short> > stateOfDominion(chessPosition &AnalysisPosition,int pieceKingdom){
    vector<vector<short> > actualDomain(9,vector<short>(9));
    for(auto z:AnalysisPosition.existentPieces[pieceKingdom]){
        switch(z.second){
            case 'r':
            case 'R':
                for(auto dir:rookMoves){
                    extendPieceMovement(actualDomain,{z.first.first+dir.first,z.first.second+dir.second},dir,AnalysisPosition);
                }
                break;
            case 'n':
            case 'N':
                for(auto dir:knightMoves)
                    extendPieceMovementUnit(actualDomain,{z.first.first+dir.first,z.first.second+dir.second});
                break;
            case 'b':
            case 'B':
                for(auto dir:bishopMoves){
                    extendPieceMovement(actualDomain,{z.first.first+dir.first,z.first.second+dir.second},dir,AnalysisPosition);
                }
                break;
            case 'Q':
            case 'q':
                for(auto dir:queenMoves){
                    extendPieceMovement(actualDomain,{z.first.first+dir.first,z.first.second+dir.second},dir,AnalysisPosition);
                }
                break;
            case 'p':
            case 'P':
                extendPieceMovementUnit(actualDomain,{z.first.first+pawnMoves[pieceKingdom][0].first
                                                    ,z.first.second+pawnMoves[pieceKingdom][0].second});
                extendPieceMovementUnit(actualDomain,{z.first.first+pawnMoves[pieceKingdom][2].first
                                                    ,z.first.second+pawnMoves[pieceKingdom][2].second});
                break;
            case 'K':
            case 'k':
                for(auto dir:kingMoves){
                    extendPieceMovementUnit(actualDomain,{z.first.first+dir.first,z.first.second+dir.second});
                }
        }
    }
    cout<<"Dominio de ";
    (pieceKingdom)?cout<<"Negras\n":cout<<"Blancas\n";
    for(int i=1;i<=8;i++){
        for(int j=1;j<=8;j++){
            cout<<actualDomain[i][j]<<" ";
        }
        cout<<"\n";
    }
    return actualDomain;
}

//Regresa la matriz de movimientos posibles por parte de un bando que puede o no tapar un jaque
vector<vector<bool> > StopCheckMovementsAdquisition(chessPosition &AnalysisPosition,int pieceKingdom){
    vector<vector<bool> > actualDomain(9,vector<bool>(9));
    for(auto z:AnalysisPosition.existentPieces[pieceKingdom]){
        switch(z.second){
            case 'r':
            case 'R':
                for(auto dir:rookMoves){
                    extendPieceMovementBool(actualDomain,{z.first.first+dir.first,z.first.second+dir.second},dir,AnalysisPosition);
                }
                break;
            case 'n':
            case 'N':
                for(auto dir:knightMoves)
                    extendPieceMovementUnitBool(actualDomain,{z.first.first+dir.first,z.first.second+dir.second});
                break;
            case 'b':
            case 'B':
                for(auto dir:bishopMoves){
                    extendPieceMovementBool(actualDomain,{z.first.first+dir.first,z.first.second+dir.second},dir,AnalysisPosition);
                }
                break;
            case 'Q':
            case 'q':
                for(auto dir:queenMoves){
                    extendPieceMovementBool(actualDomain,{z.first.first+dir.first,z.first.second+dir.second},dir,AnalysisPosition);
                }
                break;
            case 'p':
            case 'P':
                extendPieceMovementUnitBool(actualDomain,{z.first.first+pawnMoves[pieceKingdom][1].first
                                                    ,z.first.second+pawnMoves[pieceKingdom][1].second});
        }
    }
    cout<<"Dominio de ";
    (pieceKingdom)?cout<<"Negras\n":cout<<"Blancas\n";
    for(int i=1;i<=8;i++){
        for(int j=1;j<=8;j++){
            cout<<actualDomain[i][j]<<" ";
        }
        cout<<"\n";
    }
    return actualDomain;
}

int actualState(chessPosition &analysisPosition){
    vector<vector<short> > domain[2];
    vector<vector<bool> > uncheckCells;
    vector<vector<bool> > stopMovements[2];
    uncheckCells.clear();
    uncheckCells.resize(9,vector<bool>(9));
    domain[0].clear();
    domain[1].clear();
    domain[0].resize(9,vector<short>(9));
    domain[1].resize(9,vector<short>(9));


    stopMovements[0].clear();
    stopMovements[1].clear();
    stopMovements[0].resize(9,vector<bool>(9));
    stopMovements[1].resize(9,vector<bool>(9));
    bool HorizontalKing = 0;
    bool VerticalKing = 0;
    bool NormalDiagonalKing = 0;
    bool inverseDiagonalKing = 0;
    domain[0] = stateOfDominion(analysisPosition,0);
    domain[1] = stateOfDominion(analysisPosition,1);

    stopMovements[0] = StopCheckMovementsAdquisition(analysisPosition,0);
    stopMovements[1] = StopCheckMovementsAdquisition(analysisPosition,1);
    return 1;
}

#endif