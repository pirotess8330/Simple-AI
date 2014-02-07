/* James Macauley & Ilia Standish
   CPE 480
   Assignment 3 - Wumpus World
*/
#ifndef ENVIRONMENTH
#define ENVIRONMENTH

struct Environment{
	struct Grid* Map;
	char** agentLocations;
	int goalFound;
};

struct Grid{
	struct Location*** twodarr;
	int xdim;
	int ydim;
};

struct Location{
	int xcoordinate;
	int ycoordinate;
	int visited;
	int containsWall;
	int containsStench;
	int containsBreeze;
	int containsGold;
	int containsWumpus;
	int containsMinion;
	int containsExit;
	int containsPit;
	int maybePit;
	int maybeWumpus;
};

extern struct Grid* SetupMap(char* filename);
extern struct Environment* createEnvironment(char* filename);
extern struct Location* createLocation(int x, int y, int, int, int, int, int, int, int, int);
extern struct Location* getLocationSpecified(struct Grid* Map, int, int, int x, int y);
extern struct Location* getLocation(struct Environment* environ, char* agentName);
extern void moveAgent(struct Environment* environ, char* agentName, int direction);
extern int hasGoalBeenFound(struct Environment* environ);
extern int isWall(struct Grid* Map, int x, int y);
extern int isWumpus(struct Grid* Map, int x, int y);
extern int isMinion(struct Grid* Map, int x, int y);
extern int isGold(struct Grid* Map, int x, int y);
extern int isPit(struct Grid* Map, int x, int y);
extern int isMaybePit(struct Grid* Map, int x, int y);
extern int isMaybeWumpus(struct Grid* Map, int x, int y);
extern void setStench(struct Grid* Map, int x, int y);
extern void setBreeze(struct Grid* Map, int x, int y);
extern void setGold(struct Grid* Map, int x, int y);
extern void setWumpus(struct Grid* Map, int x, int y);
extern void setMinion(struct Grid* Map, int x, int y);
extern void setExit(struct Grid* Map, int x, int y);
extern void setPit(struct Grid* Map, int x, int y);
extern void setMaybePit(struct Grid* Map, int x, int y);
extern void setMaybeWumpus(struct Grid* Map, int x, int y);
extern void setGoalFound(struct Environment* environ);
/*extern void printMap(struct Environment* environ);*/
extern void addAdjacentLocationCount(struct Location* location);

#endif
