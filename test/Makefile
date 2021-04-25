# The MIT License (MIT)
# Copyright (C) 2016 Marco Guerri
#
# Permission is hereby granted, free of charge, to any person obtaining a copy of 
# this software and associated documentation files (the "Software"), to deal in 
# the Software without restriction, including without limitation the rights to use, 
# copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the 
# Software, and to permit persons to whom the Software is furnished to do so, subject
# to the following conditions:

# The above copyright notice and this permission notice shall be included in all 
# copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
# INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
# PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT 
# HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION 
# OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
# SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


SOURCES := list_test.c test.c
OBJECTS := $(SOURCES:.c=.o)

CFLAGS = -Wall -O0  -D_GNU_SOURCE -L../lib -I../include
LDLIBS = -lll

ifneq ("$(wildcard /usr/bin/valgrind)", "")
	TEST_LEAK=1
else
	TEST_LEAK=0
endif

all: run_tests leak

%.o: %.cc
	$(CC) $(CFLAGS) -c $< -o $@

tests: $(OBJECTS)
	$(MAKE) -C ../src
	$(CC) $(OBJECTS) -o $@ $(LDLIBS) $(CFLAGS)

run_tests: tests
	@LD_LIBRARY_PATH=../lib ./tests

leak: tests
	@test $(TEST_LEAK) -eq 1 && LD_LIBRARY_PATH=../lib valgrind --track-origins=yes --leak-check=yes ./tests || echo "please install valgrind to test for leaks"

clean:
	rm -f $(OBJECTS)
	rm -f tests

.PHONY: clean leak
