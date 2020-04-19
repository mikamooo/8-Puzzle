all: driver tester

driver: driver.cpp graph.cpp
	g++ -o driver -std=c++17 driver.cpp graph.cpp

tester: algo_test.cpp graph.cpp
	g++ -o tester -std=c++17 algo_test.cpp graph.cpp