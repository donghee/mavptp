all: gpiosync

gpiosync: clean 
	gcc -o gpiosync main.c -lwiringPi -lpthread 

wiringPi_test: clean
	gcc -o wiringPi_test wiringPi_test.c -lwiringPi -lpthread 

clean:
	 rm -rf *.o gpiosync wiringPi_test

