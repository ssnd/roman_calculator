compile:
	g++ -std=c++17 -Werror -Wall -Wextra -Wpedantic -o calc src/*.cpp
launch:
	./calc
run: compile launch

run_tests:
	for file in `ls tests | grep input`; do \
		./calc \
		<tests/$$file >tests/output`echo "$$file" | cut -c6-`; \
	done

	for file in `ls tests | grep input`; do \
		exp="tests/expected`echo "$$file" | cut -c6-`"; \
		out="tests/output`echo "$$file" | cut -c6-`"; \
		tst="test`echo "$$file" | cut -c6-`"; \
		echo "\n\n`echo $$tst`:\n\n`cat tests/$$file`\nexpected:\n`cat $$exp` \noutput: \n`cat $$out`"; \
		if `echo `diff $$out $$exp``; then echo checker: OK; else echo checker: NOT OK; fi \
	done
cleanup_tests:
	rm -f tests/output*

test: compile run_tests cleanup_tests