#include "Map.h"
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>
struct Map M;

void push(struct Node** ref)
{
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    
    struct Node* last = *ref;

      new_node->m = M;
      new_node->next = NULL;

      if (*ref == NULL) {
        *ref = new_node;
        return;
      }

      while (last->next != NULL)
        last = last->next;

      last->next = new_node;
      return;
}
char getDirection(char Pdir) {
    char dir = 'a';
    if (Pdir == 'l')
    {
        dir = '<';
    }
    else if (Pdir == 'u')
    {
        dir = '^';
    }
    else if (Pdir == 'd')
    {
        dir = 'V';
    }
    else if (Pdir == 'r')
    {
        dir = '>';
    }
    return dir;
}
char getDirection2(char Pdir) {
    char dir = 'a';
    if (Pdir == 'a')
    {
        dir = '<';
    }
    else if (Pdir == 'w')
    {
        dir = '^';
    }
    else if (Pdir == 's')
    {
        dir = 'V';
    }
    else if (Pdir == 'd')
    {
        dir = '>';
    }
    return dir;
}

void InitializeBoard(int row, int col, int prow, int pcol, char Pdir, int erow, int ecol, char Edir,struct mirror m[],int count){
    char dir = getDirection(Pdir);
    
    int i = 0, j = 0;
    M.row = row;
    M.col = col;
    M.board = malloc(row * sizeof(char*));
    for (i = 0; i < row; i++)
        M.board[i] = malloc(col * sizeof(char));
    for (i = 0; i < row; i++)
        for (j = 0; j < col; j++)
            M.board[i][j] = '.';
    M.board[prow][pcol] = dir;
    M.Pc.row = prow;
    M.Pc.col = pcol;
    M.Pc.direction = Pdir;
    dir = getDirection(Edir);
    M.board[erow][ecol] = dir;
    M.Ec.row = erow;
    M.Ec.col = ecol;
    M.Ec.direction = Edir;
    M.counter = 0;
    M.movement = 0;
    for(int i=0; i<count ; i++){
        
        char slash = '/';
        if(m[i].side == 'f')
            slash = '/';
        else
            slash = '\\' ;
        M.m[i].row = m[i].row;
        M.m[i].col  = m[i].col;
        M.m[i].side = m[i].side;
        M.counter++;
        
        M.board[m[i].row][m[i].col] = slash;
    }
}
void PrintBoard() {
    int i = 0, j = 0;
    for (i = 0; i <= M.col + 1; i++)
        printf("*");
    printf("\n");
    for (i = 0; i < M.row; i++)
    {
        printf("*");
        for (j = 0; j < M.col; j++)
        {
            if (j == 0)
            {
                if (M.board[i][j] == '.')
                    printf(" ");
                else
                    printf("%c", M.board[i][j]);
            }
            else {
                if (M.board[i][j] == '.')
                    printf(" ");
                else
                    printf("%c", M.board[i][j]);
            }
        }
        printf("*");
        printf("\n");
    }
    for (i = 0; i <= M.col + 1; i++)
        printf("*");
    printf("\n");
    
    printf("\n\nPress f to shoot\n");
    printf("Press w to move up\n");
    printf("Press s to move down\n");
    printf("Press d to move right\n");
    printf("Press a to move left\n");
    printf("Press l to print log\n");
    
}
void PrintBoard2() {
    int i = 0, j = 0;
    for (i = 0; i <= M.col + 1; i++)
        printf("*");
    printf("\n");
    for (i = 0; i < M.row; i++)
    {
        printf("*");
        for (j = 0; j < M.col; j++)
        {
            if (j == 0)
            {
                if (M.board[i][j] == '.')
                    printf(" ");
                else if (M.board[i][j] == '<' || M.board[i][j] == '>' || M.board[i][j] == '^' || M.board[i][j] == 'V') {
                    printf("%c", M.board[i][j]);
                }
                else
                {
                    printf("\033[0;31m");    /* change font color into red color for the oncoming printf function */
                    printf("%c", M.board[i][j]);
                    printf("\033[0m");
                }
            }
            else {
                if (M.board[i][j] == '.')
                    printf(" ");
                else if (M.board[i][j] == '<' || M.board[i][j] == '>' || M.board[i][j] == '^' || M.board[i][j] == 'V') {
                    printf("%c", M.board[i][j]);
                }
                else
                {
                    printf("\033[0;31m");    /* change font color into red color for the oncoming printf function */
                    printf("%c", M.board[i][j]);
                    printf("\033[0m");
                }
            }
        }
        printf("*");
        printf("\n");
    }
    for (i = 0; i <= M.col + 1; i++)
        printf("*");
    printf("\n");
    printf("\n\nPress f to shoot\n");
    printf("Press w to move up\n");
    printf("Press s to move down\n");
    printf("Press d to move right\n");
    printf("Press a to move left\n");
    printf("Press l to print log\n");

}

