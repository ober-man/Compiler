COMP = g++
SOURCE = ./driver/driver.cpp ./nodes/nodes.cpp ./compiler/lex.yy.cc ./compiler/grammar.tab.cc main.cpp
OPTIONS = -std=c++2a
EXEC = comp

all:
	$(COMP) $(SOURCE) $(OPTIONS) -o $(EXEC)

clean:
	rm *.o $(EXEC)
