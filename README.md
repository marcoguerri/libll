### libll
libll is an implementation of a doubly linked-list. The library is thread safe as long as data structure instances are private to each
thread.

### Usage
Clone the library:
```
git clone https://github.com/marcoguerri/libll.git
```

Example of statically linked build:

```C
#include "ll.h"


int
print(void *ptr, char *str)
{
    return sprintf(str,"%d ", *((uint8_t*)ptr));
}

int
main() {
    int v[] = {20, 30};
    ll_t* list_int = NULL;
    list_int = ll_init(&v[0], sizeof(int));
    list_int = ll_insert(list_int, &v[1], ll_len(list_int));
    printf("%s\n", ll_print(list_int, print));
}
```

Compile and run with:
```
$ gcc main.c -L lib -l ll -I$(pwd)/include/libll -o ll_test
$ LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:$(pwd)/lib ./ll_test 
20 30
```
### License
`libll` is licensed under the MIT License (MIT). See LICENSE for the full text.
