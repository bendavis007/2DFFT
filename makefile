CFLAGS = -O 
CCFLAGS = -O 
FFLAGS = -O

clean:
	rm -f *.o *.a core 

.f:
	g77 $(FFLAGS) -o $* $*.f -lm
	rm -f *.o

.c:
	cc -o $* $*.c -lm 
	rm -f *.o

.cpp:  
	g++ $(CCFLAGS) -o $* $*.cpp FileClass.cpp FileParse.cpp -lm
	rm -f *.o

.d:
	cc -o $* $*.c -L/usr/local/etc/pgplot -lpgplot -lX11 -lm 

