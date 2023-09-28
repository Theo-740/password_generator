
default : passgen

passgen : main.c
	gcc main.c -o passgen

clear : 
	rm passgen