COMP := g++

main.out:
	$(COMP) -o main.out ./parser.o ./lexer.o ./vm.o main.cpp

frontend:
	$(COMP) -c ./src/parser.cpp ./src/lexer.cpp

runtime:
	$(COMP) -c ./src/vm.cpp

run:
	build/main.out

clean:
	rm -rf build/ *.o *.out
