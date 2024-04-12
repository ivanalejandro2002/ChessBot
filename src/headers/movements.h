#ifndef movements_Cabecera
#define movements_Cabecera
#include <vector>
using namespace std;
vector<pair<int,int> > knightMoves =   {{2,1},{1,2},
                                            {-1,2},{2,-1},
                                            {-2,1},{1,-2},
                                            {-2,-1},{-1,-2}};
vector<pair<int,int> > kingMoves = {{-1,-1},{-1,0},{-1,1},
                                    {0,-1},         {0,1},
                                    {1,-1}, {0,1} ,{1,1}};
vector<pair<int,int> > pawnMoves[2] = {{{-1,-1},{-1,0},{-1,1}},
                                        {{1,-1},{1,0},{1,1}}};
vector<pair<int,int> > rookMoves = {{1,0},{0,1},{-1,0},{0,-1}};
vector<pair<int,int> > bishopMoves = {{1,1},{-1,-1},{-1,1},{1,-1}};

vector<pair<int,int> > queenMoves = {{-1,-1},{-1,0},{-1,1},
                                    {0,-1},         {0,1},
                                    {1,-1}, {0,1} ,{1,1}};
#endif