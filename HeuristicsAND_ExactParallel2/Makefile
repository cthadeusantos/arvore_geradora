all:
	clear
	g++ -std=c++11 -pthread -g -O3 -w codigo/*.cpp main.cpp -o exec.out

build_gen_graph:
	clear
	g++ -std=c++11 -g -O3 -w codigo/*.cpp main_generate_graph.cpp -o gen_graph.out
	
build_run_all:
	clear
	g++ -std=c++11 -pthread -g -O3 -w -lrt codigo/*.cpp main_run_all.cpp -o run_all.out

build_run_all2:
	clear
	g++ -std=c++11 -g -O3 -w -lrt codigo/*.cpp main_run_all2.cpp -o run_all2.out

build_run_par:
	clear
	g++ -std=c++11 -pthread -g -O3 -lrt codigo/*.cpp main_paralelo.cpp -o run_par.out

build_teste:
	clear
	g++ -std=c++11 -g -O3 -lrt codigo/*.cpp main_teste.cpp -o teste.out