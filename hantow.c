#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

/*  Initialize the pegs */
int peg1[9];
int peg2[9] = {0,0,0,0,0,0,0,0,0};
int peg3[9] = {0,0,0,0,0,0,0,0,0}; 


/* Functions to display the towers of Hanoi */
//display a line of the towers//
void display_peg_line(int num_disk) {
    int j;
  for ( j = 0; j < (10-num_disk); j++) {
    printf(" ");
  }
  for ( j = 0; j < num_disk; j++) {
    printf("+");
  }
  printf("|");
  for ( j = 0; j < num_disk; j++) {
    printf("+");
  }
  for ( j = 0; j < (10-num_disk); j++) {
    printf(" ");
  }
  printf("  ");
}

//display all 10 lines (height 9 + base)//
void display_pegs(int peg1[9], int peg2[9], int peg3[9]) {
    int i;
  for ( i = 8; i >= 0; i--) {
    display_peg_line(peg1[i]);
    display_peg_line(peg2[i]);
    display_peg_line(peg3[i]);
    printf("\n");
  }
  printf("XXXXXXXXXXXXXXXXXXXXX  XXXXXXXXXXXXXXXXXXXXX  XXXXXXXXXXXXXXXXXXXXX");
  printf("\n");
  printf("\b");
}

/* Move a disc from one peg to another (top disc) */
void move(int pegA[9], int pegB[9]) {
  int a = 8;
  int b = 8;
  int disk;
  while (pegA[a] == 0) {
    a--;                
  }
  disk = pegA[a];
  pegA[a]=0;
  if (pegB[0] == 0) {
      pegB[0] = disk;
    }
  else {
    while (pegB[b] == 0) {
        b--;
    }
    pegB[b+1] = disk;
  }
  display_pegs(peg1,peg2,peg3);
  sleep(1);
}

/* Recursive hanoi algorithm*/
void hanoi(int num_disks, int pegOrigin[9], int pegDestination[9], int pegHelper[9]) {
//if there is only one disk, simply move it to the middle (destination) //
  if(num_disks == 1) {
      move(pegOrigin, pegDestination);
  }

//for multiple disks, use recursion to move smaller towers of hanoi. Ex. for a tower of 3,
//move a tower of 2 to the empty tower, then the base to the destination tower, then move
//the tower of 2 on the base, creating the fully built tower on the middle peg 
  else {
      hanoi(num_disks-1, pegOrigin, pegHelper, pegDestination);
      move(pegOrigin, pegDestination);
      hanoi(num_disks-1,pegHelper,pegDestination,pegOrigin);
  }
}

/* Set the left tower with the appriate amount of disks from the command line arg */
void setInitPeg(int peg[9], int num_disks) {
  int i;
  int temp = num_disks;
  for(i = 0 ; i < num_disks; i++) {
      peg[i] = temp;
      temp--;
  }
  for(i=num_disks; i<9; i++) {
      peg[i] = 0;
  }
}


/* main function - check for appriate cmd line args, then move tower */
int main(int argc, char* argv[]) {
   int i;
     if (argc != 2) {
        printf("Must be 2 args:  incorrect number of command line arguments\n");
        printf("all command line arguments:\n");
        for( i = 0; i < argc; i++)
          printf("%s\n",argv[i]);
        return 0;
      }
      if (strlen(argv[1]) != 1) {
          printf("Must be a number 1-9:  invalid command line argument: \n");
            printf("%s\n",argv[1]);
          return 0;
      }
     
    if (!(isdigit(argv[1][0])) || atoi(argv[1]) == 0 ) {
      printf("MUST BE A NUMBER 1-9:  Invalid number of disks");
      return 0;
     }
  int num_disks = argv[1][0] - '0';
  setInitPeg(peg1, num_disks);
  display_pegs(peg1, peg2, peg3);
  hanoi(num_disks, peg1, peg2, peg3);
  printf("\ndone\n");
}