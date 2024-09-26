

obj: ../src/*
	g++ -c -g ../src/chess/*.cpp
	g++ -c -g ../src/memoryallocator/*.cpp
	g++ -c -g ../src/hashtable/*.cpp

client: obj ../src/topology/bss.h ../src/topology/chess_ai_client.cpp 
	g++ -g ../src/topology/chess_ai_client.cpp *.o ../dependency/obj/*.a -o client
	
server: obj ../src/topology/bss.h ../src/topology/chess_ai_load_balancer.cpp 
	g++ -g ../src/topology/chess_ai_load_balancer.cpp *.o ../dependency/obj/*.o ../dependency/obj/*.a -o server

compute: obj ../src/topology/bss.h ../src/topology/chess_ai_compute_node.cpp 
	g++ -g ../src/topology/chess_ai_compute_node.cpp *.o ../dependency/obj/*.o ../dependency/obj/*.a -o compute

local: client server compute
	mv client ../run
	mv server ../run
	mv compute ../run

clean:
	rm ./*.o
