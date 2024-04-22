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
        4 -> blancas en jaque
        5 -> negras en jaque
        6 -> si hay doble mate :|
*/
char checkLine(pair<int,int> kingCoord,pair<int,int> dir,vector<vector<char> > &analysisPosition){
    if(kingCoord.first<1 || kingCoord.first>8 ||kingCoord.second<1 || kingCoord.second>8)return 0;
    if(analysisPosition[kingCoord.first][kingCoord.second]){
        return analysisPosition[kingCoord.first][kingCoord.second];
    }
    return checkLine({kingCoord.first+dir.first,kingCoord.second+dir.second},dir,analysisPosition);
}

void extendDanger(pair<int,int> kingCoord,pair<int,int> dir,vector<vector<char> > &analysisPosition,vector<vector<bool> > &dangerZones){
    if(analysisPosition[kingCoord.first][kingCoord.second]){
        dangerZones[kingCoord.first][kingCoord.second]=1;
        return;
    }
    extendDanger({kingCoord.first+dir.first,kingCoord.second+dir.second},dir,analysisPosition,dangerZones);
    dangerZones[kingCoord.first][kingCoord.second]=1;
}

char pieceInCell(pair<int,int> kingCoord,vector<vector<char> > &analysisPosition){
    if(kingCoord.first<1 || kingCoord.first>8 || kingCoord.second<1 || kingCoord.second>8)return 0;
    return analysisPosition[kingCoord.first][kingCoord.second];
}

