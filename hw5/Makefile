#*********************************************************************
# Homework 5
# CS 110: Computer Architecture, Spring 2021
# ShanghaiTech University
#
# * Last Modified: 03/30/2021
#*********************************************************************

# Specify the compiler and flags that will be used.
CC=gcc
OPTIMIZES=-Ofast -march=native -march=native -mtune=native -flto -fuse-linker-plugin \
					# -finline -fgcse -fgcse-lm -fipa-sra -ftree-pre -ftree-vrp -fpeephole2 \
					# -fsched-spec -funroll-loops -falign-jumps -falign-loops -falign-labels -fdevirtualize -fcaller-saves -fcrossjumping  \
					# -fthread-jumps -funroll-loops -flto -freorder-blocks -fschedule-insns -finline-functions -ftree-tail-merge \
					# -fschedule-insns2 -fstrict-aliasing -fstrict-overflow -falign-functions -fcse-skip-blocks -fcse-follow-jumps -fsched-interblock -fpartial-inlining -fno-stack-protector -freorder-functions -findirect-inlining -fhoist-adjacent-loads -frerun-cse-after-loop -ftree-switch-conversion -foptimize-sibling-calls -funsafe-loop-optimizations -fdelete-null-pointer-checks
CFLAGS=-Wpedantic -Wall -Wextra -Werror $(OPTIMIZES)

# Simplify the target list below.

SHA256_HEADER=hash_functions/sha256.h
BLOCKCHAIN_HEADER=blockchain.h hash_function.h bool.h

SHA256_IMPL=hash_functions/sha256.c
BLOCKCHAIN_IMPL=blockchain.c hash_function.c

SHA256_TEST=hash_functions/sha256_test.c
BLOCKCHAIN_TEST=test.c

SHA256_TARGET=test-sha256.out
BLOCKCHAIN_TARGET=blockchain.out

SUBMISSION_IMPL=Makefile blockchain.c
SUBMISSION_TARGET=hw5.tar
cores = $(shell cat /proc/cpuinfo | grep "model name" | uniq | grep "2690" | wc -L | tr -cd "[0-9]")

ifneq (${cores}, 0)
	DEFS = -DTHREAD_NUMS=4
else
	DEFS = -DTHREAD_NUMS=20
endif
# Target for the blockchain implementation that will test your implementation.
# Trigger this target by `make` or `make blockchain.out`.
$(BLOCKCHAIN_TARGET): Makefile $(SHA256_HEADER) $(BLOCKCHAIN_HEADER) $(SHA256_IMPL) $(BLOCKCHAIN_IMPL) $(BLOCKCHAIN_TEST)
	@echo "${cores}"
	@echo ${DEFS}
	# ${CC} ${CFLAGS} $(BLOCKCHAIN_IMPL) $(SHA256_IMPL) $(BLOCKCHAIN_TEST) -o $(BLOCKCHAIN_TARGET) -lpthread ${DEFS} -fprofile-generate && ./$(BLOCKCHAIN_TARGET) 24
	${CC} ${CFLAGS} $(BLOCKCHAIN_IMPL) $(SHA256_IMPL) $(BLOCKCHAIN_TEST) -o $(BLOCKCHAIN_TARGET) -lpthread ${DEFS} # -fprofile-use -fprofile-correction

# Target for testing if the SHA256 implementation works on your computer.
# Trigger this target by `make test-sha256.out`.
$(SHA256_TARGET): Makefile $(SHA256_TEST) $(SHA256_IMPL) $(SHA256_HEADER)
	${CC} ${CFLAGS} $(SHA256_IMPL) $(SHA256_TEST) -o $(SHA256_TARGET)

# Target for creating the tarball for submission.
# Trigger this target by `make submission`.
.PHONY: submission
submission:
	tar -cvpf $(SUBMISSION_TARGET) $(SUBMISSION_IMPL)
	
# Target for cleanup your workspace - deleting all files created by your compiler.
# Trigger this target by `make clean`.
.PHONY: clean
clean:
	rm -rf $(BLOCKCHAIN_TARGET) $(SHA256_TARGET) $(SUBMISSION_TARGET) *.dSYM *.gcda

