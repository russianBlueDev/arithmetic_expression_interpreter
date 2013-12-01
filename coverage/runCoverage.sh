#!/bin/sh

# This file should be located on coverage/ folder just under root
# as files generated by coverage will be in root directory

mv *.gcda *.gcno coverage/
lcov --capture --directory . --output-file coverage/coverage.info
# Remove files from std library or kernel from coverage
lcov --remove coverage/coverage.info "/usr*" -o coverage/coverage.info
genhtml coverage/coverage.info --output-directory coverage/