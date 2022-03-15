#ifndef __UID_H__
#define __UID_H__

#include <time.h>
#include <sys/types.h>


/* UID struct */
typedef struct UID 
{
	size_t counter;
	time_t timestamp;
	pid_t pid;
} unique_id_t;


typedef int bool_t;


/* aka BADUID */
extern const unique_id_t uid_null_uid; 

/* generate a unique identifier */ 
extern unique_id_t UIDGenerate(void);

/* check two UIDs for equality */
extern bool_t UIDIsEqual(unique_id_t uid1, unique_id_t uid2); 

extern size_t getCounter(unique_id_t uid);

extern size_t getTime(unique_id_t uid);

extern size_t getPid(unique_id_t uid);



#endif

