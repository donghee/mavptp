all: timesync

timesync: clean format
	g++ -I mavlink -Ofast -std=c++11 -o timesync  main.cpp serial_port.cpp -lpthread 

clean:
	 rm -rf *.o timesync

format:
	astyle --options=./astylerc --preserve-date main.cpp

lowlatency:
	setserial /dev/ttyACM0 low_latency
	#setserial /dev/S0 low_latency
