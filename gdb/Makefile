.DEFAULT_GOAL := all
PROGRAMS := step until inspect break trace seg1 seg2 leak

.PHONY: all
all : | programs
	$(MAKE) $(PROGRAMS)

programs :
	mkdir -p $@

break : source/break.c source/break2.c
	gcc -g3 $^ -o programs/$@

% : source/%.c
	gcc -g3 $< -o programs/$@

.PHONY: clean
clean :
	rm -rf programs
