#include <stdio.h>  // Standard c libraries
#include <stdlib.h>  // Standard c libraries
#include <string.h>  // Standard c libraries
#define FALSE 0
#define TRUE  1
int debugMode = FALSE;
typedef struct mazeStruct  // struct
{
 char **arr;
 int xsize, ysize;
 int xstart, ystart;
 int xend, yend;
 int **visited;
} maze;
typedef struct stackList{
  int xplace, yplace;
  struct stackList *next;
}stack;
void push(stack **hd, int xpos, int ypos){  // Function for push the elements
  stack *newTop = (stack*) malloc (sizeof (stack));
  newTop-> xplace = xpos;
  newTop-> yplace = ypos;
  newTop-> next = *hd;
  *hd = newTop;
}
void pop(stack **hd){  // Function for pop the elements
  stack *temphd = *hd;
  *hd = (*hd)->next;
  free(temphd);  // To free temphd
}
int isEmpty (stack *hd)
{
 if (hd == NULL)
   return TRUE;  // To return true
 else
   return FALSE;  // To return false
}
stack* top (stack *hd)
{
 return hd;  // To return hd 
}
void printStack(stack *hd) {
  if(hd == NULL) {
    return;
  }
  printStack(hd->next);
  printf("(%d,%d)", hd->xplace, hd->yplace);
  return;
}
int main (int argc, char **argv)  // Main function
{
  maze m1;
  stack* head = NULL;
  int xpos, ypos;
  int i,j;
  FILE *src;
  char ltr;
  setbuf(stdout, NULL);
  for (int m = 0; m<argc; m++) {
    if(strcmp(argv[m], "-d") == 0) {
      debugMode = TRUE;
    }
  }
  if(debugMode == TRUE) {
    if(argc != 3) {
      printf("Usage: %s <input file name>\n", argv[0]);
      exit(-1);
    }
  } else {
    if(argc != 2) {
      printf("Usage: %s <input file name>\n", argv[0]);  // To print the given statement 
      exit(-1);
    }
  }
  if ((src = fopen( argv[1], "r" )) == NULL )
  {
    printf ( "Can't open input file: %s", argv[1] );  // To print the given statement
    exit(-1);
  }
  fscanf (src, "%d %d", &m1.xsize, &m1.ysize);
  fscanf (src, "%d %d", &m1.xstart, &m1.ystart);
  fscanf (src, "%d %d", &m1.xend, &m1.yend);
  if((m1.xstart == 0 && m1.ystart == 0) || (m1.xend == 0 && m1.yend == 0)){
    printf("Invalid data file.");  // To print the given statement
    exit(0);
  }
  if(m1.xsize <= 0 || m1.ysize <= 0){
    fprintf(stderr, "Maze sizes must be greater than 0.\n");  // To print the given statement
    exit(0);
  }
  printf ("size: %d, %d\n", m1.xsize, m1.ysize);
  if(m1.xstart > m1.xsize || m1.ystart <= 0 || m1.ystart > m1.ysize || m1.ystart <= 0 ){
    fprintf(stderr, "Start/End position outside of maze range.\n");  // To print the given statement
    exit(0);
  }
  printf ("start: %d, %d\n", m1.xstart, m1.ystart);
  if(m1.xend <= 0 || m1.xend > m1.xsize || m1.yend <= 0 || m1.yend > m1.ysize){
    fprintf(stderr, "Start/End position outside of maze range.\n");  // To print the given statement
    exit(-1);
  }
  printf ("end: %d, %d\n", m1.xend, m1.yend);
  m1.arr = (char**) malloc (sizeof(char*) * (m1.xsize+2));
  m1.visited = (int**) malloc (sizeof(int*) * (m1.xsize+2));
  for(i = 0; i < (m1.xsize+2); i++) {
    m1.arr[i] = (char*) malloc (sizeof(char) * (m1.ysize+2));
    m1.visited[i] = (int*) malloc (sizeof(int) * (m1.ysize+2));
  }
  for (i = 0; i < m1.xsize+2; i++)
     for (j = 0; j < m1.ysize+2; j++)
       m1.arr[i][j] = '.';
  for (i = 1; i < m1.xsize+1; i++)
     for (j = 0; j < m1.ysize+1; j++)
       m1.visited[i][j] = FALSE;
  for (i=0; i < m1.xsize+2; i++)
    {
     m1.arr[i][0] = '*';
     m1.arr[i][m1.ysize+1] = '*';
     m1.visited[i][0] = TRUE;
     m1.visited[i][m1.ysize+1] = TRUE;
    }
  for (i=0; i < m1.ysize+2; i++) {
     m1.arr[0][i] = '*';
     m1.visited[0][i] = TRUE;
     m1.arr[m1.xsize+1][i] = '*';
     m1.visited[m1.xsize+1][i] = TRUE;
  }
  m1.arr[m1.xstart][m1.ystart] = 's';
  m1.arr[m1.xend][m1.yend] = 'e';
  while(fscanf (src, "%d %d %c", &xpos, &ypos, &ltr) != EOF){
    if (m1.xsize < xpos || m1.ysize < ypos){
      fprintf(stderr, "Invalid coordinates: outside of maze range.\n");  // To print the given statement
      continue;
    }
    if(ltr == 'b')  {
      if(xpos == m1.xstart && ypos == m1.ystart){
        printf("Invalid coordinates: attempting to block start/end position.\n");  // To print the given statement
        continue;
      }
      if(xpos == m1.xend && ypos == m1.yend){
        printf("Invalid coordinates: attempting to block start/end position.\n");  // To print the given statement
        continue;
      }
      m1.arr[xpos][ypos] = '*';
      m1.visited[xpos][ypos] = TRUE;
    } else if (ltr == 'c') {
      if(xpos == m1.xstart && ypos == m1.ystart){
        printf("Invalid coordinates: attempting to block start/end position.\n");  // To print the given statement
        continue;
      }
      if(xpos == m1.xend && ypos == m1.yend){
        printf("Invalid coordinates: attempting to block start/end position.\n");  // To print the given statement
        continue;
      }
      m1.arr[xpos][ypos] = 'C';
    } else {
      fprintf(stderr, "Invalid type: type is not recognized.\n");
      continue;
    }
  }
  fclose(src);
  for (i = 0; i < m1.xsize+2; i++) {
     for (j = 0; j < m1.ysize+2; j++)
       printf ("%c", m1.arr[i][j]);  // To print the given statement
     printf("\n");  // To print the newline given statement
    }
  
  push(&head, m1.xstart, m1.ystart);
  if(debugMode == TRUE) {
    printf("(%d,%d) pushed into the stack.\n", m1.xstart, m1.ystart);  // To print the given statement
  }
  m1.visited[m1.xstart][m1.ystart] = TRUE;
  int curXPos = m1.xstart;
  int curYPos = m1.ystart;
  int coins = 0;
  int tracker = 1;
  while(isEmpty(head) == FALSE) {
    tracker++;
    if(curXPos == m1.xend && curYPos == m1.yend) {
      break;
    } else if (m1.visited[curXPos+1][curYPos] == FALSE) {
      curXPos++;
      if(m1.arr[curXPos][curYPos] == 'C' ){
        coins++;
      }
      push(&head, curXPos, curYPos);
      if(debugMode == TRUE) {
        printf("(%d,%d) pushed into the stack.\n", curXPos, curYPos);
      }
      m1.visited[curXPos][curYPos] = TRUE;
    } else if (m1.visited[curXPos][curYPos + 1] == FALSE) {
      curYPos++;
      if(m1.arr[curXPos][curYPos] == 'C' ){
        coins++;
      }
      push(&head, curXPos, curYPos);
      if(debugMode == TRUE) {
        printf("(%d,%d) pushed into the stack.\n", curXPos, curYPos);
      }
      m1.visited[curXPos][curYPos] = TRUE;
    } else if (m1.visited[curXPos - 1][curYPos] == FALSE) {
      curXPos--;
      if(m1.arr[curXPos][curYPos] == 'C' ){
        coins++;  // Increment coins
      }
      push(&head, curXPos, curYPos);
      if(debugMode == TRUE) {
        printf("(%d,%d) pushed into the stack.\n", curXPos, curYPos);
      }
      m1.visited[curXPos][curYPos] = TRUE;
    } else if (m1.visited[curXPos][curYPos - 1] == FALSE) {
      curYPos--;
      if(m1.arr[curXPos][curYPos] == 'C' ){
        coins++;
      }
      push(&head, curXPos, curYPos);
      if(debugMode == TRUE) {
        printf("(%d,%d) pushed into the stack.\n", curXPos, curYPos);
      }
      m1.visited[curXPos][curYPos] = TRUE;
    } else {
      pop(&head);
      if(debugMode == TRUE) {
        printf("(%d,%d) popped off the stack.\n", curXPos, curYPos);
      }
      if(isEmpty(head)) {
        continue;
      }
      curYPos = head->yplace;
      curXPos = head->xplace;
    }
  }
  if(isEmpty(head) == FALSE) {
    printf("The maze has a solution.\n");  // To print the given statement
    printf("The amount of coins collected: %d\n", coins);  // To print the given statement
    printf("The path from start to end:\n");  // To print the given statement
    printStack(head);
    printf("\n");
    while (head != NULL)  {
      if(debugMode == TRUE) {
        printf("(%d,%d) popped off the stack.\n", head->xplace, head->yplace);
      }
      pop(&head);
      if(head == NULL) {
        break;
      }
    }
  } else {
    printf("This maze has no solution.\n");
  }
  free(head);
  for(int i = 0; i<m1.xsize+2; i++) {
    free(m1.arr[i]);
    free(m1.visited[i]);
  }
  free(m1.arr);
  free(m1.visited);
  return 1;  // To return 
}
// end of main. 