edit : main.o inactivemousetest.o


main.o : main.c
	gcc main.c -o screensaver -lglfw -lGL
inactivemousetest.o : inactivemousetest.c
	gcc inactivemousetest.c -o main -lX11
clean :
	rm screensaver main
