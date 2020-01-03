#include "main.h"
       #include <sys/types.h>
       #include <sys/stat.h>
       #include <fcntl.h>

int main(int argc, char const *argv[])
{
	if (argc == 1){
		printf("Please specify a command line argument (-c, -r, -v)\n");
		return 0;
	}
	else if (strcmp(argv[1], "-c") == 0){
		printf("Creating shared memory\n");
		int shmid;
		shmid = shmget(SHM_KEY, sizeof(char *), IPC_CREAT | 0644);
		printf("shmid: %i\n", shmid);
		if (shmid == -1){
			printf("Well that didn't work. uh oh\n");
			printf("%s\n",strerror(errno));
			printf("%i",errno);
			return 1;
		}
		printf("Creating the semaphore\n");
		int semid = semget(SEM_KEY, 1, IPC_CREAT | IPC_EXCL | 0644);
		printf("semid: %i\n", semid);		
		if (semid == -1){
			semid = semget(SEM_KEY, 1, 0);
		}
    union semun us;
    us.val = 1;
    semctl(semid, 0 , SETVAL, us);


    printf("Creating the file\n");
    int fd = open("story.txt", O_CREAT | O_TRUNC | O_RDWR, 0644);
    if (fd == -1) {
      printf("Error: %s\n", strerror(errno));
      return -1 ;
    }
    close(fd);
	}
	else if (strcmp(argv[1], "-r") == 0){
		printf("Removing the shared memory\n");
		int shmid;
		shmid = shmget(SHM_KEY, sizeof(char *), IPC_CREAT | 0644);
		if (shmid == -1){
			printf("Well that didn't work. uh oh %s \n", strerror(errno));
			return 1;
		}
		shmctl(shmid, IPC_RMID, 0);

		printf("Removing the semaphore\n");
		int semid = semget(SEM_KEY, 1, 0);
		if (semid == -1){
			printf("Uh oh I couldn't get the semaphore\n");
		}
    struct sembuf sb;
    sb.sem_num = 0;
    sb.sem_op = -1;
    semop(semid, &sb, 1);
		semctl(semid, 0, IPC_RMID);

    int fd = open("story.txt", O_RDONLY);
    char story[1024];
    read(fd, story, 20479) ;
    printf("Here is the story:\n%s\n", story);
    if (remove("story.txt") == 0){
      printf("File Deleted\n");
    }
    else{
      printf("unable to delete file\n");
    }
	}
	else if (strcmp(argv[1], "-v") == 0){
		printf("The story so far:\n");
    int fd = open("story.txt", O_RDONLY);
    char story[1024];
    read(fd, story, 20479) ;
    printf("Here is the story:\n%s\n", story);
	}
	else{
		printf("that command is not recognized\n");
	}
	return 0;
}