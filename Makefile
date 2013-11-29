CC       = gcc
CFLAGS   = -g -std=c99 -Wall -I$(SRCDIR)

LINKER   = gcc -o
LFLAGS   = -Wall

SRCDIR   = src
OBJDIR   = obj
BINDIR   = bin
TESTDIR  = tests

TARGET 	 = $(BINDIR)/arithExprInterpreter

SRC 	 = $(wildcard $(SRCDIR)/*.c)
OBJ 	 = $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

TESTSRC  = $(wildcard $(TESTDIR)/*.c)
TESTS 	 = $(TESTSRC:%.c=%.test)

.PHONY: test

all: $(TARGET) test

$(TARGET): $(BINDIR)/main.c $(OBJ)
	@$(LINKER) $@ $^ $(LFLAGS)
	@echo "Linking successfull"

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@$(CC) -o $@ -c $< $(CFLAGS)
	@echo "Compiled "$<" successfully"

test: $(TESTS)
	@echo
	@echo "Running now unit tests:"
	@sh ./tests/runtests.sh

$(TESTDIR)/%.test: $(TESTDIR)/%.c $(OBJ)
	@$(CC) -o $@ $^ $(CFLAGS)
	@echo "Compiled test "$<" successfully"

.PHONY: clean remove

clean:
	@rm -rf $(OBJDIR)/*.o
	@rm -rf $(TESTDIR)/*.test
	@rm -rf $(TESTDIR)/*.dSYM
	@echo "Cleanup complete!"

remove: clean
	@rm -rf $(TARGET)
	@echo "Removal complete!"