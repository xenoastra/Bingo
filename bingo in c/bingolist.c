#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


typedef struct {
  
  int I;

}priv_list;

void set(list **N, int G,int O){
  priv_list *new;
  new=(priv_list *)malloc(sizeof(priv_list));
  (*new).B=N;
  (*new).I=G;
  (*O)=(list)new;

}
void print(list *O) {
  printf("%d+%di\n", (*(priv_list *)a).B, (*(priv_list *)a).I); //might need to change list to complex
}
