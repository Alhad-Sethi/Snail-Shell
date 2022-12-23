test: main ls cat date rm mkdir
	./main
	rm main ls cat date rm mkdir
main:main.c ls.c cat.c date.c rm.c mkdir.c
	gcc main.c -o main
	gcc ls.c -o ls
	gcc cat.c -o cat
	gcc date.c -o date
	gcc rm.c -o rm
	gcc mkdir.c -o mkdir
