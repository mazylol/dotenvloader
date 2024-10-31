# dotenvloader
A super simple .env loader for C++ projects

## Example
```cpp
#include <iostream>
#include "dotenvloader.h"

int main() {
    dotenvloader::load();
    
    std::cout << "Hello, " << std::getenv("USER") << "!\n";
    return 0;
}
```

## Example .env
```
USER=world
# This is a comment
   # This is also a comment   (whitespace is trimmed from both sides)
NAME=dotenvloader # This comment will be added to the value, don't do this
```


## Installation
Use CPM.cmake or FetchContent to add this repository to your cmake project. Or just rip the files if you really want to. There are two and no external dependencies.