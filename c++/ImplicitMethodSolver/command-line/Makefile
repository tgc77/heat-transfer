CC = g++
CFLAGS  = -O3 -Wall -std=c++14
MAIN = heat-transfer-solver.bin
SRCS = EqHeatImplicitMethod.cpp Main.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(MAIN)

$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(MAIN)

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean: 
	$(RM) $(MAIN) *.o *~