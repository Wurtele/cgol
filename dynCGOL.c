#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define ROWS 20
#define COLS 40

int main( int argc, char *argv[]) {
  FILE *f;

  int ticks = 50;
  int loopTicks;
  int tickCount = 0;
  int i,j;
  int y,x;
  int alive;
  int diff;

  int rows;
  int cols;

  int lineCount = 0;

  int error = 0;
  char inputString[50];
  char string[50];

  /*Check for proper number of arguments*/
  if (argc != 5) {
    printf("Usage: ./cgol filename ticks rows columns\n");
    return(1);
  }
  ticks = atoi(argv[2]);
  rows = atoi(argv[3]);
  cols = atoi(argv[4]);

  /*Declare grid*/
  int grid[rows][cols];
  int futureGrid[rows][cols];


  /*Open file and check for error*/
  if( (f = fopen(argv[1], "r") ) == NULL ) {
    printf("Null File\n");
    return(1);
  }
  lineCount=0;
  while ( fgets(string, 100, f) != NULL ) {
    if (strlen(string)!=2*cols) {
      printf("Error - File not %dx%d\n",rows,cols);
      return(1);
    }
    lineCount++;
  }
  size_t pos = ftell(f);
  fseek(f, 0, SEEK_END);
  size_t length = ftell(f);
  fseek(f, pos, SEEK_SET);
  if (length!=2*cols*rows && lineCount!=rows) {
    printf("Error - File not %dx%d\n",rows,cols);
    return(1);
  }
  fclose(f);


  if( (f = fopen(argv[1], "r") ) == NULL ) {
    printf("Null File\n");
    return(1);
  }
  /*Read file into grid*/
  for (j=0;j<rows; j++) {
    for (i=0; i<cols; i++) {
      if (fscanf(f, "%d", &grid[j][i]) != 1) {
        printf("Null Character\n");
        return(1);
      }
    }
  }
  fclose(f);

  loopTicks=ticks;

  tickCount=0;
  while (tickCount<loopTicks+1) {

    /*Display grid*/
    system("sleep 0.25");
    system("clear");

    printf(" ");
    for (i=0;i<cols;i++) {
      printf("-");
    }
    printf(" \n");
    for (i=0; i<rows; i++) {
      printf("|");
      for (j=0; j<cols; j++) {
        if (grid[i][j] == 1 ) {
          printf("X");
        } else if (grid[i][j] == 0) {
          printf(" ");
        }
      }
      printf("|\n");
    }
    printf(" ");
    for (i=0;i<cols;i++) {
      printf("-");
    }
    printf("%d\n",tickCount);

    /*START QUESTION*/
    if ( tickCount==0) {
      error=1;
      while (error==1) {
        printf("Start? (Y or N): ");
        fgets(inputString, 100, stdin);
        sscanf(inputString,"%s",string);

        if (strcmp(string,"N")==0 || strcmp(string,"n")==0) {
          return(1);
        } else if (strcmp(string,"Y")==0 || strcmp(string,"y")==0) {
          error=0;
        }
        if (error==1) {
          printf("Only the single characters Y or N are acceptable.\n");
        }
      }
    }

    /*Evaluate grid and put into futureGrid*/
    for (y=0;y<rows;y++) {
      for (x=0;x<cols;x++) {
        alive=0;

        for (i=-1;i<=1;i++) {
          for (j=-1;j<=1;j++) {
            if ( (y+i)>-1 && (y+i)<rows && (x+j)>-1 && (x+j)<cols ) {
              if ( !(j==0 && i==0) ) {
                if (grid[y+i][x+j] == 1) {
                  alive = alive + 1;

                }
              }
            }
          }
        }

        if (grid[y][x]==1) {
          if (alive < 2) {
            futureGrid[y][x]=0;
          } else if (alive==2 || alive==3) {
            futureGrid[y][x]=1;
          } else if (alive > 3) {
            futureGrid[y][x]=0;
          }
        } else if (grid[y][x]==0) {
          if (alive == 3) {
            futureGrid[y][x]=1;
          } else if (alive!=3) {
            futureGrid[y][x]=0;
          }
        }
      }
    }

    /*Transfer from futureGrid to grid and check for differences*/
    diff=0;
    for (y=0;y<rows;y++) {
      for (x=0;x<cols;x++) {
        if (grid[y][x]!=futureGrid[y][x] && diff!=1) {
          diff=1;
        }
        grid[y][x] = futureGrid[y][x];
      }
    }
    if (diff==0) {
      return(1);
    }

    tickCount++;

    /*CONTINUE QUESTION*/
    if ( tickCount>=loopTicks+1 ) {
      error=1;
      while (error==1) {
        printf("Contine? (Y or N): ");
        fgets(inputString, 100, stdin);
        sscanf(inputString,"%s",string);

        if (strcmp(string,"N")==0 || strcmp(string,"n")==0) {
          return(1);
        } else if (strcmp(string,"Y")==0 || strcmp(string,"y")==0) {
          loopTicks=loopTicks+ticks;
          error=0;
        }
        if (error==1) {
          printf("Only the single characters Y or N are acceptable.\n");
        }
      }
    }

  }

  return(0);
}
