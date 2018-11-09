CXX     	= g++
CXXFLAGS  	= -Wall -std=c++11
OBJS    	= runningstat.o tabu_search.o tabu_list.o grasp.o local_search.o sorted_heuristic.o cheng_church.o teng_chan.o matrix.o bicluster.o readcsv.o main.o util.o


TARGET	= proj

default: $(TARGET)
	@echo Done.

$(TARGET): $(OBJS) 
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@

main.o: main.cpp readcsv.h tabu_search.h tabu_list.h local_search.h cheng_church.h teng_chan.h sorted_heuristic.h bicluster.h


tabu_search.o: tabu_search.cpp tabu_search.h bicluster.h tabu_list.h

tabu_list.o: tabu_list.cpp tabu_list.h bicluster.h

grasp.o: grasp.cpp grasp.h matrix.h bicluster.h local_search.h sorted_heuristic.h

local_search.o: local_search.cpp local_search.h bicluster.h

sorted_heuristic.o: sorted_heuristic.cpp sorted_heuristic.h runningstat.h bicluster.h matrix.h

teng_chan.o: teng_chan.cpp teng_chan.h bicluster.h matrix.h

cheng_church.o: cheng_church.cpp cheng_church.h bicluster.h

matrix.o: matrix.cpp matrix.h

bicluster.o: bicluster.cpp bicluster.h

readcsv.o: readcsv.cpp readcsv.h util.h

runningstat.o: runningstat.cpp runningstat.h

util.o:	util.h

.PHONY: clean
clean: 
	rm -f $(TARGET) *.o

.PHONY: all
all: clean $(TARGET)

