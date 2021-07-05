CXX			:= g++
CXX_FLAGS	:= -std=c++17 -Werror -Wall -Wextra -Wpedantic

WORK_DIR	:= src
TEST_DIR	:= tests

OUTPUT_BIN	:= calc
TEST_IN_P	:= input
TEST_OUT_P	:= output
TEST_EXP_P	:= expected

compile:
	$(CXX) $(CXX_FLAGS) -o $(OUTPUT_BIN) $(WORK_DIR)/*.cpp

execute:
	./$(OUTPUT_BIN)

clean:
	-rm -f $(OUTPUT_BIN)

run: clean compile execute

run_tests:
	for file in `ls $(TEST_DIR) | grep $(TEST_IN_P)`; do \
		./$(OUTPUT_BIN) \
		<$(TEST_DIR)/$$file >$(TEST_DIR)/$(TEST_OUT_P) `echo "$$file" | cut -c6-`; \
	done

	for file in `ls $(TEST_DIR) | grep $(TEST_IN_P)`; do \
		exp="$(TEST_DIR)/$(TEST_EXP_P)`echo "$$file" | cut -c6-`"; \
		out="$(TEST_DIR)/$(TEST_OUT_P)`echo "$$file" | cut -c6-`"; \
		tst="$(TEST_DIR)`echo "$$file" | cut -c6-`"; \
		echo "\n\n`echo $$tst`:\n\n`cat $(TEST_DIR)/$$file`\$(TEST_EXP_P):\n`cat $$exp` \noutput: \n`cat $$out`"; \
		if `echo `diff $$out $$exp``; then echo checker: OK; else echo checker: NOT OK; fi \
	done

cleanup_tests:
	-rm -f $(TEST_DIR)/$(TEST_OUT_P)*

test: compile run_tests cleanup_tests