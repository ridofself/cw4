/* agent.h */

#ifndef AGENT_H
#define AGENT_H 

struct agent
{
	char* name;
	struct agent_stat* stat;
};

struct agent* agent_new(const char*);
int agent_remove(struct agent*);

#endif
/* end of file */