bool checkMirror(int r1, int c1){
    
    for(int i=0 ; i< M.counter ; i++){
        
        if(r1 == M.m[i].row && c1 == M.m[i].col)
        {
            return false;
        }
    }
    return true;
    
}
char checkMirror2(int r1, int c1){
    
    for(int i=0 ; i< M.counter ; i++){
        
        if(r1 == M.m[i].row && c1 == M.m[i].col)
        {
            return M.m[i].side;
        }
    }
    return 'n';
    
}


int roww=0;
int coll=0;

bool moveDown(char direction){
    int i=0;
    bool flag = false;
    for (i = roww + 1; i < M.row; i++)
    {
        if (i == M.Ec.row && coll == M.Ec.col) {
            M.board[i][coll] = 'X';
            flag = true;
           
            return true;
            break;
        }
        else if(checkMirror2(i,coll) != 'n'){
            char slash = checkMirror2(i,coll);
            roww=i;
            if(slash == 'f'){
                M.movement = 1;
            }
            else if(slash == 'b'){
                M.movement = 2;
            }
            break;
        }
        else {
            M.movement = 0;
            M.board[i][coll] = '|';
            PrintBoard2();
       
            sleep(1);
            system("clear");
            M.board[i][coll] = '.';
        }
    }
    return false;
}

bool moveUp( char direction){
    int i=0;
    bool flag = false;
    
    
    if (roww > 0)
    {
        for (i = roww - 1; i >= 0; i--)
        {
            if (i == M.Ec.row && coll == M.Ec.col) {
                M.board[i][coll] = 'X';
                flag = true;
             
                return true;
                break;
            }
            else if(checkMirror2(i,coll) != 'n'){
                char slash = checkMirror2(i,coll);
                roww=i;
                if(slash == 'f'){
                    M.movement = 2;
                }
                else if(slash == 'b'){
                    M.movement = 1;
                }
                break;
            }
            else {
                M.movement = 0;
                M.board[i][coll] = '|';
                PrintBoard2();
             
                sleep(1);
                system("clear");
                M.board[i][coll] = '.';
            }
        }
    }
    return false;
}


bool moveLeft( char direction){
    int i=0;
    bool flag = false;
    
    for (i = coll - 1; i >= 0; i--)
    {
        if (roww == M.Ec.row && i == M.Ec.col) {
            M.board[roww][i] = 'X';
            flag = true;
         
            return true;
            break;
        }
        else if(checkMirror2(roww,i) != 'n'){
            char slash = checkMirror2(roww,i);
            coll = i;
            if(slash == 'f'){
                M.movement = 4;
            }
            else if(slash == 'b'){
                M.movement = 3;
            }
            break;
        }
        else {
            M.movement=0;
            M.board[roww][i] = '-';
            PrintBoard2();

            sleep(1);
            system("clear");
            M.board[roww][i] = '.';
        }
    }
    
    return false;
}

bool moveRight(char direction){
    int i=0;
    bool flag = false;
    
    for (i = coll + 1; i < M.col; i++)
    {
        if (roww == M.Ec.row && i == M.Ec.col) {
            M.board[roww][i] = 'X';
         
            flag = true;
            return true;
            break;
        }
        else if(checkMirror2(roww,i) != 'n'){
            char slash = checkMirror2(roww,i);
            coll = i;
            if(slash == 'f'){
                M.movement = 3;
            }
            else if(slash == 'b'){
                M.movement = 4;
            }
            break;
        }
        else {
            M.movement = 0;
            M.board[roww][i] = '-';
            PrintBoard2();
           
            sleep(1);
            system("clear");
            M.board[roww][i] = '.';
        }
    }
    
    return false;

}

void printList(struct Node *node)
{
    printf("Printing the LOG \n\n\n");
  while (node != NULL)
  {
      int i = 0, j = 0;
      for (i = 0; i <= node->m.col + 1; i++)
          printf("*");
      printf("\n");
      for (i = 0; i < node->m.row; i++)
      {
          printf("*");
          for (j = 0; j < node->m.col; j++)
          {
              if (j == 0)
              {
                  if (node->m.board[i][j] == '.')
                      printf(" ");
                  else
                      printf("%c", node->m.board[i][j]);
              }
              else {
                  if (node->m.board[i][j] == '.')
                      printf(" ");
                  else
                      printf("%c", node->m.board[i][j]);
              }
          }
          printf("*");
          printf("\n");
      }
      for (i = 0; i <= node->m.col + 1; i++)
          printf("*");
      printf("\n");

     node = node->next;
  }
}
 

