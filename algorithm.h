#ifndef ALGORITHM_H
#define ALGORITHM_H

#include<iostream>
#include<queue>
#include<stack>
#include<vector>

struct Coordinates {
    int x;
    int y;

    Coordinates();
    Coordinates(int x, int y);
};

struct Move {
    int chessBoard[8][8];
    int attackBoard[8][8];
    std::queue<Coordinates> leftoverHorsePlacements;
    int horsesPlaced;

    Move(int chessBoard[8][8], int attackBoard[8][8], std::queue<Coordinates> leftoverHorsePlacements, int horsesPlaced);
};

void algorithm();
void doNextMove(int chessBoard[8][8], int attackBoard[8][8], int horsesPlaced);
void printBoard(int board[8][8]);
bool checkIfValidMove(int x, int y);
std::vector<Coordinates> horseMoves(int x, int y);
void calculateNumberOfAttacks(int attackBoard[8][8]);
Coordinates getCoordinatesToFill(int attackBoard[8][8]);
std::queue<Coordinates> possibleHorsePlacements(int chessBoard[8][8], Coordinates squareToFill);
void placeHorse(int chessBoard[8][8], int attackBoard[8][8], Coordinates currentHorsePlacement);
bool checkIfTheBoardIsFilled(int chessBoard[8][8]);
void debugPrint(int chessBoard[8][8], int attackBoard[8][8], int horsesPlaced);
Coordinates positionToPlaceHorse(int chessBoard[8][8], int attackBoard[8][8], int horsesPlaced);
void saveCurrentState(int chessBoard[8][8], int attackBoard[8][8], std::queue<Coordinates> possibleHorsePlacementsQueue, int horsesPlaced);
void retrack(int chessBoard[8][8], int attackBoard[8][8], int &horsesPlaced);

#endif