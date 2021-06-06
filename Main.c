#include <stdio.h>

#include <stdlib.h>
#include <string.h>

#include "Map.h"

int main(int argc, char** argv) {

	if (argc == 3)
	{
        char fn[50];
        char log[50];
        struct mirror m[100];
        int count=0;
        
		strcpy (fn, "/Users/m1/Desktop/c++/test/test/map.txt");
        strcpy(log,argv[2]);
        
        FILE *fptr;
        fptr = fopen(fn,"r");
        
        int row=0,col=0,prow=0,pcol=0;
        char Pdir;
        int erow=0,ecol=0;
        char Edir;
        
        fscanf(fptr,"%d",&row);
        
        fscanf(fptr,"%d",&col);
        fscanf(fptr,"%d",&prow);
        fscanf(fptr,"%d",&pcol);
        fscanf(fptr,"%c",&Pdir);
        fscanf(fptr,"%c",&Pdir);
        
        fscanf(fptr,"%d",&erow);
        fscanf(fptr,"%d",&ecol);
        fscanf(fptr,"%c",&Edir);
        fscanf(fptr,"%c",&Edir);
        
        int one,two;
        char three;
        while(1) {
            
            fscanf(fptr,"%d",&one);
            fscanf(fptr,"%d",&two);
            
            fscanf(fptr,"%c",&three);
            fscanf(fptr,"%c",&three);
            
            if( feof(fptr) ) {
                 break ;
              }
            
            m[count].row = one;
            m[count].col = two;
            m[count].side = three;
            count++;
            
        
           
        }
        
        fclose(fptr);
        
       

		if (row < 5 || col < 25) {
			InitializeBoard(row, col, prow, pcol, Pdir, erow, ecol, Edir,m,count);
			PlayGame();
		}
         
	}
	

	return 0;
}
