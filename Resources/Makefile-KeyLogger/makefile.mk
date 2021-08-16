all: KeyLogger.exe clean

KeyLogger.exe : KeyLogger.o functions.o
	gcc KeyLogger.o functions.o -o KeyLogger.exe

KeyLogger.o : KeyLogger.c functions.c functions.h
	gcc -c KeyLogger.c

functions.o : functions.c functions.o
	gcc -c functions.c

clean :
	del *.o 