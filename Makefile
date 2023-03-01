a.out: main.cc map.h actors.h linked_list.h combat.h
	g++ -g -Og main.cc -lcurl -lncurses

clean:
	rm -rf a.out core *.o
