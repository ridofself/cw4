/* test.c */

#include <stdio.h> /* printf */
#include <assert.h> /* assert */
#include <string.h> /* strcmp */

static unsigned int test_count;

#include "name.h"

int test_test()
{
	assert(1);
	test_count++;
	return 0;
}

int test_name_new()
{
	char* name = "store this name";
	unsigned int i;
	char longName[NAME_SIZE_MAX +1];

	char* storedName = name_new(name);
	assert(storedName);
	test_count++;

	assert(!strcmp(name, storedName));
	test_count++;

	assert(!name_new(name)); /* NULL: name already stored */
	test_count++;

	assert(!name_new(NULL));
	test_count++;

	assert(!name_new(""));
	test_count++;

	for ( i=0; i<NAME_SIZE_MAX +1; i++ ) longName[i] = 'x';
	assert(strcmp(name_new(longName), longName));
	test_count++;

	name = "illeg@l ch@r n@m3!";
	assert(!name_new(name));
	test_count++;

	name_remove(name);
	name_remove(longName);
		
	return 0;
}

int test_name_remove()
{
	char* name = "to be removed";
	name_new(name);
	assert(!name_remove(name));
	test_count++;

	assert(name_remove(name) == -2);
	test_count++;

	assert(name_remove(NULL) == -1);
	test_count++;

	return 0;
}

int test_name_change()
{
	char* oldName = "Gandalf the Grey";
	char* newName = "Gandalf the White";
	name_new(oldName);
	assert(name_change(NULL, newName) == -1);
	assert(name_change(oldName, NULL) == -1);
	test_count++;

	assert(!name_change(oldName, newName));
	test_count++;

	assert(name_change(oldName, newName) == -2);
	test_count++;

	return 0;
}

#include "user.h"

int test_user_new()
{
	struct user* user;
	char* name = "new user name";
	user = user_new(name);
	assert(user);
	test_count++;

	assert(!strcmp(user->name, name));
	test_count++;

	assert(!user_new(name));
	test_count++;

	user_remove(user);

	return 0;
}

int test_user_remove()
{
	struct user* user;
	char* name = "user to remove";
	user = user_new(name);
	assert(!user_remove(user));
	test_count++;

	assert(user_remove(user) == -1);
	test_count++;

	return 0;
}

#include "agent.h"

int test_agent_new()
{
	struct agent* agent;
	char* name = "new agent name";
	agent = agent_new(name);
	assert(agent);
	test_count++;

	assert(!strcmp(agent->name, name));
	test_count++;

	assert(!agent_new(name));
	test_count++;

	agent_remove(agent);

	return 0;
}

int test_agent_remove()
{
	struct agent* agent;
	char* name = "agent to remove";
	agent = agent_new(name);
	assert(!agent_remove(agent));
	test_count++;

	assert(agent_remove(agent) == -1);
	test_count++;

	return 0;
}

int test_user_agent_assign()
{
	struct agent* agent = agent_new("users agent");
	struct user* user = user_new("agents user");
	assert(!user_agent_assign(user, agent));
	test_count++;

	assert(user->agent[user->agent_count -1] == agent);
	test_count++;

	assert(user_agent_assign(user, agent) == -3);
	test_count++;
	
	agent_remove(agent);
	user_remove(user);

	assert(user_agent_assign(NULL, NULL) == -2);
	test_count++;

	return 0;
}

int test_user_agent_resign()
{
	struct agent* agent = agent_new("users agent");
	struct user* user = user_new("agents user");
	user_agent_assign(user, agent);

	assert(!user_agent_resign(user, agent));
	test_count++;

	assert(user_agent_resign(user, agent) == -1);
	test_count++;

	agent_remove(agent);
	user_remove(user);

	assert(user_agent_resign(NULL, NULL) == -2);
	test_count++;

	return 0;
}

int test_all()
{
	test_test();
	test_name_new();
	test_name_remove();
	test_name_change();
	test_user_new();
	test_user_remove();
	test_agent_new();
	test_agent_remove();
	test_user_agent_assign();
	test_user_agent_resign();
	return 0;
}

int main()
{
	printf("\ntesting...");
	assert(!test_all());
	printf("\t%d tests were run successfully\n\n", test_count);
	return 0;
}
