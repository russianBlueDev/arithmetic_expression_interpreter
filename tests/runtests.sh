#!/bin/sh

if test -f tests/tests.log
then
    rm tests/tests.log
fi

for i in tests/*.test
do
    if test -f $i
    then
        if valgrind --leak-check=yes --error-exitcode=1 ./$i 2>> tests/tests.log
        then
            echo $i PASS
            rm tests/tests.log
        else
            echo "ERROR in test $i: here's tests/tests.log"
            echo "------"
            more tests/tests.log
            exit 1
        fi
    fi
done

echo ""