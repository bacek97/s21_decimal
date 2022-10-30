.PHONY: all libs check clean test
CC = gcc
RM = rm -rf
FOLDER_TST = `grep -o "tests/.*/" .vscode/launch.json`
PROJECT = s21_decimal

all: $(PROJECT).a

$(PROJECT).a: liliammo
	cp $(PROJECT)/$</$(PROJECT).a ./

%:
	cd s21_*/$@ && CFLAGS="$(CFLAGS)" CC=$(CC) $(MAKE);

test: $(PROJECT).a
	cd $(FOLDER_TST) && CK_VERBOSITY=verbose CFLAGS="$(CFLAGS)" CC=$(CC) $(MAKE)

check:
	cd $(FOLDER_TST) && $(MAKE) check

gcov_report: clean
	CFLAGS="-g --coverage -fprofile-arcs -ftest-coverage" $(MAKE) $(PROJECT).a test
	lcov -o lcov.genhtml -c -d . --no-external
	genhtml -o report lcov.genhtml

clean:
	ls | grep -v '.vscode\|tests\|s21_[a-z_]*\|Makefile' | xargs $(RM)
	ls | grep 's21_[a-z_]*[.].*' | xargs $(RM)
	for folders in $(wildcard s21_*/*/) ; do \
		cd $$folders && $(MAKE) clean && cd -; \
	done
	cd $(FOLDER_TST) && $(MAKE) clean
