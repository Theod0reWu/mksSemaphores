#include "main.h"

int main(int argc, char const *argv[])
{
	if (argc == 1){
		printf("Please specify a command line argument (-c, -r, -v)\n");
		return 0;
	}
	else if (strcmp(argv[1], "-c") == 0){
		printf("Creating shared memory\n");
		int shmid;
		shmid = shmget(SHM_KEY, sizeof(char) * 128, IPC_EXCL | IPC_CREAT | 0644);
		printf("shmid: %i\n", shmid);
		if (shmid == -1){
			printf("Well that didn't work. uh oh\n");
			printf(strerror(errno));
			printf("%i",errno);
			return 1;
		}
		printf("Creating the semaphore\n");
		int semid = semget(SEM_KEY, 1, IPC_CREAT | IPC_EXCL | 0644);
		printf("semid: %i\n", semid);		
		if (semid == -1){
			semid = semget(SEM_KEY, 1, 0);
		}

	}
	else if (strcmp(argv[1], "-r") == 0){
		printf("Removing the shared memory\n");
		int shmid;
		shmid = shmget(SHM_KEY, 256 * sizeof(char), 0);
		if (shmid == -1){
			printf("Well that didn't work. uh oh %s \n", strerror(errno));
			return 1;
		}
		shmctl(shmid, IPC_RMID, 0);

		printf("Remvoing the semaphore\n");
		int semid = semget(SEM_KEY, 1, 0);
		if (semid == -1){
			printf("Uh oh I couldn't get the semaphore\n");
		}
		semctl(semid, 0, IPC_RMID);
	}
	else if (strcmp(argv[1], "-v") == 0){
		printf("The story so far:\n");
	}
	else{
		printf("that command is not recognized\n");
	}
	return 0;
}