bool checkCellSafety(pair<int,int> kingCoord,chessPosition &analysisPosition,vector<vector<short> > &enemyDomain){
    if(kingCoord.first<1 || kingCoord.first>8 || kingCoord.second<1 || kingCoord.second>8)return 1;
    if(!analysisPosition.turn){
        if(analysisPosition.position[kingCoord.first][kingCoord.second]>='A' && analysisPosition.position[kingCoord.first][kingCoord.second]<='Z')return 1;
    }else{
        if(analysisPosition.position[kingCoord.first][kingCoord.second]>='a' && analysisPosition.position[kingCoord.first][kingCoord.second]<='z')return 1;
    }
    return enemyDomain[kingCoord.first][kingCoord.second];
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
    if(!analysisPositon.turn){
        if(analysisPositon.position[piecePositionEX.first][piecePositionEX.second]>='A' &&analysisPositon.position[piecePositionEX.first][piecePositionEX.second]<='Z')return;
    }else{
        if(analysisPositon.position[piecePositionEX.first][piecePositionEX.second]>='a' &&analysisPositon.position[piecePositionEX.first][piecePositionEX.second]<='z')return;
    }
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
    bool HorizontalPin = 0;
    bool VerticalPin = 0;
    bool NormalDiagonalPin = 0;
    bool inverseDiagonalPin = 0;
    char bishop,knight,queen,rook,king;
    if(!pieceKingdom){
        bishop = 'b';
        knight = 'n';
        queen = 'q';
        rook = 'r';
        king = 'K';
    }else{
        bishop = 'B';
        knight = 'N';
        queen = 'Q';
        rook = 'R';
        king = 'k';
    }
    cout<<";)\n";
    for(auto z:AnalysisPosition.existentPieces[pieceKingdom]){
        
        HorizontalPin = 0;
        VerticalPin = 0;
        NormalDiagonalPin = 0;
        inverseDiagonalPin = 0;
        char alignedPiece;
        for(pair<int,int> dir:bishopMoves){
            alignedPiece = checkLine({dir.first+z.first.first,dir.second+z.first.second},dir,AnalysisPosition.position);
            if(alignedPiece== queen || alignedPiece==bishop){
                alignedPiece = checkLine({dir.first*-1+z.first.first,dir.second*-1+z.first.second},{dir.first*-1,dir.second*-1},AnalysisPosition.position);
                if(alignedPiece==king){
                    if(dir.first+dir.second==0){
                        inverseDiagonalPin=1;
                        cout<<z.second<<" esta clavado en sentido inverso diagonal\n";
                    }else{
                        NormalDiagonalPin=1;
                        cout<<z.second<<" esta clavado en sentido diagonal\n";
                    }
                }
            }
        }

        for(pair<int,int> dir:rookMoves){
            alignedPiece = checkLine({dir.first+z.first.first,dir.second+z.first.second},dir,AnalysisPosition.position);
            if(alignedPiece== queen || alignedPiece==rook){
                alignedPiece = checkLine({dir.first*-1+z.first.first,dir.second*-1+z.first.second},{dir.first*-1,dir.second*-1},AnalysisPosition.position);
                if(alignedPiece==king){
                    if(dir.first==0){
                        HorizontalPin=1;
                        cout<<z.second<<" esta clavado en sentido horizontal\n";
                    }else{
                        VerticalPin=1;
                        cout<<z.second<<" esta clavado en sentido vertical\n";
                    }
                }
            }
        }

        switch(z.second){
            case 'r':
            case 'R':
                if(NormalDiagonalPin || inverseDiagonalPin)continue;
                for(auto dir:rookMoves){
                    if(VerticalPin && dir.first==0)continue;
                    if(HorizontalPin && dir.second==0)continue;
                    extendPieceMovementBool(actualDomain,{z.first.first+dir.first,z.first.second+dir.second},dir,AnalysisPosition);
                }
                break;
            case 'n':
            case 'N':
                if(NormalDiagonalPin||VerticalPin||HorizontalPin||inverseDiagonalPin)continue;
                for(auto dir:knightMoves)
                    extendPieceMovementUnitBool(actualDomain,{z.first.first+dir.first,z.first.second+dir.second});
                break;
            case 'b':
            case 'B':
                if(HorizontalPin || VerticalPin)continue;
                for(auto dir:bishopMoves){
                    if(NormalDiagonalPin && dir.first!=dir.second)continue;
                    if(inverseDiagonalPin && dir.first==dir.second)continue;
                    extendPieceMovementBool(actualDomain,{z.first.first+dir.first,z.first.second+dir.second},dir,AnalysisPosition);
                }
                break;
            case 'Q':
            case 'q':
                for(auto dir:queenMoves){
                    if(VerticalPin && (dir.first==0 || dir.second!=0))continue;
                    if(HorizontalPin && (dir.first!=0 || dir.second==0))continue;
                    if(NormalDiagonalPin && dir.first!=dir.second)continue;
                    if(inverseDiagonalPin && dir.first!=dir.second*-1)continue;
                    extendPieceMovementBool(actualDomain,{z.first.first+dir.first,z.first.second+dir.second},dir,AnalysisPosition);
                }
                break;
            case 'p':
            case 'P':
                if(HorizontalPin)continue;
                int ny,nx;
                char minKingdom;
                char maxKingdom;
                
                if(!pieceKingdom){
                    minKingdom='a';
                    maxKingdom='z';
                }else{
                    minKingdom='A';
                    maxKingdom='Z';
                }

                if(!VerticalPin){
                    if(!inverseDiagonalPin){
                        ny = z.first.first+pawnMoves[pieceKingdom][0].first;
                        nx = z.first.second+pawnMoves[pieceKingdom][0].second;
                        
                        if(ny>=1 && ny<=8 && nx>=1 && nx<=8 && AnalysisPosition.position[ny][nx]>=minKingdom && AnalysisPosition.position[ny][nx]<=maxKingdom){
                            extendPieceMovementUnitBool(actualDomain,{ny,nx});
                        }
                    }

                    if(!NormalDiagonalPin){
                        ny = z.first.first+pawnMoves[pieceKingdom][2].first;
                        nx = z.first.second+pawnMoves[pieceKingdom][2].second;
                        if(ny>=1 && ny<=8 && nx>=1 && nx<=8 && AnalysisPosition.position[ny][nx]>=minKingdom && AnalysisPosition.position[ny][nx]<=maxKingdom){
                            extendPieceMovementUnitBool(actualDomain,{ny,nx});
                        }
                    }
                }

                if(NormalDiagonalPin || inverseDiagonalPin)continue;
                ny = z.first.first+pawnMoves[pieceKingdom][1].first;
                nx = z.first.second+pawnMoves[pieceKingdom][1].second;
                if(!AnalysisPosition.position[ny][nx]){
                    extendPieceMovementUnitBool(actualDomain,{z.first.first+pawnMoves[pieceKingdom][1].first
                                                        ,z.first.second+pawnMoves[pieceKingdom][1].second});
                    if((!pieceKingdom && z.first.first==7) || (pieceKingdom && z.first.first==2)){
                        ny += pawnMoves[pieceKingdom][1].first;
                        nx += pawnMoves[pieceKingdom][1].second;
                        if(!AnalysisPosition.position[ny][nx])
                            extendPieceMovementUnitBool(actualDomain,{ny,nx});
                    }
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

vector<vector<bool> > checkChecks(chessPosition &analysisPosition, int &numChecks, bool pieceKingdom,bool &knightChecked,pair<int,int> &KingCoords){
    int targetColor;
    char targetKing;
    if(pieceKingdom==0)targetColor=1;
    else targetColor = 0;
    if(pieceKingdom==0)targetKing='K';
    else targetKing='k';
    
    int xKing,yKing;
    for(int i=1;i<=8;i++){
        for(int j=1;j<=8;j++){
            if(analysisPosition.position[i][j] == targetKing){
                xKing = j;
                yKing = i;
            }
        }
    }
    KingCoords = {yKing,xKing};
    vector<vector<bool> > dangerZones(9,vector<bool>(9));
    char alignedPiece;
    for(auto z:rookMoves){
        alignedPiece = checkLine({yKing+z.first,xKing+z.second},z,analysisPosition.position);
        if(!pieceKingdom){
            if(alignedPiece == 'q' || alignedPiece == 'r'){
                numChecks++;
                extendDanger({yKing+z.first,xKing+z.second},z,analysisPosition.position,dangerZones);
            }
        }else{
            if(alignedPiece == 'Q' || alignedPiece == 'R'){
                numChecks++;
                extendDanger({yKing+z.first,xKing+z.second},z,analysisPosition.position,dangerZones);
            }
        }
    }
    for(auto z:bishopMoves){
        alignedPiece = checkLine({yKing+z.first,xKing+z.second},z,analysisPosition.position);
        cout<<alignedPiece<<"\n";
        if(!pieceKingdom){
            if(alignedPiece=='b' || alignedPiece=='q'){
                numChecks++;
                extendDanger({yKing+z.first,xKing+z.second},z,analysisPosition.position,dangerZones);
            }
        }else if(alignedPiece=='B' || alignedPiece=='Q'){
            numChecks++;
            extendDanger({yKing+z.first,xKing+z.second},z,analysisPosition.position,dangerZones);
        }
    }
    char thatPiece1 = pieceInCell({yKing+pawnMoves[pieceKingdom][0].first,xKing+pawnMoves[pieceKingdom][0].second},analysisPosition.position);
    char thatPiece2 = pieceInCell({yKing+pawnMoves[pieceKingdom][2].first,xKing+pawnMoves[pieceKingdom][2].second},analysisPosition.position);
    if(!pieceKingdom){
        if(thatPiece1=='p'){
            numChecks++;
            dangerZones[yKing+pawnMoves[pieceKingdom][0].first][xKing+pawnMoves[pieceKingdom][0].second]=1;
        }
        if(thatPiece2=='p'){
            numChecks++;
            dangerZones[yKing+pawnMoves[pieceKingdom][2].first][xKing+pawnMoves[pieceKingdom][2].second]=1;
        }
    }else{
        if(thatPiece1=='P'){
            numChecks++;
            dangerZones[yKing+pawnMoves[pieceKingdom][0].first][xKing+pawnMoves[pieceKingdom][0].second]=1;
        }
        if(thatPiece2=='P'){
            numChecks++;
            dangerZones[yKing+pawnMoves[pieceKingdom][2].first][xKing+pawnMoves[pieceKingdom][2].second]=1;
        }
    }
    for(auto z:knightMoves){
        thatPiece1 = pieceInCell({yKing+z.first,xKing+z.second},analysisPosition.position);
        if(!pieceKingdom){
            if(thatPiece1=='n'){
                numChecks++;
                dangerZones[yKing+z.first][xKing+z.second]=1;
                knightChecked=1;
            }
        }else{
            if(thatPiece1=='N'){
                numChecks++;
                dangerZones[yKing+z.first][xKing+z.second]=1;
                knightChecked=1;
            }
        }
    }
    cout<<numChecks<<"::::\n";
    for(int i=1;i<=8;i++){
        for(int j=1;j<=8;j++){
            cout<<dangerZones[i][j];
        }
        cout<<"\n";
    }
    return dangerZones;
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

    int countChecks = 0;
    bool knightChecked = 0;
    bool isMate = 0;
    pair<int,int> kingCoord;
    vector<vector<bool> > checkOrigins = checkChecks(analysisPosition,countChecks,analysisPosition.turn,knightChecked,kingCoord);
    domain[0] = stateOfDominion(analysisPosition,0);
    domain[1] = stateOfDominion(analysisPosition,1);

    stopMovements[0] = StopCheckMovementsAdquisition(analysisPosition,0);
    stopMovements[1] = StopCheckMovementsAdquisition(analysisPosition,1);

    if(countChecks){
        
        if(countChecks==1){
            
            isMate=1;
            for(int i=1;i<=8;i++){
                for(int j=1;j<=8;j++){
                    if(stopMovements[analysisPosition.turn][i][j] && checkOrigins[i][j]){
                        isMate=0;
                    }
                }
            }
            cout<<isMate<<"\n";
            if(isMate){
                for(auto z:kingMoves){
                    isMate&=checkCellSafety({kingCoord.first+z.first,kingCoord.second+z.second},
                                    analysisPosition,domain[!analysisPosition.turn]);
                }
            }
            if(isMate){
                cout<<"Es mate y ganan ";
                if(!analysisPosition.turn){
                    cout<<"negras\n";
                    return 2;
                }else{
                    cout<<"blancas\n";
                    return 1;
                }
            }
            cout<<"Solo es jaque\n";
            if(!analysisPosition.turn)
                return 4;
            else return 5;
        }
        isMate=1;
        for(auto z:kingMoves){
            isMate&=checkCellSafety({kingCoord.first+z.first,kingCoord.second+z.second},
                            analysisPosition,domain[!analysisPosition.turn]);
        }
        if(isMate){
            cout<<"Es mate y ganan ";
            if(!analysisPosition.turn){
                cout<<"negras\n";
                return 2;
            }else{
                cout<<"blancas\n";
                return 1;
            }
        }
        cout<<"Solo es jaque\n";
        if(!analysisPosition.turn)
            return 4;
        else return 5;
    }else{
        bool isStalemate = 1;
        for(int i=1;i<=8;i++){
            for(int j=1;j<=8;j++){
                isStalemate&=!stopMovements[analysisPosition.turn][i][j];
            }
        }
        for(auto z:kingMoves){
            isStalemate&=(bool)(checkCellSafety({kingCoord.first+z.first,kingCoord.second+z.second},
                            analysisPosition,domain[!analysisPosition.turn]));
        }

        if(isStalemate){
            cout<<"Son tablas\n";
            return 3;
        }
    }
    return 0;
}

#endif