/* user.h */

#ifndef USER_H
#define USER_H
#define USER_TEAM_MAX 8

struct user
{
	char* name;
	struct agent* agent[USER_TEAM_MAX];
	unsigned int agent_count;
};

struct user* user_new(const char*);
int user_remove(struct user*);
int user_agent_assign(struct user*, struct agent*);
int user_agent_resign(struct user*, struct agent*);

#endif

/* end of file */
