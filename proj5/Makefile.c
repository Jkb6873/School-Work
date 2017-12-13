########################################
##
## Makefile
## LINUX compilation
##
##############################################

#FLAGS
C++FLAG = -g -std=c++11 -Wall

#Math Library
MATH_LIBS = -lm
EXEC_DIR=.

#Rule for .cpp files
# .SUFFIXES : .cpp.o

.cpp.o:
	g++ $(C++FLAG) $(INCLUDES)  -c $< -o $@

#Including
INCLUDES=  -I.


LIBS_ALL =  -L/usr/lib -L/usr/local/lib $(MATH_LIBS)


#ZEROTH PROGRAM
ALL_OBJ0=Matrix.o
PROGRAM_0=Matrix
$(PROGRAM_0): $(ALL_OBJ0)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(ALL_OBJ0) $(INCLUDES) $(LIBS_ALL)

all:
		make $(PROGRAM_0)

clean:
	(rm -f *.o; rm -f $(PROGRAM_0)
(:
