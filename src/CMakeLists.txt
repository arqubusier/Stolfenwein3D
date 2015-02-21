project(src)
# add_executable(Lesson0 src/main.cpp)
target_link_libraries(src ${SDL2_LIBRARY})
install(TARGETS src RUNTIME DESTINATION ${BIN_DIR})
