/* user.h */

#define USER_TEAM_MAX 8

struct user
{
	char* name;
	struct agent* member[USER_TEAM_MAX];
	unsigned int member_count;
};

struct user* user_new(const char*);
int user_remove(struct user*);
int user_team_assign(struct user*, struct agent*);
