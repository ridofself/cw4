/* agent_stat.c */

#include "agent.h" /* struct agent->stat */
#include "agent_stat.h"

float agent_stat_weight(struct agent_stat* stat)
{
	return stat->fat + stat->water + stat->grain;
}

/* end of file */
