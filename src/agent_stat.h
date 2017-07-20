/* agent_stat.h */

#ifndef AGENT_STAT_H
#define AGENT_STAT_H

struct agent_stat
{
	float grain;
	float water;
	float fat;
};

float agent_stat_weight(struct agent_stat*);

#endif
/* end of file */
