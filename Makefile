CC       = gcc-4.2
CFLAGS   = -g -std=c99 -Wall -I$(SRCDIR) --coverage

LINKER   = gcc-4.2 -o
LFLAGS   = -Wall --coverage

SRCDIR   = src
OBJDIR   = obj
BINDIR   = bin
TESTDIR  = tests
COVDIR	 = coverage

TARGET 	 = $(BINDIR)/arithExprInterpreter.out

SRC 	 = $(wildcard $(SRCDIR)/*.c)
OBJ 	 = $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

TESTSRC  = $(wildcard $(TESTDIR)/*.c)
TESTS 	 = $(TESTSRC:%.c=%.test)

.PHONY: test

all: $(TARGET) test

$(TARGET): $(BINDIR)/main.c $(OBJ)
	@$(LINKER) $@ $^ $(CFLAGS) $(LFLAGS)
	@echo "Linking successfull"

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@$(CC) -o $@ -c $< $(CFLAGS)
	@echo "Compiled "$<" successfully"

test: $(TESTS)
	@echo
	@echo "Running now unit tests:"
	@sh ./tests/runtests.sh
	@echo "Generating code coverage"
	@sh ./coverage/runCoverage.sh

$(TESTDIR)/%.test: $(TESTDIR)/%.c $(OBJ)
	@$(CC) -o $@ $^ $(CFLAGS)
	@echo "Compiled test "$<" successfully"

.PHONY: clean remove

clean:
	@rm -rf $(OBJDIR)/*.o
	@rm -rf $(TESTDIR)/*.test
	@rm -rf $(TESTDIR)/*.dSYM
	@rm -rf $(OBJDIR)/*.g*
	@mv $(COVDIR)/runCoverage.sh .
	@rm -rf $(COVDIR)/*
	@mv runCoverage.sh $(COVDIR)/
	@rm -f $(SRCDIR)/*.html
	@rm -f $(TESTDIR)/*.html
	@echo "Cleanup complete!"

remove: clean
	@rm -rf $(TARGET)
	@rm -rf $(BINDIR)/*.dSYM
	@echo "Removal complete!"