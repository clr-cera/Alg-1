#include <stdio.h>
#include <string.h>
#include "word.h"
#include "skipList.h"

void Insert();
void Alter();
void Remove();
void Search();
void Print();


int main(void){
  char command[11];
  while(1){
    scanf(" %s", command);
    if     (strcmp(command, "insercao") == 0)
      Insert();

    else if(strcmp(command, "alteracao") == 0)
      Alter();

    else if(strcmp(command, "remocao") == 0)
      Remove();

    else if(strcmp(command, "busca") == 0)
      Search();

    else if(strcmp(command, "impressao") == 0)
      Print();
  }
}
