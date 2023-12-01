configure_file(aexample.txt aexample.txt COPYONLY)
configure_file(ainput.txt ainput.txt COPYONLY)

configure_file(bexample.txt bexample.txt COPYONLY)
configure_file(binput.txt binput.txt COPYONLY)

add_executable(day1a a.cpp)
add_executable(day1b b.cpp)