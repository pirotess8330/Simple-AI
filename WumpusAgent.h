/* 
   Wumpus World
*/

#ifndef WUMPUSAGNETH
#define WUMPUSAGENTH

#include "Environment.h"

typedef struct WA
{
   int movementCost;
   int searchCost;
   int life;
   int numberOfArrows;
   char* name;
   int orientation;
   struct Location* start;

}WumpusAgent;

extern WumpusAgent* createAgent();
extern void addToSearchCost(int newCost, int* oldCost);
extern void addToMovementCost(int newCost, int* oldCost);
extern void alterLifeValue(int newValue, int* life);
extern void alterNumberOfArrows(int newValue, int* numberOfArrows);
extern void setName(char* newName, char** name);
extern struct Location* getAgentLocation(WumpusAgent* agent, struct Environment* environment);
extern int isGoalReached(WumpusAgent* agent, struct Environment* environment);
extern int getSearchCost(WumpusAgent* agent);
extern int getMovementCost(WumpusAgent* agent);
extern int getLifeValue(WumpusAgent* agent);
extern int getNumberOfArrows(WumpusAgent* agent);
extern char* getName(WumpusAgent* agent);
extern void moveForward(WumpusAgent* agent, struct Environment* environment);
extern void turnLeft(WumpusAgent* agent);
extern void turnRight(WumpusAgent* agent);
extern void turnTo(int direction, WumpusAgent* agent);
extern void setStartingLocation(WumpusAgent* agent, struct Environment* envrion);
extern struct Location* getStartingLocation(WumpusAgent* agent);
extern int random1(int value);

#endif
