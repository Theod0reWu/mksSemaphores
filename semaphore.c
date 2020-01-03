#include "main.h"

int main(int argc, char const *argv[])
{
	int semid = semget(SEM_KEY, 1, 0);
	struct sembuf sb;
	sb.sem_num = 0;
    sb.sem_op = -1;
    sb.sem_flg = SEM_UNDO ;
  	int sem_opp = semop(semid, &sb, 1);

  	int shmid = shmget(SHM_KEY, sizeof (char), 0644);
  	if (shmid == -1){
			printf("Well that didn't work. uh oh\n");
			printf("%s\n",strerror(errno));
			printf("%i",errno);
			return 1;
	}
	int * line = shmat(shmid,0,0);
	printf("Last Line: %s\n", line);
	char * newLine;
	printf("New Line: ");
	fgets(newLine, 1024, stdin);
	int fd = open("story.txt", O_CREAT | O_TRUNC | O_RDWR, 0644) ;
	write(fd, newLine, 1024);
	close(fd);

	strcpy(line, newLine);
	shmdt(line);
	sb.sem_op = 1;
	semop(semid, &sb, 1);


	return 0;
}