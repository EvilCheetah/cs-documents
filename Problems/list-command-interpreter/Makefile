# run with 'make -i'
# Note: the large spaces are tabs, this is important
# Run GCOV, requires that we build the code
# All of these runs of ./prog are a test case
# We want to cover 100% of prog through these tests

CXX      = g++
CXXFLAGS = -std=c++17 -pedantic -Wall -Wextra -fprofile-arcs -ftest-coverage -g
VG       = valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes

SRCS = prog.cpp bounded-list.cpp command.cpp
PROG = prog
OBJS = $(SRCS:.cpp=.o)

TEST_DIR = tests
OUT_DIR  = out

run-tests-coverage: build
	mkdir -p $(OUT_DIR)
	
	@# PASS
	./$(PROG) $(TEST_DIR)/pass/bounded.txt        $(OUT_DIR)/bounded.txt
	./$(PROG) $(TEST_DIR)/pass/example-1.spec.txt $(OUT_DIR)/example-1.spec.txt
	./$(PROG) $(TEST_DIR)/pass/example-2.spec.txt $(OUT_DIR)/example-2.spec.txt
	./$(PROG) $(TEST_DIR)/pass/unbounded.txt      $(OUT_DIR)/unbounded.txt
	
	@# FAIL
	-./prog
	-./$(PROG) $(TEST_DIR)/pass/example-1.spec.txt      $(TEST_DIR)/pass/example-1.spec.txt $(OUT_DIR)/example-1.spec.txt
	-./$(PROG) $(TEST_DIR)/404_NOT_FOUND.txt            $(OUT_DIR)/fail.txt
	-./$(PROG) $(TEST_DIR)/pass/example-1.spec.txt      ./404_NOT_FOUND/example-1.spec.txt
	-./$(PROG) $(TEST_DIR)/fail/blank-line.txt          $(OUT_DIR)/blank-line.txt
	-./$(PROG) $(TEST_DIR)/fail/extra-token.txt         $(OUT_DIR)/extra-token.txt
	-./$(PROG) $(TEST_DIR)/fail/insert-missing-char.txt $(OUT_DIR)/insert-missing-char.txt
	-./$(PROG) $(TEST_DIR)/fail/insert-without-side.txt $(OUT_DIR)/insert-without-side.txt
	-./$(PROG) $(TEST_DIR)/fail/invalid-command.txt     $(OUT_DIR)/invalid-command.txt
	-./$(PROG) $(TEST_DIR)/fail/late-spec.txt           $(OUT_DIR)/late-spec.txt
	-./$(PROG) $(TEST_DIR)/fail/no-spec.txt             $(OUT_DIR)/no-spec.txt
	-./$(PROG) $(TEST_DIR)/fail/remove-without-side.txt $(OUT_DIR)/remove-without-side.txt
	-./$(PROG) $(TEST_DIR)/fail/spec-not-integer.txt    $(OUT_DIR)/spec-not-integer.txt
	-./$(PROG) $(TEST_DIR)/fail/spec-with-side.txt      $(OUT_DIR)/spec-with-side.txt
	
	gcov -r $(SRCS)

# Run Valgrind to find memory leaks, requires that we build the code
run-tests-leak: build
	mkdir -p $(OUT_DIR)
	
	@# PASS
	$(VG) ./$(PROG) $(TEST_DIR)/pass/bounded.txt        $(OUT_DIR)/bounded.txt
	$(VG) ./$(PROG) $(TEST_DIR)/pass/example-1.spec.txt $(OUT_DIR)/example-1.spec.txt
	$(VG) ./$(PROG) $(TEST_DIR)/pass/example-2.spec.txt $(OUT_DIR)/example-2.spec.txt
	$(VG) ./$(PROG) $(TEST_DIR)/pass/unbounded.txt      $(OUT_DIR)/unbounded.txt

	@# FAIL
	-$(VG) ./$(PROG)
	-$(VG) ./$(PROG) $(TEST_DIR)/pass/example-1.spec.txt      $(TEST_DIR)/pass/example-1.spec.txt $(OUT_DIR)/example-1.spec.txt
	-$(VG) ./$(PROG) $(TEST_DIR)/404_NOT_FOUND.txt            $(OUT_DIR)/fail.txt
	-$(VG) ./$(PROG) $(TEST_DIR)/pass/example-1.spec.txt      ./404_NOT_FOUND/example-1.spec.txt
	-$(VG) ./$(PROG) $(TEST_DIR)/fail/blank-line.txt          $(OUT_DIR)/blank-line.txt
	-$(VG) ./$(PROG) $(TEST_DIR)/fail/extra-token.txt         $(OUT_DIR)/extra-token.txt
	-$(VG) ./$(PROG) $(TEST_DIR)/fail/insert-missing-char.txt $(OUT_DIR)/insert-missing-char.txt
	-$(VG) ./$(PROG) $(TEST_DIR)/fail/insert-without-side.txt $(OUT_DIR)/insert-without-side.txt
	-$(VG) ./$(PROG) $(TEST_DIR)/fail/invalid-command.txt     $(OUT_DIR)/invalid-command.txt
	-$(VG) ./$(PROG) $(TEST_DIR)/fail/late-spec.txt           $(OUT_DIR)/late-spec.txt
	-$(VG) ./$(PROG) $(TEST_DIR)/fail/no-spec.txt             $(OUT_DIR)/no-spec.txt
	-$(VG) ./$(PROG) $(TEST_DIR)/fail/remove-without-side.txt $(OUT_DIR)/remove-without-side.txt
	-$(VG) ./$(PROG) $(TEST_DIR)/fail/spec-not-integer.txt    $(OUT_DIR)/spec-not-integer.txt
	-$(VG) ./$(PROG) $(TEST_DIR)/fail/spec-with-side.txt      $(OUT_DIR)/spec-with-side.txt

# Compile the code, requires that we clean up some files first.
# Add –lm if your code needs the math library.
build: clean
	$(MAKE) $(PROG)
clean:
	rm -f *~
	rm -f $(PROG) $(OBJS)
	rm -f *.gcda *.gcno *.gcov
	rm -rf $(OUT_DIR)

$(PROG): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(PROG)
$(PROG).o: prog.cpp command.h bounded-list.h
	$(CXX) $(CXXFLAGS) -c prog.cpp -o $@
command.o: command.h command.cpp bounded-list.h
	$(CXX) $(CXXFLAGS) -c command.cpp -o $@
bounded-list.o: bounded-list.h bounded-list.cpp
	$(CXX) $(CXXFLAGS) -c bounded-list.cpp -o $@

