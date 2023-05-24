
all: clean compile run

compile:
	@ gcc -o prog test_call_other_process.c -lm 
# -lm é usado para linkar a biblioteca math.h

run: clean compile
	@ ./prog

clean:
	@ rm -f *.o prog