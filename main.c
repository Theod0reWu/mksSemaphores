#include "main.h"

int main(int argc, char const *argv[])
{
	if (argc == 1){
		printf("Please specify a command line argument (-c, -r, -v)\n");
		return 0;
	}
	else if (strcmp(argv[1], "-c") == 0){
		printf("Creating semaphore\n");
		int shmid;
		shmid = shmget(KEY, 256 * sizeof(char), IPC_CREAT | 0644);
		printf("%i\n", shmid);
		if (shmid == -1){
			printf("Well that didn't work. uh oh\n");
			perror("shared memory");
			return 1;
		}

	}
	else if (strcmp(argv[1], "-r") == 0){
		printf("Removing the shared memory\n");
		int shmid;
		shmid = shmget(12345, 256 * sizeof(char), IPC_CREAT | 0644);
		if (shmid == -1){
			printf("Well that didn't work. uh oh\n");
			return 1;
		}
		shmctl(shmid, IPC_RMID, 0);
	}
	else if (strcmp(argv[1], "-v") == 0){
		printf("The story so far:\n");
	}
	else{
		printf("that command is not recognized\n");
	}
	return 0;
}