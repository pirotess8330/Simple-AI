/* 
   Wumpus World
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <strings.h>
#include "Environment.h"
#include "Directions.h"

#define BUFSZE 1024

struct Grid* SetupMap(char* filename){
	int gridsize = sizeof(struct Grid);
	struct Grid* G = (struct Grid*)malloc(gridsize);
	char* buf;
	struct Location* nextToCurrentLocation;
	if((buf = (char*)malloc(BUFSZE))== NULL){
		printf("Could not allocate space\n");
		exit(-1);
	}
	int fd;
	if((fd = open(filename, O_RDONLY)) == -1){
		printf("Error Opening File\n");
		exit(-1);
	}
	int locationCount = 0;
	struct Location*** arr = malloc(BUFSZE);
	G->twodarr = arr;

	int n;
	char currentChar;
	if((n = read(fd, buf, BUFSZE))<1){
		printf("Error Reading\n");
		exit(-1);
	}
	int xNdx = 0, yNdx;
	while((currentChar = buf[locationCount]) != 'Q'){
		yNdx = 0;
		G->twodarr[xNdx] = malloc(BUFSZE);
		while((currentChar = buf[locationCount]) != '\n'){
			/*if(!(locationCount < BUFSZE)){
				read(fd, &buf, sizeof(BUFSZE));
				locationCount = 0;
			}*/

			G->twodarr[xNdx][yNdx] = malloc(sizeof(struct Location*));

			switch(buf[locationCount]){
				case 'X':
					G->twodarr[xNdx][yNdx] = createLocation(xNdx,yNdx,1,0,0,0,0,0,0,0);
					break;
				case '0':
					G->twodarr[xNdx][yNdx] = createLocation(xNdx,yNdx,0,0,0,0,0,0,0,0);
					break;
				case 'P':
					G->twodarr[xNdx][yNdx] = createLocation(xNdx,yNdx,0,0,0,0,0,0,0,1);
					/*setBreeze(G, xNdx+1, yNdx);*/
					if(getLocationSpecified(G, xNdx, yNdx, xNdx-1, yNdx) != NULL){
						setBreeze(G, xNdx-1, yNdx);
					}
					/*setBreeze(G, xNdx, yNdx+1);*/
					if(getLocationSpecified(G, xNdx, yNdx, xNdx, yNdx-1) != NULL){
						setBreeze(G, xNdx, yNdx-1);
					}
					break;
				case 'W':
					G->twodarr[xNdx][yNdx] = createLocation(yNdx,xNdx,0,0,0,0,1,0,0,0);
					/*setStench(G, xNdx+1, yNdx);*/
					if(getLocationSpecified(G, xNdx, yNdx, xNdx-1, yNdx) != NULL){
						setStench(G, xNdx-1, yNdx);
					}
					/*setStench(G, xNdx, yNdx+1);*/
					if(getLocationSpecified(G, xNdx, yNdx, xNdx, yNdx-1) != NULL){
						setStench(G, xNdx, yNdx-1);
					}
					break;
				case 'M':
					G->twodarr[xNdx][yNdx] = createLocation(yNdx,xNdx,0,0,0,0,0,1,0,0);
					/*setStench(G, x+1, y){
					//setStench(G, x-1, y){
					//setStench(G, x, y+1){
					//setStench(G, x, y-1){*/
					break;
				case 'E':
					G->twodarr[xNdx][yNdx] = createLocation(yNdx,xNdx,0,0,0,0,0,0,1,0);
					break;
				case 'G':
					G->twodarr[xNdx][yNdx] = createLocation(yNdx,xNdx,0,0,0,1,0,0,0,0);
					break;
			}

			if((nextToCurrentLocation = getLocationSpecified(G, xNdx, yNdx, xNdx-1, yNdx)) != NULL){
				if(nextToCurrentLocation->containsPit){
					G->twodarr[xNdx][yNdx]->containsBreeze = 1;
				}
				if(nextToCurrentLocation->containsWumpus){
					G->twodarr[xNdx][yNdx]->containsStench = 1;
				}
			}
			if((nextToCurrentLocation = getLocationSpecified(G, xNdx, yNdx, xNdx, yNdx-1)) != NULL){
				if(nextToCurrentLocation->containsPit){
					G->twodarr[xNdx][yNdx]->containsBreeze = 1;
				}
				if(nextToCurrentLocation->containsWumpus){
					G->twodarr[xNdx][yNdx]->containsStench = 1;
				}
			}

			locationCount++;
			yNdx++;
		}
		locationCount++;
		xNdx++;
	}
	G->xdim = xNdx;
	G->ydim = yNdx;
	return G;
}

