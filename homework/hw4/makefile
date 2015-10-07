OBJS = idq_c.o idq_i.o customer.o event.o item.o main.o
CC = g++
DEBUG = 
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

main : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o main

idq_i.o : idq_i.h idq_i.cpp
	$(CC) $(CFLAGS) idq_i.cpp

idq_c.o : idq_c.h idq_c.cpp
	$(CC) $(CFLAGS) idq_c.cpp
	
item.o : item.h idq_i.h item.cpp 
	$(CC) $(CFLAGS) item.cpp
	
customer.o : customer.h idq_c.h customer.cpp
	$(CC) $(CFLAGS) customer.cpp
	
event.o : event.h event.cpp
	$(CC) $(CFLAGS) event.cpp
	
main.o : idq_c.h idq_i.h event.h item.h customer.h main.cpp 
	$(CC) $(CFLAGS) main.cpp

clean:
	rm -f *.o main.exe