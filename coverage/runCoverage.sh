#!/bin/sh

# This file should be located on coverage/ folder just under root
# as files generated by coverage will be in root directory

# Warning output mostly redirected to /dev/null for convenience

mv *.gcda *.gcno coverage/
lcov --capture --directory . --output-file coverage/coverage.info 1>/dev/null 2>&1
# Remove files from std library or kernel from coverage
lcov --remove coverage/coverage.info "/usr*" -o coverage/coverage.info 1>/dev/null 2>&1
lcov --remove coverage/coverage.info "utils*" -o coverage/coverage.info 1>/dev/null 2>&1
genhtml coverage/coverage.info --output-directory coverage/
