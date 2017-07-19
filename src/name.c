/* name.c */

#include <malloc.h> /* malloc, free */
#include <string.h> /* memset, memcpy */
#include <ctype.h> /* isalpha */
#include "name.h" /* NAME_SIZE_MAX */

static char** name_list;
static unsigned int name_count;

char* name_new(const char* name)
{
	unsigned int i;
	char* newName;

	if ( !name || !strcmp(name, "") ) return NULL;

	newName = malloc((NAME_SIZE_MAX +1) * sizeof (char));
	memset(newName, 0, NAME_SIZE_MAX +1);
	memcpy(newName, name, NAME_SIZE_MAX);

	for ( i=0; i<name_count; i++ ) /* unique name? */
		if ( !strcmp(name_list[i], newName) )
		{
			free(newName);
			return NULL; 
		}
	for ( i=0; i<strlen(newName); i++ ) /* sanitary? */
		if ( !isalpha(newName[i]) && newName[i] != 32 )
		{
			free(newName);
			return NULL;
		}
	name_list = realloc(name_list, (name_count +1) * sizeof (char*));
	name_list[name_count] = newName;
	return name_list[name_count++];
}

int name_remove(const char* name)
{
	unsigned int i;
	if ( !name ) return -1;

	for ( i=0; i<name_count; i++ )
		if ( !strcmp(name, name_list[i]) )
		{
			for ( ; i<name_count-1; i++ )
				name_list[i] = name_list[i+1];
			name_count--;
			return 0; /* name was removed */
		}
		return -2; /* no such name */
}

int name_change(char* oldName, char* newName)
{
	unsigned int i;
	if ( !oldName || !newName ) return -1;
	
	for ( i=0; i<name_count; i++ )
		if ( !strcmp(oldName, name_list[i]) && name_new(newName) )
		{
			strcpy(name_list[i], newName);
			name_remove(newName);
			return 0; /* name was changed */
		}
		return -2; /* no such name */
}

/* end of file */
