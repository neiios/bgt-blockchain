BINARY=bin
# can be a list
CODEDIRS=. bgt-hash
INCDIRS=. bgt-hash

CC=g++
OPT=-O3 -march=native
# OPT=-O0
DEPFLAGS=-MP -MD
CFLAGS=-Wall -Wextra -std=gnu++2a -g $(foreach D,$(INCDIRS),-I$(D)) $(OPT) $(DEPFLAGS)

CFILES=$(foreach D,$(CODEDIRS),$(wildcard $(D)/*.cpp))
OBJECTS=$(patsubst %.cpp,%.o,$(CFILES))
DEPFILES=$(patsubst %.cpp,%.d,$(CFILES))

all: $(BINARY)

$(BINARY): $(OBJECTS)
	$(CC) -o $@ $^ -fopenmp -I/usr/local/include -L/usr/local/lib -lbitcoin -lboost_chrono -lboost_date_time -lboost_filesystem -lboost_locale -lboost_program_options -lboost_regex -lboost_system -lboost_thread -lpthread -lrt -ldl -lsecp256k1

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $< -fopenmp -I/usr/local/include -L/usr/local/lib -lbitcoin -lboost_chrono -lboost_date_time -lboost_filesystem -lboost_locale -lboost_program_options -lboost_regex -lboost_system -lboost_thread -lpthread -lrt -ldl -lsecp256k1

clean:
	rm -rf $(BINARY) $(OBJECTS) $(DEPFILES)

run:
	./bin

-include $(DEPFILES)
.PHONY: all clean run
