add_subdirectory(code)

if(BUILD_TEST)
    add_subdirectory(unitTests)
endif(BUILD_TEST)

add_subdirectory(public)