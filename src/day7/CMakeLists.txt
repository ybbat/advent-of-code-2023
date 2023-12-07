configure_file(example.txt example.txt COPYONLY)
configure_file(input.txt input.txt COPYONLY)

add_executable(day7a a.cpp)
add_executable(day7b b.cpp)