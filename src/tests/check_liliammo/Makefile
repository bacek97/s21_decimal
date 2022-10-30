CHECK_H  = `pkg-config --static --libs check`
PROJECT = ../../s21_*/*/*

all: s21_checkh.c
	$(CC) $(CFLAGS) $< $(PROJECT).a $(CHECK_H) -o a.exe
	rm $<
	./a.exe

s21_checkh.c: s21_checkmk.*
	checkmk $^ > $@

clean:
	ls | grep -v 's21_[a-z_]*[.]ts\|Makefile' | xargs rm -rf





check:
ifeq ($(shell uname -s), Darwin)
	@echo -e "\033[0;32m"
	# -cp ../../../materials/linters/CPPLINT.cfg ../../
	# -python3 ../../../materials/linters/cpplint.py --extensions=h,c --recursive ../../
	@echo -e "\033[0;34m"
	cppcheck -q --enable=all --inconclusive --std=c11 --suppress=missingIncludeSystem ../../ --suppress=unusedFunction
	bash -c "grep -e 'leaks for' <(CK_FORK=no leaks -q --atExit -- ./a.exe)"

else
	@echo -e "\033[0;32m"
	-cpplint --extensions=h,c --recursive ../../
	@echo -e "\033[0;34m"
	cppcheck -q --enable=all --inconclusive --std=c11 --suppress=missingIncludeSystem ../../ --suppress=unusedFunction
	@CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=RESULT_VALGRIND.txt ./a.exe
	@tail -n 1 RESULT_VALGRIND.txt
endif
