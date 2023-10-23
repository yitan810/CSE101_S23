#*************************************************************************************
# Daria Tan, ytan87 
# 2023 Winter CSE101 PA#8
# Makefile
# make/make WordFrequency	makes WordFrequency executable
# make Order				makes Order exuecutable	
# make Dictionary Test 		makes DictionaryTest executable
# make clean				removes all binaries
#*************************************************************************************
CC = g++
CFLAGS = -std=c++17 -Wall
Targets = DictionaryTest Order WordFrequency
OBJECT = Dictionary.o
COMPILE = $(CC) $(CFLAGS) -c
LINK = $(CC) $(CFLAGS) -o

WordFrequency: WordFrequency.o $(OBJECT)
	$(LINK) $@ $^

Order: Order.o $(OBJECT)
	$(LINK) $@ $^

DictionaryTest: DictionaryTest.o $(OBJECT)
	$(LINK) $@ $^

%.o: %.cpp
	$(COMPILE) $< 

clean:
	rm -rf $(Targets) *.o *.d
