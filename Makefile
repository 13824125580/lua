all:
	#gcc add.c -g -I/usr/local/include  -llua -lm -ldl -o add 
	#gcc add_hook.c -g -I/usr/local/include -llua -lm -ldl -o add_hook
	gcc avr.c -g -I/usr/local/include -llua -lm -ldl -o avr
