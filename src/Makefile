all: cipher

cipher: cipher.o
	gcc -Wall -Wextra -Werror -o ../build/cipher ../build/cipher.o

cipher.o:
	gcc -Wall -Wextra -Werror -c -o ../build/cipher.o cipher.c

clean:
	rm -rf *.o ../build/*

rebuild: clean all
