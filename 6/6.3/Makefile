all: main libcalc.so
	@echo "Выполнить команду: export LD_LIBRARY_PATH=.:$$LD_LIBRARY_PATH"

main: main.c
	gcc -o main main.c -ldl

libcalc.so: calc.c calc.h
	gcc -fPIC -shared calc.c -o libcalc.so

clear:
	rm -f main libcalc.so calc.o
