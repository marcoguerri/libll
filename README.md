### libads
libads is an implementation of a doubly linked-list. The library is thread safe as long as data structure instances are private to each
thread.

### Usage
Clone the library:
```
git clone https://github.com/marcoguerri/libads.git
```

Example of statically linked build:

```C
#include "list.h"


int
print_integer_payload(void *ptr, char *str)
{
    return sprintf(str,"%d ", *((uint8_t*)ptr));
}

int
main() {
    int a = 20;
    int b = 30;
    char *list_repr;
    ads_list_t* list_int = NULL;
    list_int = ads_list_init(&a, sizeof(int));
    list_int = ads_list_insert(list_int, &b, ads_list_len(list_int));
    list_repr = ads_list_print(list_int, print_integer_payload);
    printf("List representation: %s\n", list_repr);
    ads_list_destroy((void*)list_int);
}
```

Compile with:
```
$ gcc main.c -L lib -l ads -I$(pwd)/include/libads -o libads_test
$ LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:$(pwd)/lib ./libads_test 
List representation: 20 30
```

For dynamic linkage, see how [tcpinfo](https://github.com/marcoguerri/tcpinfo) uses this library.



### License
`libads` is licensed under the MIT License (MIT).

```
Copyright (C) 2016 Marco Guerri <marco.guerri.dev@fastmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy of 
this software and associated documentation files (the "Software"), to deal in 
the Software without restriction, including without limitation the rights to use, 
copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the 
Software, and to permit persons to whom the Software is furnished to do so, subject
to the following conditions:

The above copyright notice and this permission notice shall be included in all 
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT 
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION 
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
```
