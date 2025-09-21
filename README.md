# Solving Euler problems
[Project Eurler archive](https://projecteuler.net/archives)

## Build and run tests
Run the script `./build.sh problem4`

## Dependencies
### cmocka
`apt install libcmocka0 libcmocka-dev`

https://stackoverflow.com/questions/59817576/how-to-run-c-unit-testcases-using-cmocka-framework
https://www.samlewis.me/2016/09/embedded-unit-testing-with-cmocka/
https://stackoverflow.com/questions/29945791/undefined-reference-to-cmocka-run-group-tests-when-running-sample-cmocka-te

## Benchmark
`apt install hyperfine`

E.g.
`hyperfine --warmup 2 --runs 5 --shell=none ./main`

## Unity unit test framework
Added as submodule: `git submodule add https://github.com/ThrowTheSwitch/Unity.git unity`