CXX     	= g++
CXXFLAGS  	= -Wall -std=c++11
OBJS    	= cheng_church.o teng_chan.o matrix.o bicluster.o readcsv.o main.o util.o


TARGET	= proj

default: $(TARGET)
	@echo Done.

$(TARGET): $(OBJS) 
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@

main.o: main.cpp readcsv.h cheng_church.h teng_chan.h bicluster.h

teng_chan.o: teng_chan.cpp teng_chan.h bicluster.h matrix.h

cheng_church.o: cheng_church.cpp cheng_church.h bicluster.h

matrix.o: matrix.cpp matrix.h

bicluster.o: bicluster.cpp bicluster.h

readcsv.o: readcsv.cpp readcsv.h util.h

util.o:	util.h

.PHONY: clean
clean: 
	rm -f $(TARGET) *.o

.PHONY: all
all: clean $(TARGET)

