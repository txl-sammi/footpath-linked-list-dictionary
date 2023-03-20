dict1: driver.o data.o list.o array.o
	gcc -o dict1 driver.o data.o list.o array.o

dict2: driver.o data.o list.o array.o
	gcc -o dict2 driver.o data.o list.o array.o

driver.o: driver.c data.o list.o array.o
	gcc -c driver.c

data.o: data.c data.h
	gcc -c data.c

list.o: list.c list.h
	gcc -c list.c

array.o: data.o array.c array.h
	gcc -c array.c

clean: 
	rm -f *.o
