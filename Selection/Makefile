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
	./$(PROG) $(TEST)/pass/negatives.txt $(OUT)/negatives.txt
	./$(PROG) $(TEST)/pass/reverse.txt   $(OUT)/reverse.txt
	./$(PROG) $(TEST)/pass/single.txt    $(OUT)/single.txt
	./$(PROG) $(TEST)/pass/sorted.txt    $(OUT)/sorted.txt
	./$(PROG) $(TEST)/pass/spec.txt      $(OUT)/spec.txt
	
	@# FAIL
	-./$(PROG)
	-./$(PROG) $(TEST)/pass/spec.txt
	-./$(PROG) $(TEST)/pass/spec.txt           $(TEST)/pass/spec.txt $(OUT)/spec.txt
	-./$(PROG) $(TEST)/fail/bad_count.txt      $(OUT)/fail.txt
	-./$(PROG) $(TEST)/fail/empty.txt          $(OUT)/fail.txt
	-./$(PROG) $(TEST)/fail/negative_count.txt $(OUT)/fail.txt
	-./$(PROG) $(TEST)/fail/truncated.txt      $(OUT)/fail.txt
	-./$(PROG) $(TEST)/404_NOT_FOUND.txt       $(OUT)/fail.txt
	-./$(PROG) $(TEST)/pass/spec.txt           ./404_NOT_FOUND/spec.txt
	
	gcov $(SRC)

# Run Valgrind to find memory leaks, requires that we build the code
run-tests-leak: build
	mkdir -p $(OUT)
	
	@# PASS
	$(VG) ./$(PROG) $(TEST)/pass/negatives.txt $(OUT)/negatives.txt
	$(VG) ./$(PROG) $(TEST)/pass/reverse.txt   $(OUT)/reverse.txt
	$(VG) ./$(PROG) $(TEST)/pass/single.txt    $(OUT)/single.txt
	$(VG) ./$(PROG) $(TEST)/pass/sorted.txt    $(OUT)/sorted.txt
	$(VG) ./$(PROG) $(TEST)/pass/spec.txt      $(OUT)/spec.txt
	
	@# FAIL
	-$(VG) ./$(PROG)
	-$(VG) ./$(PROG) $(TEST)/pass/spec.txt
	-$(VG) ./$(PROG) $(TEST)/pass/spec.txt           $(TEST)/pass/spec.txt $(OUT)/spec.txt
	-$(VG) ./$(PROG) $(TEST)/fail/bad_count.txt      $(OUT)/fail.txt
	-$(VG) ./$(PROG) $(TEST)/fail/empty.txt          $(OUT)/fail.txt
	-$(VG) ./$(PROG) $(TEST)/fail/negative_count.txt $(OUT)/fail.txt
	-$(VG) ./$(PROG) $(TEST)/fail/truncated.txt      $(OUT)/fail.txt
	-$(VG) ./$(PROG) $(TEST)/404_NOT_FOUND.txt       $(OUT)/fail.txt
	-$(VG) ./$(PROG) $(TEST)/pass/spec.txt           ./404_NOT_FOUND/spec.txt

# Compile the code, requires that we clean up some files first.
# Add –lm if your code needs the math library.
build: clean
	$(CC) $(CFLAGS) $(SRC) -o $(PROG)

clean:
	rm -rf $(OUT)
	rm -f *~
	rm -f $(PROG)
	rm -f *.gcda *.gcno *.gcov