struct Environment* createEnvironment(char* filename){
	struct Environment* environ = (struct Environment*)malloc(sizeof(struct Environment));
	environ->Map = SetupMap(filename);
	environ->agentLocations = malloc(sizeof(int));
	char* agent1 = malloc(13);
	char* agent2 = malloc(13);
	char* nullAgent = malloc(1);
	snprintf(agent1, (size_t)13 , "%s%s%s%s%s%s", "agent1", " ", "10", " ", "5", "\0");
	snprintf(agent2, (size_t)13 , "%s%s%s%s%s%s", "third", " ", "17", " ", "15", "\0");
	environ->agentLocations[0] = agent1;
	environ->agentLocations[1] = agent2;
	environ->agentLocations[2] = NULL;
	environ->goalFound = 0;
	return environ;
}

struct Location* createLocation(int x, int y, int Wl, int St, int Br, int G, int W, int M, int E, int P){
	struct Location* newLocation = (struct Location *)malloc(sizeof(struct Location));
	newLocation->xcoordinate = x;
	newLocation->ycoordinate = y;
	newLocation->visited = 0;
	newLocation->containsWall = 0;
	newLocation->containsStench = 0;
	newLocation->containsBreeze = 0;
	newLocation->containsGold = 0;
	newLocation->containsWumpus= 0;
	newLocation->containsMinion = 0;
	newLocation->containsExit = 0;
	newLocation->containsPit = 0;
	newLocation->maybePit = 0;
	newLocation->maybeWumpus = 0;

	if(Wl){
		newLocation->containsWall = 1;
	}
	if(St){
		newLocation->containsStench = 1;
	}
	if(Br){
		newLocation->containsBreeze = 1;
	}
	if(G){
		newLocation->containsGold = 1;
	}
	if(W){
		newLocation->containsWumpus= 1;
	}
	if(M){
		newLocation->containsMinion = 1;
	}
	if(E){
		newLocation->containsExit = 1;
	}
	if(P){
		newLocation->containsPit = 1;
	}
	return newLocation;
}

struct Location* getLocationSpecified(struct Grid* Map, int actualX, int actualY, int xOfInterest, int yOfInterest){
	if((actualX-1) < 0 || (actualY-1) < 0){
		return NULL;
	}
	else{
		return Map->twodarr[xOfInterest][yOfInterest];
	}
}

struct Location* getLocation(struct Environment* environ, char* agentName){
	int namesNdx = -1;
	char* currentName;
	char* xS;
	char* yS;
	int x, y;
	while(environ->agentLocations[++namesNdx] != NULL){
		int sNdx = -1;
		currentName = malloc(strlen(environ->agentLocations[namesNdx]));
		while(environ->agentLocations[namesNdx][++sNdx] != ' '){
			currentName[sNdx] = environ->agentLocations[namesNdx][sNdx];
		}
		currentName[sNdx] = '\0';
		if(strcmp(currentName,agentName) == 0){
			int ndx = 0;
			xS = malloc(strlen(environ->agentLocations[namesNdx]));
			yS = malloc(strlen(environ->agentLocations[namesNdx]));
			while(environ->agentLocations[namesNdx][++sNdx] != ' '){
				xS[ndx++] = environ->agentLocations[namesNdx][sNdx];
			}
			xS[ndx] = '\0';
			ndx = 0;
			while(environ->agentLocations[namesNdx][++sNdx] != '\0'){
				yS[ndx++] = environ->agentLocations[namesNdx][sNdx];
			}
			yS[ndx] = '\0';
			x = atoi(xS);
			y = atoi(yS);
			return environ->Map->twodarr[x][y];
		}
	}
	return NULL;
}

