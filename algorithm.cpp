#include"algorithm.h"

std::stack<Move> previousMoves;
bool backtracked = false;

Coordinates::Coordinates()
{

}

Coordinates::Coordinates(int x, int y)
{
    this->x = x;
    this->y = y;
}

Move::Move(int chessBoard[8][8], int attackBoard[8][8], std::queue<Coordinates> leftoverHorsePlacements, int horsesPlaced)
{
    this->leftoverHorsePlacements = leftoverHorsePlacements;
    this->horsesPlaced = horsesPlaced;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            this->chessBoard[i][j] = chessBoard[i][j];
            this->attackBoard[i][j] = attackBoard[i][j];
        }
    }
}

void algorithm()
{
    int chessBoard[8][8]{};
    int attackBoard[8][8]{};

    calculateNumberOfAttacks(attackBoard);

    int horsesPlaced = 0;
    bool boardIsFilled = false;

    while (!boardIsFilled) {
        doNextMove(chessBoard, attackBoard, horsesPlaced);
        backtracked = false;
        horsesPlaced++;

        //printBoard(chessBoard);
        //std::cout << "\n";

        if (horsesPlaced == 12) {
            if (checkIfTheBoardIsFilled(chessBoard)) {
                boardIsFilled = true;
                std::cout << "FINAL ANSWER:" << std::endl;
                printBoard(chessBoard);
            }
            else {
                retrack(chessBoard, attackBoard, horsesPlaced);
            }
        }
    }
}

void doNextMove(int chessBoard[8][8], int attackBoard[8][8], int horsesPlaced)
{
    if (backtracked) {
        Coordinates horseCoordinates = previousMoves.top().leftoverHorsePlacements.front();
        previousMoves.top().leftoverHorsePlacements.pop();
        placeHorse(chessBoard, attackBoard, horseCoordinates);
    }
    else {
        Coordinates horseCoordinates = positionToPlaceHorse(chessBoard, attackBoard, horsesPlaced);
        placeHorse(chessBoard, attackBoard, horseCoordinates);
    }
}

Coordinates positionToPlaceHorse(int chessBoard[8][8], int attackBoard[8][8], int horsesPlaced)
{
    Coordinates toFill = getCoordinatesToFill(attackBoard);
    std::queue<Coordinates> possibleHorsePlacementsQueue = possibleHorsePlacements(chessBoard, toFill);
    Coordinates currentHorsePlacement = possibleHorsePlacementsQueue.front();
    possibleHorsePlacementsQueue.pop();

    saveCurrentState(chessBoard, attackBoard, possibleHorsePlacementsQueue, horsesPlaced);

    return currentHorsePlacement;
}

void printBoard(int board[8][8])
{
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            std::cout << board[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

bool checkIfValidMove(int x, int y)
{
    if (x < 0 || x > 7) {
        return false;
    }
    if (y < 0 || y > 7) {
        return false;
    }
    return true;
}

std::vector<Coordinates> horseMoves(int x, int y)
{
    std::vector<Coordinates> attackedSquares;

    int x1[2] = {-2, 2};
    int y1[2] = {-1, 1};

    int x2[2] = {-1, 1};
    int y2[2] = {-2, 2};

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            if (checkIfValidMove(x1[i] + x, y1[j] + y)) {
                Coordinates coordinates(x1[i] + x, y1[j] + y);
                attackedSquares.push_back(coordinates);
            }
            if (checkIfValidMove(x2[i] + x, y2[j] + y)) {
                Coordinates coordinates(x2[i] + x, y2[j] + y);
                attackedSquares.push_back(coordinates);
            }
        }
    }

    return attackedSquares;
}

void calculateNumberOfAttacks(int attackBoard[8][8])
{
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            std::vector<Coordinates> attackedSquares = horseMoves(i, j);
            for (int h = 0; h < attackedSquares.size(); h++) {
                attackBoard[attackedSquares[h].x][attackedSquares[h].y]++;
            }
        }
    }
}

