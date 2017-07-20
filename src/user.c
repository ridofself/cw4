/* user.c */

#include <malloc.h> /* malloc, NULL */
#include "user.h"
#include "name.h"

static struct user** user_list;
static unsigned int user_count;

struct user* user_new(const char* name)
{
	struct user* newUser;
	char* userName;

	userName = name_new(name);
	if ( !userName ) return NULL;

	newUser = malloc(sizeof (struct user));
	newUser->name = userName;
	user_list = realloc(user_list, (user_count +1) * sizeof (struct user*));
	user_list[user_count] = newUser;
	return user_list[user_count++];
}

int user_remove(struct user* user)
{
	unsigned int i;
	for ( i=0; i<user_count; i++ )
		if ( user_list[i] == user )
		{
			name_remove(user_list[i]->name);
			for ( ; i<user_count-1; i++ )
				user_list[i] = user_list[i+1];
			user_count--;
			return 0;
		}
	return -1;
}

int user_agent_assign(struct user* user, struct agent* agent)
{
	int i;
	if ( !user || !agent ) return -2;
	if ( user->agent_count >= USER_TEAM_MAX ) return -1;

	for ( i=0; i<USER_TEAM_MAX; i++ )
		if ( agent == user->agent[i] ) return -3;
	
	user->agent[user->agent_count++] = agent;
	return 0;
}

int user_agent_resign(struct user* user, struct agent* agent)
{
	int i;
	if ( !user || !agent ) return -2;
	for ( i=0; i<USER_TEAM_MAX; i++ )
		if ( agent == user->agent[i] )
		{
			for ( ; i<USER_TEAM_MAX-1; i++ )
				user->agent[i] = user->agent[i-1];
			user->agent_count--;
			return 0;
		}
		return -1;
}

/* end of file */
