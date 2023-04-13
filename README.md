# FS

## Overview

This is a C++ application to interact with files

## Usage

1. Create `zip` archive with given file:
    ```
    ./fs --zip <file path>
    ```
   Output file will be placed in the same directory as the original file and has the following name: `<original filename>.zip`.


2. Calculate `SHA-256` sum of given file:
    ```
    ./fs --hash <file path>
    ```
   Output file will be placed in the same directory as the original file and has the following name: `<original filename>.hash`. 


3. Count the number of rows in the given file:
    ```
    ./fs --lines <file path>
    ```

4. Run commands with path's existence checking (without this flag **the `std::terminate()` may be called** and no message will be displayed stating that the file doesn't exist):
    ```
    ./fs --check-path  <flags...>
    ``` 
   

5. Don't request root privileges on failure
   ```
    ./fs --no-root  <flags...>
   ``` 

If standard privileges are not sufficient to perform the action and `--no-root` flag is _not_ provided, **root privileges will be requested**.

If the path is specified incorrectly, **the `std::terminate()` may be called**. To avoid this use `--check-path` flag.

## Requirements

* `Linux` system
* `CMake 3.16` or higher
* `gcc 10`/`clang 10` or higher 
* `boost 1.65.1` or higher **with compiled binaries**
* `libzippp` library
* `OpenSSL` library

## Build

In project's root directory run following commands:

```shell
mkdir build
cd build
cmake ..
make
```

Run application:

```
./fs <flags...>
```