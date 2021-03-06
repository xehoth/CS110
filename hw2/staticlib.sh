gcc -c doubll2d.c -o doubll2d.o -Wpedantic -Wall -Wextra -Werror -std=c89
gcc -c test.c -o test.o -Wpedantic -Wall -Wextra -Werror -std=c89
ar rcs liblist.a doubll2d.o
gcc test.o -o staticlist -L . -llist -Wpedantic -Wall -Wextra -Werror -std=c89