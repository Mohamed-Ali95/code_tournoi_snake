//YAZID Mohamed-Ali EISE3

#include <stdio.h>
#include <stdlib.h>
#include "snakeAPI.h"
#include "ret_type.h"
#include "clientAPI.h"
#include "anticipMov.h"

/*dans ce code, on retourne les directions dans lesquelles il est possible d'aller
sous la forme d'un tableau(pointeur).Pour cela, on simule le déplacement du snake
 pour savoir si la direction souhaitée n'est pas un obstacle.
L'anticipation se fait à une case près de la position du snake
*/
int* anticipMove(){

  int* directPossibles;
  directPossibles=(int*)malloc(4*sizeof(int));
  int i;
  for (i=0;i<4;i++){
    int boole0=1; //vérfie si la direction 0 n'est pas déjà dans directPossibles
    int j;
    for (j=0;j<4;j++){
      if (directPossibles[j]==0){
        boole0=!boole0;
        break;
      }
    }
    int boole1=1; //vérfie si la direction 1 n'est pas déjà dans directPossibles
    int k;
    for (k=0;k<4;k++){
      if (directPossibles[k]==1){
        boole1=!boole1;
        break;
      }
    }


    int boole2=1; //vérfie si la direction 2 n'est pas déjà dans directPossibles
    int l;
    for (l=0;l<4;l++){
      if (directPossibles[l]==2){
        boole2=!boole2;
        break;
      }
    }


    if (getMove(NORTH)!=LOOSING_MOVE){

          directPossibles[i]=0;
    }

    else if (getMove(EAST)!=LOOSING_MOVE){

          directPossibles[i]=1;

    }

    else if (getMove(SOUTH)!=LOOSING_MOVE && boole2){

          directPossibles[i]=2;

    }

    else if (getMove(WEST)!=LOOSING_MOVE){
      directPossibles[i]=3;

      break;
    }
  }

  //test
  int l;
  for (l=0;l<4;l++){
    printf("%d\n",directPossibles[l]);
  }
  return directPossibles;
}
