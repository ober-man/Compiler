LEXER = lexer.l
GRAMMAR = grammar.y

all: flex bison

flex:
	flex $(LEXER)

bison:
	bison $(GRAMMAR) -d
