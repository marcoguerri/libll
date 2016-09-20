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


SOURCES := $(shell find . -path ./src/tests -prune -o -name "*.c" -print)
SOURCES_TESTS := $(shell find ./src/tests -name "*.c" -print)
OBJECTS := $(SOURCES:.c=.o)
OBJECTS_TESTS := $(SOURCES_TESTS:.c=.o)

CFLAGS = -Wall -O0 -fPIC -D_GNU_SOURCE -Isrc -Isrc/tests -g
LDFLAGS = -shared
LDFLAGS_TESTS = -Lbin
LDLIBS_TESTS = -lads

all: libads.so

libads.so: $(OBJECTS)
	@install -d bin -m 755
	$(CC) $(OBJECTS) -o bin/$@ $(LDLIBS) $(LDFLAGS) $(CFLAGS)

%.o: %.cc
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

tests: libads.so $(OBJECTS_TESTS)
	$(CC) $(OBJECTS_TESTS) -o bin/$@ $(LDFLAGS_TESTS) $(LDLIBS_TESTS) $(CFLAGS)

run_tests: tests
	@export LD_LIBRARY_PATH=bin && ./bin/tests

	
clean:
	rm -f $(OBJECTS)
	rm -f $(OBJECTS_TESTS)
	rm -f bin/*

.PHONY: clean
