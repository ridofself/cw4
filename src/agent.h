/* agent.h */

struct agent
{
	char* name;
};

struct agent* agent_new(const char*);
int agent_remove(struct agent*);
