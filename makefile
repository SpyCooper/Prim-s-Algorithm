.PHONY: all, compile, run

all: compile
run: compile execute

compile:
	g++ prims.cc -o a.out

execute:
	./a.out

clean:
	rm a.out