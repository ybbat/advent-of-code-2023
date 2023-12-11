configure_file(example.txt example.txt COPYONLY)
configure_file(input.txt input.txt COPYONLY)

add_executable(day11a a.cpp)
add_executable(day11b b.cpp)