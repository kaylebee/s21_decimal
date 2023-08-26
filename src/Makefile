CC = gcc
FLAGS = -g 
# -Wall -Werror -Wextra
INC_DIR = -L. -I.
CHECK_LIB = -lcheck
OS:=$(shell uname -s)
CCOV = -lgcov --coverage

LIB_HEADER = s21_decimal.h
LIB = s21_decimal.a
LIB_DIR = lib/
OBJ_DIR = obj/
COV_DIR = coverage_info/
TEST_DIR = tests/
LIB_OBJ_DIR = $(OBJ_DIR)$(LIB_DIR)
COV_OBJ_DIR = $(COV_DIR)$(OBJ_DIR)

ifeq ($(OS), Linux)
	CHECK_LIB += -lrt -lpthread -lm -lsubunit
endif

## Make array of all object files for library
LIB_SRCS = $(addprefix $(LIB_DIR),arithmetic_conditions.c \
								extended_decimal_additional_arithmetic.c \
								extended_decimal_arithmetic.c \
								extended_decimal_assignment.c \
								extended_decimal_comparison.c \
								extended_decimal_round.c \
								extended_decimal.c \
								s21_arithm_operators.c \
								s21_comparison.c \
								s21_converters.c \
								s21_other_functions.c \
								s21_common.c)

## Make array of all test files
TEST_SRCS = $(addprefix $(TEST_DIR)coverage_test/,s21_tests.c \
												  s21_arithmetic_tests.c \
												  s21_comparison_tests.c \
												  s21_other_functions_tests.c \
												  s21_converters_tests.c)
												  
LIB_OBJS = $(patsubst %.c, $(OBJ_DIR)%.o, $(LIB_SRCS))
COV_OBJS = $(patsubst %.c, $(COV_OBJ_DIR)%.o, $(LIB_SRCS))

TEST_EXEC = test
COV_EXEC = $(COV_DIR)test_cov
COV_INFO = $(COV_DIR)s21_decimal.info
COV_REPORT = $(COV_DIR)/lib/index.html

vpath %.c $(LIB_DIR)

all: clean test gcov_report

test: $(LIB) $(TEST_SRCS)
	$(CC) $(FLAGS) $(INC_DIR) $(TEST_SRCS) $(LIB) $(CHECK_LIB) -o $(TEST_EXEC)

extended_test: $(LIB)
	g++ $(FLAGS) $(INC_DIR) $(TEST_DIR)cpp_part/*.cpp $(LIB) -o cpp_part
	mcs -out:cs_part $(TEST_DIR)/cs_part/*
	./cpp_part
	mono ./cs_part

gcov_report: $(LIB) $(TEST_SRCS) $(COV_OBJS)
	$(CC) $(FLAGS) $(INC_DIR) $(CCOV) $(LIB) $^ $(CHECK_LIB) -o $(COV_EXEC)
	@-./$(COV_EXEC)
	@lcov -q -c -d $(COV_DIR) -o $(COV_INFO) --exclude "$(TEST_DIR)*"
	@genhtml -q $(COV_INFO) -o $(COV_DIR)
	@open $(COV_REPORT)
	@rm -rf *.gc*

style:
	clang-format -n $(LIB_HEADER) lib/* tests/coverage_test/* tests/cpp_part/*

leaks: test
	valgrind ./test

$(LIB): $(LIB_OBJS)
	ar rc $@ $^
	ranlib $@

$(LIB_OBJ_DIR)%.o: %.c $(LIB_HEADER)
	@mkdir -p $(LIB_OBJ_DIR)
	$(CC) $(FLAGS) $(INC_DIR) -c $< -o $@

$(COV_OBJ_DIR)%.o: %.c $(LIB_HEADER)
	@mkdir -p $(COV_OBJ_DIR)$(LIB_DIR)
	@$(CC) $(FLAGS) $(INC_DIR) $(CCOV) -c $< -o $@


clean:
	rm -rf $(OBJ_DIR) \
		   $(LIB) \
		   $(TEST_EXEC) \
		   $(TEST_EXEC).dSYM \
		   test.log  \
		   $(COV_DIR) \
		   *.gc* \
		   cpp_part \
		   cs_part \
		   data

rebuild: clean all
