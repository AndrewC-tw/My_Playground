#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <errno.h>

int main(int argc, char **argv)
{
	int size = 16, i = 0;
	if(argc > 1)
		size = strtol(*(argv + 1), NULL, 10);
	int fd_shm = shm_open ("/test", O_RDWR | O_CREAT, 0660);
	int rtn = 0;
	fprintf(stderr, "AA\n");
	//write(fd_shm, "Hello moto000!\n", size);
	fprintf(stderr, "BB\n");
	if((rtn = ftruncate(fd_shm, size)))
		perror("");
	char *test = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd_shm, 0);
	//char *test = malloc(size);
	for(; i < size; i++)
		strncpy((test+i), "a", 1);
	fprintf(stderr, "CC\n");
	printf("test=%p\n", test);
	//printf("test=%s\n", test);
	strcpy(test, "Hello World!!\n");
	printf("test=%p\ntest=%s\n", test, test);
	sleep(3);
	munmap(test, size);
	shm_unlink("/test");
	close(fd_shm);
	return 0;
}