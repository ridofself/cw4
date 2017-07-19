/* agent.c */

#include <malloc.h> /* malloc, NULL */
#include "name.h"
#include "agent.h"
#include "user.h"

static struct agent** agent_list;
static unsigned int agent_count;

struct agent* agent_new(const char* name)
{
	struct agent* newUser;
	char* agentName;

	agentName = name_new(name);
	if ( !agentName ) return NULL;

	newUser = malloc(sizeof (struct agent));
	newUser->name = agentName;
	agent_list =
		realloc(agent_list, (agent_count +1) * sizeof (struct agent*));
	agent_list[agent_count] = newUser;
	return agent_list[agent_count++];
}

int agent_remove(struct agent* agent)
{
	unsigned int i;
	for ( i=0; i<agent_count; i++ )
		if ( agent_list[i] == agent )
		{
			name_remove(agent_list[i]->name);
			for ( ; i<agent_count-1; i++ )
				agent_list[i] = agent_list[i+1];
			agent_count--;
			return 0;
		}
	return -1;
}

/* end of file */