void moveAgent(struct Environment* environ, char* agentName, int direction){
	int namesNdx = -1;
	char* newLocation;
	char* currentName;
	char* xS;
	char* yS;
	int x, y;
	while(environ->agentLocations[++namesNdx] != NULL){
		int sNdx = -1;
		while(environ->agentLocations[namesNdx][++sNdx] != ' '){
			currentName[sNdx] = environ->agentLocations[namesNdx][sNdx];
		}
		currentName[sNdx] = '\0';

		if(strcmp(currentName,agentName) == 0){
			int ndx = 0;
			xS = malloc(strlen(environ->agentLocations[namesNdx]));
			yS = malloc(strlen(environ->agentLocations[namesNdx]));
			while(environ->agentLocations[namesNdx][++sNdx] != ' '){
				xS[ndx++] = environ->agentLocations[namesNdx][sNdx];
			}
			xS[ndx] = '\0';
			ndx = 0;
			while(environ->agentLocations[namesNdx][++sNdx] != '\0'){
				yS[ndx++] = environ->agentLocations[namesNdx][sNdx];
			}
			yS[ndx] = '\0';
			x = atoi(xS);
			y = atoi(yS);
			if(direction == NORTH){
				printf("Moving %s north\n", currentName);
				int newIntLen;
				y--;
				if(y<10) newIntLen = 1;
				else if(y<100) newIntLen = 2;
				else newIntLen = 3;
				newLocation = malloc(strlen(currentName) + newIntLen + strlen(xS) + 3);
				snprintf(newLocation, strlen(currentName) + newIntLen + strlen(xS) + 3, "%s%s%s%s%d", currentName, " ", xS, " ", y);
				environ->agentLocations[namesNdx] = newLocation;
				return;
			}
			if(direction == SOUTH){
				printf("Moving %s south\n", currentName);
				int newIntLen;
				y++;
				if(y<10) newIntLen = 1;
				else if(y<100) newIntLen = 2;
				else newIntLen = 3;
				newLocation = malloc(strlen(currentName) + newIntLen + strlen(xS) + 3);
				snprintf(newLocation, strlen(currentName) + newIntLen + strlen(xS) + 3, "%s%s%s%s%d", currentName, " ", xS, " ", y);
				environ->agentLocations[namesNdx] = newLocation;
				return;
			}
			if(direction == EAST){
				printf("Moving %s east\n", currentName);
				int newIntLen;
				x++;
				if(x<10) newIntLen = 1;
				else if(x<100) newIntLen = 2;
				else newIntLen = 3;
				newLocation = malloc(strlen(currentName) + newIntLen + strlen(yS) + 3);
				snprintf(newLocation, strlen(currentName) + newIntLen + strlen(xS) + 3, "%s%s%d%s%s", currentName, " ", x, " ", yS);
				environ->agentLocations[namesNdx] = newLocation;
				return;
			}
			if(direction == WEST){
				printf("Moving %s west\n", currentName);
				int newIntLen;
				x--;
				if(x<10) newIntLen = 1;
				else if(x<100) newIntLen = 2;
				else newIntLen = 3;
				newLocation = malloc(strlen(currentName) + newIntLen + strlen(yS) + 3);
				snprintf(newLocation, strlen(currentName) + newIntLen + strlen(yS) + 3, "%s%s%d%s%s", currentName, " ", x, " ", yS);
				environ->agentLocations[namesNdx] = newLocation;
				return;
			}
		}
	}
}

int hasGoalBeenFound(struct Environment* environ){
	return environ->goalFound;
}

int isWall(struct Grid* Map, int x, int y){
	return Map->twodarr[x][y]->containsWall;
}

int isWumpus(struct Grid* Map, int x, int y){
	return Map->twodarr[x][y]->containsWumpus;
}

int isMinion(struct Grid* Map, int x, int y){
	return Map->twodarr[x][y]->containsMinion;
}

int isGold(struct Grid* Map, int x, int y){
	return Map->twodarr[x][y]->containsGold;
}

int isPit(struct Grid* Map, int x, int y){
	return Map->twodarr[x][y]->containsPit;
}

int isMaybePit(struct Grid* Map, int x, int y){
	return Map->twodarr[x][y]->maybePit;
}

int isMaybeWumpus(struct Grid* Map, int x, int y){
	return Map->twodarr[x][y]->maybeWumpus;
}

void setStench(struct Grid* Map, int x, int y){
	Map->twodarr[x][y]->containsStench = 1;
}

void setBreeze(struct Grid* Map, int x, int y){
	Map->twodarr[x][y]->containsBreeze = 1;
}

void setGold(struct Grid* Map, int x, int y){
	Map->twodarr[x][y]->containsGold = 1;
}

void setWumpus(struct Grid* Map, int x, int y){
	Map->twodarr[x][y]->containsWumpus= 1;
}

void setMinion(struct Grid* Map, int x, int y){
	Map->twodarr[x][y]->containsMinion = 1;
}

void setExit(struct Grid* Map, int x, int y){
	Map->twodarr[x][y]->containsExit = 1;
}

void setPit(struct Grid* Map, int x, int y){
	Map->twodarr[x][y]->containsPit = 1;
}

void setMaybeWumpus(struct Grid* Map, int x, int y){
	Map->twodarr[x][y]->maybeWumpus = 1;
}

void setMaybePit(struct Grid* Map, int x, int y){
	Map->twodarr[x][y]->maybePit = 1;
}

void setGoalFound(struct Environment* environ){
	environ->goalFound = 1;
}

