gcc -c test.c -o test.o -Wpedantic -Wall -Wextra -Werror -std=c89
gcc -fPIC -shared doubll2d.c -o liblist.so -Wpedantic -Wall -Wextra -Werror -std=c89
gcc test.o -o dynamiclist ./liblist.so -Wpedantic -Wall -Wextra -Werror -std=c89