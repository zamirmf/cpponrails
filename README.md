# Dependencies
The following setup has been used as part of the docker container provided:
 - Google Test (v. 1.8.1) - https://github.com/google/googletest
 - GNU G++/GCC (v. 9.1.0) - https://www.gnu.org/software/gcc
 - GNU Make  (v. 3.8.2) - https://www.gnu.org/software/make

# Docker
For those using docker, the following can be used to initialize and access the container:
 ```
 docker-compose up -d
 ```
To access the container:
```
docker exec -it cpp_on_rails_container /bin/bash
```

The docker version used is 18.09.3(for more info: https://docs.docker.com).

# Build and Run
The following rules are supported by the make file provided:
 ```
 ./app/make all #Generates the test binary (i.e., test) under the build directory
 ```
 ```
 ./app/make run_tests #Generates and runs the test binary (i.e., test)
 ```
 ```
 ./build/test --gtest_filter=<Test_Case>* #Runs only the test cases that match <Test_Case>
 ```
 ```
 ./app/make clean #Deletes all files under the build directory
 ```