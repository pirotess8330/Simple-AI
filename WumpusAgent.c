/* 
   Wumpus World
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Environment.h"
#include "Directions.h"
#include "WumpusAgent.h"

#define INTERACTION 1
#define HINT 5
#define MOVE 20
#define TURN 0

WumpusAgent* createAgent()
{
	WumpusAgent *agent = malloc(sizeof(WumpusAgent));
	agent->movementCost = 0;
	agent->searchCost = 0;
	agent->life = 10000;
	agent->numberOfArrows = 10;
	agent->name = "\0";
	agent->orientation = NORTH;
	agent->start = NULL;
    return agent;
}

void addToSearchCost(int newCost, int* oldCost)
{
	*oldCost += newCost;
}

void addToMovementCost(int newCost, int* oldCost)
{
	*oldCost += newCost;
}

void alterLifeValue(int newValue, int* life)
{
	*life += newValue;
}

void alterNumberOfArrows(int newValue, int* numberOfArrows)
{
	*numberOfArrows += newValue;
}

void setName(char* newName, char** name)
{
	*name = newName;
}

struct Location* getAgentLocation(WumpusAgent* agent, struct Environment* environment)
{
	addToSearchCost(INTERACTION, &(agent->searchCost));

	return getLocation(environment, agent->name);
}

int isGoalReached(WumpusAgent* agent, struct Environment* environment)
{
	addToSearchCost(INTERACTION, &(agent->searchCost));

	return hasGoalBeenFound(environment);
}

int getSearchCost(WumpusAgent* agent)
{
	return agent->searchCost;
}

int getMovementCost(WumpusAgent* agent)
{
	return agent->movementCost;
}

int getLifeValue(WumpusAgent* agent)
{
	return agent->life;
}

int getNumberOfArrows(WumpusAgent* agent)
{
	return agent->numberOfArrows;
}

char* getName(WumpusAgent* agent)
{
	return agent->name;
}

void moveForward(WumpusAgent* agent, struct Environment* environment)
{
	addToMovementCost(MOVE, &(agent->movementCost));

	moveAgent(environment, agent->name, agent->orientation);
}

void turnLeft(WumpusAgent* agent)
{
	addToMovementCost(TURN, &(agent->movementCost));
	if(agent->orientation == NORTH)
	{
		agent->orientation = WEST;
	}

	else if(agent->orientation == EAST)
	{
		agent->orientation = NORTH;
	}

	else if(agent->orientation == SOUTH)
	{
		agent->orientation = EAST;
	}

	else if(agent->orientation == WEST)
	{
		agent->orientation = SOUTH;
	}
}

void turnRight(WumpusAgent* agent)
{
	addToMovementCost(TURN, &(agent->movementCost));
	if(agent->orientation == NORTH)
	{
		agent->orientation = EAST;
	}

	else if(agent->orientation == EAST)
	{
		agent->orientation = SOUTH;
	}

	else if(agent->orientation == SOUTH)
	{
		agent->orientation = WEST;
	}

	else if(agent->orientation == WEST)
	{
		agent->orientation = NORTH;
	}
}

void turnTo(int direction, WumpusAgent* agent)
{
	addToMovementCost(TURN, &(agent->movementCost));
	agent->orientation = direction;
}

void setStartingLocation(WumpusAgent* agent, struct Environment* environ)
{
	int x = random1(environ->Map->xdim);
	int y = random1(environ->Map->ydim);
	agent->start = getLocationSpecified(environ->Map, 1, 1, x, y);
}

struct Location* getStartingLocation(WumpusAgent* agent)
{
	return agent->start;
}

unsigned long next = 1;

int random1(int value)
{
	next = next * 1103515245 + 12345;
	return(unsigned int)(next/65536) % (value + 1);
}


