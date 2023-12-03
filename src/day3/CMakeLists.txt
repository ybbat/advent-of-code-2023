configure_file(example.txt example.txt COPYONLY)
configure_file(input.txt input.txt COPYONLY)

add_executable(day3a a.cpp)
add_executable(day3b b.cpp)