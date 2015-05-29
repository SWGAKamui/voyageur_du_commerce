add_library(graph Graph.c)

add_executable(TestGraph Graph.c TestGraph.c)

install(TARGETS TestGraph DESTINATION bin)
