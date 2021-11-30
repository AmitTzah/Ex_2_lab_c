my_grep: main.o identify_and_parse_input.o match_pattern_to_line.o print_outputs.o regular_expressions.o
	gcc main.o identify_and_parse_input.o match_pattern_to_line.o print_outputs.o regular_expressions.o -o my_grep

main.o: main.c identify_and_parse_input.h match_pattern_to_line.h print_outputs.h
	gcc -c main.c

identify_and_parse_input.o: identify_and_parse_input.c identify_and_parse_input.h
	gcc -c identify_and_parse_input.c

match_pattern_to_line.o: match_pattern_to_line.c match_pattern_to_line.h identify_and_parse_input.h
	gcc -c  match_pattern_to_line.c

print_outputs.o: print_outputs.c print_outputs.h identify_and_parse_input.h
	gcc -c print_outputs.c

regular_expressions.o: regular_expressions.c regular_expressions.h 
	gcc -c regular_expressions.c

.PHONY: all clean test

all: my_grep

clean:
	-rm *.o my_grep 

test: all
	~nimrodav/grep_tests/run_all.sh
