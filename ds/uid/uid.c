#include <unistd.h>
#include <time.h>

#include "uid.h"


extern size_t getCounter(unique_id_t uid);
extern size_t getTime(unique_id_t uid);
extern size_t getPid(unique_id_t uid);


const unique_id_t uid_null_uid = {0, 0, 0};


unique_id_t UIDGenerate(void)
{
	static size_t counter = 0;
	unique_id_t new_uid;
	
	new_uid.counter = counter;
	new_uid.timestamp = time(NULL);
	new_uid.pid = getpid(); 
		
	++counter;
	return new_uid;
}


bool_t UIDIsEqual(unique_id_t uid1, unique_id_t uid2)
{
	return (uid1.counter == uid2.counter) &&
			!(difftime(uid1.timestamp, uid2.timestamp)) && 
			(uid1.pid == uid2.pid);
}



/* ------------------------------ helper functions ------------------------------- */



size_t getCounter(unique_id_t uid)
{
	return uid.counter;
}


size_t getTime(unique_id_t uid)
{
	return (size_t)uid.timestamp;
}


size_t getPid(unique_id_t uid)
{
	return (size_t)uid.pid;
}


