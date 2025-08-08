mask:
	gcc -DMASK=1 main.c mychmod.c -lm -o mask

mystat:
	gcc -DSTAT=1 main.c mychmod.c -o mystat

mychmod:
	gcc -DCHMOD=1 main.c mychmod.c -o mychmod

clear:
	rm -rf mask
	rm -rf mystat
	rm -rf mychmod
