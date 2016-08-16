OBJS = $(patsubst %.cpp,%.o,$(wildcard *.cpp))
CC = g++
CFLAGS = -g -Wall -O2
LIBS = -lpthread -lm
all:begin main end
begin:
	@echo "----compile begin----"
	@echo $(OBJS)

main : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

end:
	rm *.o
	@echo "----compile finished----"

.PHONY: clean
clean :
	rm -rf main *.o