Coordinates getCoordinatesToFill(int attackBoard[8][8])
{
    int value = 9;
    Coordinates coordinates;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (attackBoard[i][j] < value) {
                value = attackBoard[i][j];
                coordinates.x = i;
                coordinates.y = j;
            }
        }
    }
    return coordinates;
}

std::queue<Coordinates> possibleHorsePlacements(int chessBoard[8][8], Coordinates squareToFill)
{
    std::vector<Coordinates> possiblePlacements = horseMoves(squareToFill.x, squareToFill.y);
    std::queue<Coordinates> possibleHorsePlacementsQueue;

    for (int i = 0; i < possiblePlacements.size(); i++) {
        Coordinates coordinates = possiblePlacements[i];
        if (chessBoard[coordinates.x][coordinates.y] != 2) {
            possibleHorsePlacementsQueue.push(coordinates);
        }
    }
    return possibleHorsePlacementsQueue;
}

void placeHorse(int chessBoard[8][8], int attackBoard[8][8], Coordinates currentHorsePlacement)
{
    chessBoard[currentHorsePlacement.x][currentHorsePlacement.y] = 2;
    std::vector<Coordinates> attackingMoves = horseMoves(currentHorsePlacement.x, currentHorsePlacement.y);
    for (int i = 0; i < attackingMoves.size(); i++) {
        if (chessBoard[attackingMoves[i].x][attackingMoves[i].y] != 2) {
            chessBoard[attackingMoves[i].x][attackingMoves[i].y] = 1;
            attackBoard[attackingMoves[i].x][attackingMoves[i].y] = 9;
        }
        attackBoard[attackingMoves[i].x][attackingMoves[i].y] = 9;
    }
}

bool checkIfTheBoardIsFilled(int chessBoard[8][8])
{
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (chessBoard[i][j] == 0) {
                return false;
            }
        }
    }
    return true;
}

void debugPrint(int chessBoard[8][8], int attackBoard[8][8], int horsesPlaced)
{
    std::cout << "chessBoard:" << std::endl;
    printBoard(chessBoard);
    std::cout << "attackBoard: " << std::endl;
    printBoard(attackBoard);
    std::cout << "horses placed:" << std::endl;
    std::cout << horsesPlaced << std::endl;

    std::cout << "STACK: " << std::endl;
    std::cout << "chessBoard:" << std::endl;
    printBoard(previousMoves.top().chessBoard);
    std::cout << "attackBoard: " << std::endl;
    printBoard(previousMoves.top().attackBoard);
    std::cout << "possibleHorsePlacementsQueue: " << std::endl;
    while (!previousMoves.top().leftoverHorsePlacements.empty()) {
        std::cout << "x: " << previousMoves.top().leftoverHorsePlacements.front().x << " y: " << previousMoves.top().leftoverHorsePlacements.front().y << std::endl;
        previousMoves.top().leftoverHorsePlacements.pop();
    }
    std::cout << "horses placed:" << std::endl;
    std::cout << previousMoves.top().horsesPlaced << std::endl;
}

void saveCurrentState(int chessBoard[8][8], int attackBoard[8][8], std::queue<Coordinates> possibleHorsePlacementsQueue, int horsesPlaced)
{
    Move move(chessBoard, attackBoard, possibleHorsePlacementsQueue, horsesPlaced);
    previousMoves.push(move);
    backtracked = true;
}

void retrack(int chessBoard[8][8], int attackBoard[8][8], int &horsesPlaced)
{
    while (previousMoves.top().leftoverHorsePlacements.empty()) {
        previousMoves.pop();
    }
    horsesPlaced = previousMoves.top().horsesPlaced;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            chessBoard[i][j] = previousMoves.top().chessBoard[i][j];
            attackBoard[i][j] = previousMoves.top().attackBoard[i][j];
        }
    }
    backtracked = true;
}