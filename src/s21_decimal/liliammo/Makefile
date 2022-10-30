.PHONY: all clean
override CFLAGS += -std=c11 -Wall -Wextra -Ofast # -Werror
CC ?= gcc
RM=rm -rf
PROJECT=$(patsubst %.h,%,$(wildcard s21_*.h))

all: $(PROJECT).a

%.o: %.c
	$(CC) -c $(CFLAGS) $^

$(PROJECT).a: $(PROJECT).h $(PROJECT).a($(patsubst %.c,%.o,$(wildcard *.c)))
	ranlib $@

$(PROJECT).h: *.c
ifeq ($(shell uname -s), Darwin)
	sed -i '' '/generated/,$$d' $@
else
	sed -i '/generated/,$$d' $@
endif
	echo "//  generated_by_makefile" >> $@
	cat s21_*.c | grep -E "^\w+.+[)] [{]" | grep -v "main(" | sed 's/ {/;/' >> $@

clean:
	ls | grep -v 's21_[a-z_]*[.][c|h]\|Makefile' | xargs $(RM)
