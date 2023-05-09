COMP = g++ `llvm-config --cflags`
SOURCE = ./driver/driver.cpp ./codegen/codegen.cpp ./nodes/nodes.cpp \
	 ./compiler/lex.yy.cc ./compiler/grammar.tab.cc main.cpp
OPTIONS = -std=c++2a `llvm-config --ldflags --libs all --system-libs`
EXEC = comp

all:
	$(COMP) $(SOURCE) $(OPTIONS) -o $(EXEC)

clean:
	rm *.o $(EXEC)
