#include <stdio.h>
#include "uid.h"
#include <sys/time.h>
#include <unistd.h>


int main()
{
	unique_id_t uid1 = uid_null_uid;
	unique_id_t uid2 = uid_null_uid;
	
	size_t now = (size_t)time(NULL);
	size_t thisProccess = (size_t)getpid();
	
	if(!(UIDIsEqual(uid1, uid2) == 1))
	{
		printf("fail in %d\n", __LINE__);
	}

	uid1 = UIDGenerate();
	
	if(!(UIDIsEqual(uid1, uid2) == 0))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	if(!(getCounter(uid1) == 0))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	if(!(getTime(uid1) == now))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	if(!(getPid(uid1) == thisProccess))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	sleep(3);

	uid2 = UIDGenerate();
	
	if(!(UIDIsEqual(uid1, uid2) == 0))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	if(!(getCounter(uid2) == 1))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	if(!(getTime(uid2) == now + 3))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	if(!(getPid(uid2) == thisProccess))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	if(!(getTime(uid2) == getTime(uid1) + 3))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	if(!(getPid(uid2) == getPid(uid1)))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	return 0;
}
