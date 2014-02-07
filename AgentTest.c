#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "WumpusAgent.h"
#include "Directions.h"

int main()
{
	WumpusAgent* agent;
	agent = createAgent();

	printf("Creating Step:\n");
	printf("MovementCost  - should be 0: %d\n", getMovementCost(agent));
	printf("SearchCost    - should be 0: %d\n", getSearchCost(agent));
	printf("AgentLife - should be 10000: %d\n",	getLifeValue(agent));
	printf("NumberArrows - should be 10: %d\n", getNumberOfArrows(agent));
	printf("AgentName  - should be NULL: %s\n",	getName(agent));
	printf("Orientation   - should be 1: %d\n\n", agent->orientation);

	addToSearchCost(15, &(agent->searchCost));
	addToSearchCost(7, &(agent->searchCost));

	addToMovementCost(11, &(agent->movementCost));
	addToMovementCost(7, &(agent->movementCost));

	alterLifeValue(-100, &(agent->life));
	alterLifeValue(-50, &(agent->life));
	alterLifeValue(75, &(agent->life));

	alterNumberOfArrows(-5, &(agent->numberOfArrows));
	alterNumberOfArrows(3, &(agent->numberOfArrows));

	setName("first", &(agent->name));
	setName("second", &(agent->name));
	setName("third", &(agent->name));

	printf("After Manipulation:\n");
	struct Location* loc;
	struct Location* loc2;
	struct Environment* environ;
	environ = createEnvironment("twentySQtemplate");
	loc2 = getLocationSpecified(environ->Map, 1, 1, 19, 19);
	printf("Get Location call: x = %d, y = %d", loc2->xcoordinate, loc2->ycoordinate);
	loc2 = getLocationSpecified(environ->Map, 1, 1, 10, 5);
	printf("Get Location call: x = %d, y = %d", loc2->xcoordinate, loc2->ycoordinate);
	loc = getAgentLocation(agent, environ);
	printf("Get Location call: x = %d, y = %d", loc->xcoordinate, loc->ycoordinate);
	printf("MovementCost - should be 18: %d\n", getMovementCost(agent));
	printf("SearchCost   - should be 22: %d\n", getSearchCost(agent));
	printf("AgentLife  - should be 9925: %d\n",	getLifeValue(agent));
	printf("NumberArrows  - should be 8: %d\n", getNumberOfArrows(agent));
	printf("AgentName - should be third: %s\n",	getName(agent));

	printf("Orientation   - should be 1: %d\n", agent->orientation);
	turnLeft(agent);
	printf("Orientation   - should be 4: %d\n", agent->orientation);
	turnLeft(agent);
	printf("Orientation   - should be 3: %d\n", agent->orientation);
	turnRight(agent);
	printf("Orientation   - should be 4: %d\n", agent->orientation);
	turnRight(agent);
	printf("Orientation   - should be 1: %d\n", agent->orientation);
	turnRight(agent);
	printf("Orientation   - should be 2: %d\n", agent->orientation);
	turnLeft(agent);
	printf("Orientation   - should be 1: %d\n", agent->orientation);
	turnLeft(agent);
	printf("Orientation   - should be 4: %d\n", agent->orientation);

	printf("MovementCost - should be 68: %d\n", getMovementCost(agent));
	turnTo(WEST, agent);
	printf("Orientation   - should be 4: %d\n", agent->orientation);
	turnTo(SOUTH, agent);
	printf("Orientation   - should be 3: %d\n", agent->orientation);
	turnTo(EAST, agent);
	printf("Orientation   - should be 2: %d\n", agent->orientation);
	turnTo(NORTH, agent);
	printf("Orientation   - should be 1: %d\n", agent->orientation);
	printf("MovementCost - should be 78: %d\n", getMovementCost(agent));
}
