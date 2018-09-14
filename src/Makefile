CXX     	= g++
CXXFLAGS  	= -Wall --std=c++11
OBJS    	= readcsv.o main.o util.o

TARGET	= proj

default: $(TARGET)
	@echo Done.

$(TARGET): $(OBJS) 
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@

main.o: main.cpp readcsv.h

readcsv.o: readcsv.cpp readcsv.h util.h

util.o:	util.h

.PHONY: clean
clean: 
	rm -f $(TARGET) *.o

.PHONY: all
all: clean $(TARGET)

