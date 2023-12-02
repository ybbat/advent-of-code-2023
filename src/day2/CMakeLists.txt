configure_file(example.txt example.txt COPYONLY)
configure_file(input.txt input.txt COPYONLY)

add_executable(day2a a.cpp)
add_executable(day2b b.cpp)