void PlayGame() {
    
    struct Node* head = NULL;
    int i = 0;
    bool flag = false;
    while (flag == false) {
        char choice = 'a';
       
        system("clear");
        PrintBoard();
       
        push(&head);

        system("stty raw");
        choice = getchar();
        system("stty cooked");
        if (choice == 'f')
        {
            roww = M.Pc.row;
            coll = M.Pc.col;
            char direction = M.Pc.direction;
            
            system("clear");
            
            
            if (direction == 's')
            {
               flag = moveDown(direction);
                while(M.movement != 0){
                    if(M.movement  == 1){
                        flag =moveLeft(direction);
                    }
                    else if(M.movement == 2){
                        flag = moveRight(direction);
                    }
                    else if(M.movement == 3){
                        flag =moveUp(direction);
                    }
                    else if(M.movement == 4){
                        flag = moveDown(direction);
                    }
                    
                }
            }
 

else if (direction == 'w')
            {
                flag = moveUp(direction);
                while(M.movement != 0){
                    if(M.movement == 1){
                        flag =moveLeft(direction);
                    }
                    else if(M.movement == 2){
                        flag =moveRight(direction);
                    }
                    else if(M.movement == 3){
                        flag =moveUp(direction);
                    }
                    else if(M.movement == 4){
                        flag = moveDown(direction);
                    }
                    
                }
            }
            else if (direction == 'd')
            {
                flag = moveRight(direction);
                while(M.movement != 0){
                    if(M.movement == 1){
                        flag =  moveLeft(direction);
                    }
                    else if(M.movement == 2){
                        flag = moveRight(direction);
                    }
                    else if(M.movement == 3){
                        flag = moveUp(direction);
                    }
                    else if(M.movement == 4){
                        flag = moveDown(direction);
                    }
                    
                }
            }
            else if (direction == 'a')
            {
                flag = moveLeft(direction);
                while(M.movement != 0){
                    if(M.movement == 1){
                        flag =  moveLeft(direction);
                    }
                    else if(M.movement == 2){
                        flag = moveRight(direction);
                    }
                    else if(M.movement == 3){
                        flag =moveUp(direction);
                    }
                    else if(M.movement == 4){
                        flag = moveDown(direction);
                    }
                    
                }
            }
        }
        else if (choice == 'w')
        {
            
            if (M.Pc.row != 0)
            {
                
                if(checkMirror(M.Pc.row-1,M.Pc.col) == true){
                    M.Pc.row--;
                    
                    
                    if (M.Pc.col == M.Ec.col && M.Pc.row == M.Ec.row)
                    {
                        M.Pc.row++;
                    }
                    else {
                        M.board[M.Pc.row + 1][M.Pc.col] = '.';
                        M.Pc.direction = choice;
                    }
                }
            }
            M.Pc.direction = choice;
            M.board[M.Pc.row][M.Pc.col] = '^';
          //  push(&head,M);

        }
        else if (choice == 'a')
        {
            if (M.Pc.col != 0)
            {
                if(checkMirror(M.Pc.row,M.Pc.col-1) == true){
                    
                    M.Pc.col--;
                    if (M.Pc.col == M.Ec.col && M.Pc.row == M.Ec.row)
                    {
                        M.Pc.col++;
                    }
                    else {
                        M.board[M.Pc.row][M.Pc.col + 1] = '.';
                        M.Pc.direction = choice;
                    }
                }
            }
            M.Pc.direction = choice;
            M.board[M.Pc.row][M.Pc.col] = '<';
         //   push(&head,M);

        }
        else if (choice == 's')
        {
            if (M.Pc.row != M.row - 1)
            {
                if(checkMirror(M.Pc.row+1,M.Pc.col) == true){
                    
                    M.Pc.row++;
                    if (M.Pc.col == M.Ec.col && M.Pc.row == M.Ec.row)
                    {
                        M.Pc.row--;
                    }
                    else {
                        M.board[M.Pc.row - 1][M.Pc.col] = '.';
                        M.Pc.direction = choice;
                    }
                }
            }
            M.Pc.direction = choice;
            M.board[M.Pc.row][M.Pc.col] = 'V';
          //  push(&head,M);

        }
        else if (choice == 'd')
        {
            if (M.Pc.col != M.col - 1)
            {
                if(checkMirror(M.Pc.row,M.Pc.col+1) == true){
                    
                    M.Pc.col++;
                    if (M.Pc.col == M.Ec.col && M.Pc.row == M.Ec.row)
                    {
                        M.Pc.col--;
                    }
                    else {
                        M.board[M.Pc.row][M.Pc.col - 1] = '.';
                        M.Pc.direction = choice;
                    }
                }
            }
            M.board[M.Pc.row][M.Pc.col] = '>';
             
            M.Pc.direction = choice;
        //    push(&head,M);

        }
        printList(head);
        int a=0;
    }
   // push(&head,M);
    PrintBoard();
    printList(head);
}
