.PHONY: all test check clean
override CFLAGS += -std=c11 -Wall -Wextra -Ofast # -Werror
CC ?= gcc
RM=rm -rf
FNAME=$(patsubst %.h,%,$(wildcard s21_*.h))

all: $(FNAME).a

%.o: %.c
	$(CC) -c $(CFLAGS) $^

$(FNAME).a: $(FNAME).h $(FNAME).a($(patsubst %.c,%.o,$(wildcard *.c)))
	ranlib $@

s21_%.h: *.c
ifeq ($(shell uname -s), Darwin)
	sed -i '' '/generated/,$$d' $@
else
	sed -i '/generated/,$$d' $@
endif
	echo "//  generated_by_makefile" >> $@
	cat s21_*.c | grep -E "^\w+.*[)] [{]" | grep -v "main(" | sed 's/ {/;/' >> $@

clean:
	ls | grep -v 's21_[a-z_]*[.][c|h]\|Makefile' | xargs $(RM)

ECHO=echo
ifeq ($(shell uname -s), Darwin)
ECHO=echo -e
endif

check:
	@$(ECHO) "\033[0;32m"
#	cp ../../materials/linters/CPPLINT.cfg . && python3 ../../materials/linters/cpplint.py --extensions=c *.? liba/*.?
	-cpplint --extensions=c *.h *.c
	@$(ECHO) "\033[0;34m"
	cppcheck -q --enable=all --inconclusive --std=c11 --suppress=missingIncludeSystem .
	@$(ECHO) "\033[0;35m"