/*void printMap(struct Environment* environ)
{
	struct Location* loc;
	struct Location** agents;
	char** currentName;
	char* name;
	int namesNdx = -1;
	while(environ->agentLocations[++namesNdx] != NULL)
	{
		int sNdx = -1;
		currentName[namesNdx] = malloc(sizeof(char*));
		while(environ->agentLocations[namesNdx][++sNdx] != ' ')
		{
			currentName[namesNdx][sNdx] = malloc(strlen(environ->agentLocations[namesNdx]));
			currentName[namesNdx][sNdx] = environ->agentLocations[namesNdx][sNdx];
		}

		currentName[namesNdx][sNdx] = malloc(1);
		currentName[namesNdx][sNdx] = '\0';
	}
	currentName[namesNdx] = malloc(1);
	currentName[namesNdx] = '\0';

	int temp1 = 0;
	while(currentName[temp1] != NULL)
	{
		agents[temp1] = malloc(sizeof(struct Location*));
		int temp2 = 0;
		while((name = currentName[temp1][temp2]) != NULL)
		{
			//agents[temp1][temp2] = malloc(sizeof(struct Location*));
			//agents[temp1][temp2] = getLocation(environ, name);
			temp2++;
		}

		//agents[temp1][temp2] = malloc(1);
		//agents[temp1][temp2] = '\0';
		temp1++;
	}

	agents[temp1] = malloc(1);
	agents[temp1] = '\0';

	loc = getLocationSpecified(environ->Map, 1, 1, 0, 0);
	int currenty = 0;
	int xsize = environ->Map->xdim;
	int ysize = environ->Map->ydim;
	while(currenty < ysize)
	{
		int currentx = 0;
		while(currentx < xsize)
		{
			printf("------");
			currentx++;
		}

		printf("\n");
		currentx = 0;

		while(currentx < xsize)
		{
			temp1 = 0;
			while(agents[temp1] != NULL)
			{
				int temp2 = 0;
				//while(agents[temp1][temp2] != NULL)
				{
					//if(agents[temp1][temp2] == loc)
					{
						printf("| A%d |", temp1+1);
					}
					temp2++;
				}

				temp1++;
			}

			if(loc->containsWall)
			{
				printf("||||||");
			}

			else if(loc->containsBreeze && loc->containsStench && loc->containsGold && loc->visited)
			{
				printf("|VSBG|");
			}

			else if(loc->containsBreeze && loc->containsStench && loc->containsExit && loc->visited)
			{
				printf("|VSBE|");
			}

			else if(loc->containsMinion && loc->containsStench && loc->containsBreeze && loc->visited)
			{
				printf("|VMSB|");
			}
			else if(loc->containsMinion && loc->containsStench && loc->visited)
			{
				printf("|VMS |");
			}

			else if(loc->containsMinion && loc->containsBreeze && loc->visited)
			{
				printf("|VMB |");
			}
			else if(loc->containsBreeze && loc->containsStench && loc->visited)
			{
				printf("|VSB |");
			}

			else if(loc->containsExit && loc->containsStench && loc->visited)
			{
				printf("|VES |");
			}

			else if(loc->containsExit && loc->containsBreeze && loc->visited)
			{
				printf("|VEB |");
			}

			else if(loc->containsMinion && loc->containsStench && loc->containsBreeze)
			{
				printf("| MSB|");
			}

			else if(loc->maybePit && loc->containsStench && loc->visited)
			{
				printf("|VSP?|");
			}

			else if(loc->maybeWumpus && loc->containsStench && loc->visited)
			{
				printf("|VSW?|");
			}

			else if(loc->maybePit && loc->containsGold && loc->visited)
			{
				printf("|VP?G|");
			}

			else if(loc->maybeWumpus && loc->containsGold && loc->visited)
			{
				printf("|VW?G|");
			}

			else if(loc->maybePit && loc->containsExit && loc->visited)
			{
				printf("|VP?E|");
			}

			else if(loc->maybeWumpus && loc->containsExit && loc->visited)
			{
				printf("|VW?E|");
			}

			else if(loc->maybePit && loc->containsMinion && loc->visited)
			{
				printf("|VP?M|");
			}

			else if(loc->maybeWumpus && loc->containsMinion && loc->visited)
			{
				printf("|VW?M|");
			}

			else if(loc->maybeWumpus && loc->containsWumpus && loc->visited)
			{
				printf("|VW! |");
			}

			else if(loc->maybePit && loc->containsBreeze && loc->visited)
			{
				printf("|VP?B|");
			}

			else if(loc->maybeWumpus && loc->containsBreeze && loc->visited)
			{
				printf("|VW?B|");
			}

			else if(loc->containsWumpus && loc->containsBreeze && loc->visited)
			{
				printf("|VWB |");
			}

			else if(loc->containsGold && loc->containsStench && loc->visited)
			{
				printf("|VGS |");
			}

			else if(loc->containsGold && loc->containsBreeze && loc->visited)
			{
				printf("|VGB |");
			}

			else if(loc->containsPit && loc->containsStench && loc->visited)
			{
				printf("|VPS |");
			}

			else if(loc->containsBreeze && loc->containsStench && loc->containsGold)
			{
				printf("| SBG|");
			}

			else if(loc->containsBreeze && loc->containsStench && loc->containsExit)
			{
				printf("| SBE|");
			}

			else if(loc->containsBreeze && loc->containsStench)
			{
				printf("| SB |");
			}

			else if(loc->containsBreeze && loc->visited)
			{
				printf("|VB  |");
			}

			else if(loc->containsStench && loc->visited)
			{
				printf("|VS  |");
			}

			else if(loc->containsExit && loc->visited)
			{
				printf("|VE  |");
			}

			else if(loc->maybePit && loc->visited)
			{
				printf("|VP? |");
			}

			else if(loc->maybeWumpus && loc->visited)
			{
				printf("|VW? |");
			}

			else if(loc->containsWumpus && loc->visited)
			{
				printf("|VW  |");
			}

			else if(loc->containsGold && loc->visited)
			{
				printf("|VG  |");
			}

			else if(loc->containsPit && loc->visited)
			{
				printf("|VP  |");
			}

			else if(loc->containsMinion && loc->visited)
			{
				printf("|VM  |");
			}

			else if(loc->containsExit && loc->containsStench)
			{
				printf("| ES |");
			}

			else if(loc->containsExit && loc->containsBreeze)
			{
				printf("| EB |");
			}

			else if(loc->maybePit && loc->containsStench)
			{
				printf("|SP? |");
			}

			else if(loc->maybeWumpus && loc->containsStench)
			{
				printf("|SW? |");
			}

			else if(loc->maybePit && loc->containsGold)
			{
				printf("| P?G|");
			}

			else if(loc->maybeWumpus && loc->containsGold)
			{
				printf("| W?G|");
			}

			else if(loc->maybePit && loc->containsExit)
			{
				printf("| P?E|");
			}

			else if(loc->maybeWumpus && loc->containsExit)
			{
				printf("| W?E|");
			}

			else if(loc->maybePit && loc->containsMinion)
			{
				printf("| P?M|");
			}

			else if(loc->maybeWumpus && loc->containsMinion)
			{
				printf("| W?M|");
			}

			else if(loc->maybeWumpus && loc->containsWumpus)
			{
				printf("| W! |");
			}

			else if(loc->maybePit && loc->containsBreeze)
			{
				printf("| P?B|");
			}

			else if(loc->maybeWumpus && loc->containsBreeze)
			{
				printf("| W?B|");
			}

			else if(loc->containsWumpus && loc->containsBreeze)
			{
				printf("| WB |");
			}

			else if(loc->containsGold && loc->containsStench)
			{
				printf("| GS |");
			}

			else if(loc->containsGold && loc->containsBreeze)
			{
				printf("| GB |");
			}

			else if(loc->containsPit && loc->containsStench)
			{
				printf("| PS |");
			}

			else if(loc->containsMinion && loc->containsStench)
			{
				printf("| MS |");
			}

			else if(loc->containsMinion && loc->containsBreeze)
			{
				printf("| MB |");
			}

			else if(loc->visited)
			{
				printf("| V  |");
			}

			else if(loc->containsBreeze)
			{
				printf("| B  |");
			}

			else if(loc->containsStench)
			{
				printf("| S  |");
			}

			else if(loc->containsExit)
			{
				printf("| E  |");
			}

			else if(loc->maybePit)
			{
				printf("| P? |");
			}

			else if(loc->maybeWumpus)
			{
				printf("| W? |");
			}

			else if(loc->containsWumpus)
			{
				printf("| W  |");
			}

			else if(loc->containsGold)
			{
				printf("| G  |");
			}

			else if(loc->containsMinion)
			{
				printf("| M  |");
			}

			else if(loc->containsPit)
			{
				printf("| P  |");
			}

			else
			{
				printf("|----|");
			}

			currentx++;
			if(currentx < xsize)
			{
				loc = getLocationSpecified(environ->Map, 1, 1, currentx, currenty);
			}
		}

		printf("\n");
		currenty++;
	}

	currenty = 0;
	while(currenty < xsize)
	{
		printf("------");
		currenty++;
	}
	printf("\n");
}*/
