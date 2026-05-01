#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h> //for o_creat, o_rdwr
#include <sys/shm.h> //for shared memory constant
#include <sys/mman.h> //for shm_open & mmap
#include <sys/stat.h> //for mode constant -0777
#include <unistd.h> //for ftruncate


int main () {
	const int SIZE = 8192; //size of the shared memory object(8kb)
	
	const char *name = "SharedMemory"; //name of the shared memory

	const char *message1 ="First message in the shared memory";
	const char *message2 ="Second message in the shared memory";

	int fd; //creating a file descriptor for the shared memory
	
	//creating the shared memory 
	fd=shm_open(name, O_CREAT | O_RDWR, 0777); //shm_open = shared memory open
	// O_crea = create the memory, O_RDWR= read and write 
	//0777 permission 
	
	ftruncate(fd, SIZE); //setting the size of the memory

	void *ptr=mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0); 
	//mapping the object of the shared memory to the address space
	
	char *p=(char *)ptr; //temp pointer to the shared memory ptr so that the initial pointer stays at the original address	

	//write to the shared memory
	sprintf(p, "%s", message1);
	p+=strlen(message1);
	sprintf(p, "%s", message2);
	p+=strlen(message2);

	printf("Data: %s\n", (char *)ptr); //verify the data in the shared mmemory	
	munmap(ptr, SIZE); //unlink the memory
	close(fd);
	shm_unlink(name); //remove the object from the system;
	return 0;

}
