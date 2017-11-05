#include <stdio.h>                                                              
#include <fcntl.h>                                                              
#include <sys/mman.h>                                                           
#include <stdint.h>                                                             
#include <time.h>
#include <unistd.h>

#include <wiringPi.h>

// Toggle GPA0.2
#define ODROIDXU_GPA_BASE   0x14010000  
static volatile uint32_t *gpio;                                                 

#define NSEC_PER_SEC 1000000000

int main(int argc, char **argv)                                                 
{                                                                               
	wiringPiSetup();
	pinMode(1, OUTPUT);

	int fd ;                                                                

	if ((fd = open ("/dev/mem", O_RDWR | O_SYNC) ) < 0) {                   
		printf("Unable to open /dev/mem\n");                            
		return -1;                                                      
	}                                                                       

	gpio = mmap(0, getpagesize(), PROT_READ|PROT_WRITE, MAP_SHARED, fd,     ODROIDXU_GPA_BASE);

	if (gpio < 0){                                                          
		printf("Mmap failed.\n");                                       
		return -1;                                                      
	}                                                                       

	struct timespec tv;

	// Print GPA0BASE
	//printf("GPA0BASE: 0x%08x\n", (unsigned int)(gpio));       

	// Set direction of GPA0.2 configuration register as out.               
	*(gpio + 0)  |= (0x1 << 8);                                  
	//printf("GPA0CON register : 0x%08x\n", *(unsigned int *)(gpio));       

	while(1) {
		clock_gettime(CLOCK_REALTIME, &tv);
		if(tv.tv_sec % 1 == 0 && tv.tv_nsec < NSEC_PER_SEC / 10000) { // 100us
			//// GPX1.2 High                                                          
			*(gpio + 1) |= (0x1 << 2);                                    
			//printf("GPA0DAT register : 0x%08x\n", *(unsigned int *)(gpio + 1));       
		} else {
			// GPX1.2 Low                                                           
			*(gpio + 1) &= ~(0x1 << 2);                                   
			//printf("GPA0DAT register : 0x%08x\n", *(unsigned int *)(gpio + 1));       
		}
		usleep(1);
	}


	return 0;                                                               
}
