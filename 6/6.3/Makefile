all:
	gcc main.c calc.c -o calc

calclib:
	gcc -fPIC calc.c -c
	gcc -shared  calc.o -o libcalc.so
	gcc -o main main.c -ldl
#"Выполнить команду: export LD_LIBRARY_PATH=.:$$LD_LIBRARY_PATH"

clear:
	rm calc
