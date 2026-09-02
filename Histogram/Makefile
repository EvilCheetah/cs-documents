# run with 'make -i'
# Note: the large spaces are tabs, this is important
# Run GCOV, requires that we build the code
# All of these runs of ./ are a test case
# We want to cover 100% of prog through these tests

CC     = gcc
CFLAGS = -Wall -Wextra -fprofile-arcs -ftest-coverage -g
VG     = valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes

SRC  = prog.c
PROG = prog
TEST = tests
OUT  = out


run-tests-coverage: build
	mkdir -p $(OUT)
	
	@# PASS
	./$(PROG) $(TEST)/pass/empty.txt   	   $(OUT)/empty.txt
	./$(PROG) $(TEST)/pass/hello-world.txt $(OUT)/hello-world.txt
	./$(PROG) $(TEST)/pass/spec.txt        $(OUT)/spec.txt
	./$(PROG) $(TEST)/pass/special.txt     $(OUT)/special.txt
	
	@# FAIL
	-./$(PROG)
	-./$(PROG) $(TEST)/pass/spec.txt
	-./$(PROG) $(TEST)/pass/spec.txt           $(TEST)/pass/spec.txt $(OUT)/spec.txt
	-./$(PROG) $(TEST)/404_NOT_FOUND.txt       $(OUT)/fail.txt
	-./$(PROG) $(TEST)/pass/spec.txt           ./404_NOT_FOUND/spec.txt
	
	gcov $(SRC)

# Run Valgrind to find memory leaks, requires that we build the code
run-tests-leak: build
	mkdir -p $(OUT)
	
	@# PASS
	$(VG) ./$(PROG) $(TEST)/pass/empty.txt   	   $(OUT)/empty.txt
	$(VG) ./$(PROG) $(TEST)/pass/hello-world.txt $(OUT)/hello-world.txt
	$(VG) ./$(PROG) $(TEST)/pass/spec.txt        $(OUT)/spec.txt
	$(VG) ./$(PROG) $(TEST)/pass/special.txt     $(OUT)/special.txt
	
	@# FAIL
	$(VG) -./$(PROG)
	$(VG) -./$(PROG) $(TEST)/pass/spec.txt
	$(VG) -./$(PROG) $(TEST)/pass/spec.txt           $(TEST)/pass/spec.txt $(OUT)/spec.txt
	$(VG) -./$(PROG) $(TEST)/404_NOT_FOUND.txt       $(OUT)/fail.txt
	$(VG) -./$(PROG) $(TEST)/pass/spec.txt           ./404_NOT_FOUND/spec.txt

# Compile the code, requires that we clean up some files first.
# Add –lm if your code needs the math library.
build: clean
	$(CC) $(CFLAGS) $(SRC) -o $(PROG)

clean:
	rm -rf $(OUT)
	rm -f *~
	rm -f $(PROG)
	rm -f *.gcda *.gcno *.gcov
