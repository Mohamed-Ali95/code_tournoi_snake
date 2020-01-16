//YAZID Mohamed-Ali EISE3

#include <stdio.h>
#include <stdlib.h>
#include "snakeAPI.h"
#include "ret_type.h"
#include "clientAPI.h"
#include "anticipMov.h"

void main(int argc,char* argv[]){

  char* serverName="li2051-215.members.linode.com";
	int port= strtol(argv[2], NULL, 10);
	char* name="anaconda";
	char* gameType ="RANDOM_PLAYER difficulty=2 seed=123 timeout=100 start=0";
	char gameName[200];
	int sizeX;
	int sizeY;
	int nbWalls;

	t_move move;

  connectToServer(argv[1],port,name);
  waitForSnakeGame(argv[3],gameName,&sizeX,&sizeY,&nbWalls);


  int* walls;
  walls=(int*)malloc(4*nbWalls*sizeof(int));


  int first;//désigne joueur qui commence
  first=getSnakeArena(walls);
  printArena();
  t_return_code ret;
  int direction; //égal à 0,1,2 ou 3 (NORTH,EAST,WEST,SOUTH)
  int aquiletour;//booléen qui détermine à qui c'est le tour de jouer

  if(first==0){
	  direction=(int)rand()%4;
	 	ret=sendMove((t_move)direction);
	 	printArena();
		aquiletour=1;
	}
	else{
		ret=getMove(&move);
		printArena();
		aquiletour=0;
  }

  int* directPossibles; //directions possibles
  directPossibles=(int*)malloc(4*sizeof(int));

  //enchaînement des tours des joueurs
	while (ret!=WINNING_MOVE && ret!=LOOSING_MOVE){
		//notre tour
		if (!aquiletour){

      directPossibles=anticipMove();
      //cas où aucune direction possible
      if (*directPossibles==NULL){
        direction=(int)rand()%4;
      }
      else{
        int val_int;
        val_int=directPossibles[rand()%4]; /*variable stockant une direction prise
        au hasard dans les directions possibles*/

        while (val_int==direction){
          val_int=directPossibles[rand()%4];
        }
        direction=val_int;
      }
      ret=sendMove((t_move)direction);
			printArena();
			aquiletour=!aquiletour; //on change la valeur du booléen
    }
    //tour de l'adversaire
    else if (aquiletour){
       ret=getMove(&move);
       printArena();
       aquiletour=!aquiletour;//on change la valeur du booléen
    }

  }

	closeConnection();

}
