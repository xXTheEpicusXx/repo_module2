all:
	gcc main.c contacts.c -o contacts -L. -liblist

test_1:
	gcc -DTEST_1=1 main.c contacts.c tests.c -o test_1 -L. -llist

test_2:
	gcc -DTEST_2=1 main.c contacts.c tests.c -o test_2 -L. -llist

test_3:
	gcc -DTEST_3=1 main.c contacts.c tests.c -o test_3 -L. -llist

test_4:
	gcc -DTEST_4=1 main.c contacts.c tests.c -o test_4 -L. -llist

test_5:
	gcc -DTEST_5=1 main.c contacts.c tests.c -o test_5 -L. -llist

dll:
	gcc -fPIC double_linked_list.c -c
	gcc -shared  double_linked_list.o -o liblist.so
#"Выполнить команду: export LD_LIBRARY_PATH=.:$$LD_LIBRARY_PATH"
clear_tests:
	rm -rf test_*
