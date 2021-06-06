#include "MapLocation.h"



struct mirror{
    int row;
    int col;
    char side;
    
};
struct Map {

	int row, col;
	char** board;
	struct PlayerCell Pc;
	struct PlayerCell Ec;
    struct mirror m[100];
    int counter;
    int movement; // 1 is left 2 is right 3 is up 4 is down
};

struct Node {
    struct Map m;
    struct Node* next;
};

char getDirection(char Pdir);
void InitializeBoard(int row, int col, int prow, int pcol, char Pdir, int erow, int ecol, char Edir,struct mirror m[],int count);
void PrintBoard();
void PlayGame();
