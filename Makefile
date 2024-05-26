main: main.c
	if [ -f main ]; then rm main; fi; gcc -o main main.c; ./main
