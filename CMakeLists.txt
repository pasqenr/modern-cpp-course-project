cmake_minimum_required(VERSION 3.5)
project(simplelist CXX)

set(CMAKE_CXX_STANDARD 14)

# ------------------------------------------------------------------------------
### COMPILER FLAGS ###

include(CheckCXXCompilerFlag)

CHECK_CXX_COMPILER_FLAG("-std=c++14" COMPILER_SUPPORTS_CXX14)
if (COMPILER_SUPPORTS_CXX14)
    add_compile_options("-std=c++14")
else ()
    message(FATAL_ERROR "Compiler ${CMAKE_CXX_COMPILER} has no C++14 support.")
endif ()

if (${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
    add_compile_options("-Weverything")
    add_compile_options("-Wno-c++98-compat")
    add_compile_options("-Wno-c++98-compat-pedantic")
    add_compile_options("-Wno-padded")
    add_compile_options("-Wno-undefined-func-template")
    add_compile_options("-Wno-documentation-unknown-command")
    add_compile_options("-Wno-global-constructors")
    add_compile_options("-Wno-exit-time-destructors")
    add_compile_options("-Wno-sign-conversion")
    add_compile_options("-Wno-weak-vtables")
    add_compile_options("-Wno-weak-template-vtables")
    add_compile_options("-Wno-documentation")
    add_compile_options("-Werror")
elseif (CMAKE_COMPILER_IS_GNUCXX)
    add_compile_options("-Wall")
    add_compile_options("-Wextra")
    add_compile_options("-Wpedantic")
    add_compile_options("-O0")
    add_compile_options("-Werror")
endif ()

# ------------------------------------------------------------------------------
### BUILD TYPE ###

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_options("-O3")
    add_compile_options("-DNDEBUG")

elseif (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options("-Werror")
    add_compile_options("-Wall")
    add_compile_options("-Wextra")
    add_compile_options("-Wpedantic")
    add_compile_options("-O0")

    if (CMAKE_COMPILER_IS_GNUCXX)
        add_compile_options("-ggdb")
    elseif (CMAKE_CXX_COMPILER_ID EQUAL "Clang")
        add_compile_options("-ggdb")
    else ()
        add_compile_options("-g")
    endif ()

elseif (CMAKE_BUILD_TYPE STREQUAL "Coverage")
    if (CMAKE_COMPILER_IS_GNUCXX)
        set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "--coverage")
        add_compile_options("--coverage")
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        add_compile_options("-fprofile-instr-generate")
        add_compile_options("-fcoverage-mapping")
        set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS}
                "-fprofile-instr-generate -fcoverage-mapping")
    endif ()

elseif (CMAKE_BUILD_TYPE STREQUAL "SANITIZE" AND
        CMAKE_CXX_COMPILER_ID EQUAL "Clang")

    add_compile_options("-O1")
    add_compile_options("-g")
    add_compile_options("-fno-omit-frame-pointer")
    add_compile_options("-fno-optimize-sibling-calls")

    add_compile_options("-fsanitize=address")
    add_compile_options("-fsanitize=leak")
    add_compile_options("-fsanitize=memory")
    add_compile_options("-fsanitize-memory-track-origins")
    add_compile_options("-fsanitize=undefined")
    add_compile_options("-fsanitize=integer")
    add_compile_options("-fsanitize=nullability")

    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address")
endif ()

# ------------------------------------------------------------------------------
### CUSTOM TARGETS ###

add_custom_target(clean-all
        COMMAND rm -rf ${PROJECT_SOURCE_DIR}/bin/*
        COMMAND rm -rf ${PROJECT_SOURCE_DIR}/build/*
        COMMAND rm -rf ${PROJECT_SOURCE_DIR}/lib/libsimplelistlib.a
        COMMAND rm -rf ${PROJECT_SOURCE_DIR}/doc/*
        COMMAND rm -rf ${PROJECT_SOURCE_DIR}/infer-out/
        COMMAND rm -rf ${PROJECT_SOURCE_DIR}/scan-build-out/
        COMMAND rm -rf ${PROJECT_SOURCE_DIR}/compile_commands.json
        COMMAND rm -rf ${PROJECT_SOURCE_DIR}/coverage.info
        COMMAND rm -rf ${PROJECT_SOURCE_DIR}/Testing
        COMMAND rm -rf ${PROJECT_SOURCE_DIR}/cmake-build-debug
        COMMAND rm -rf ${PROJECT_SOURCE_DIR}/CMakeFiles
        COMMAND rm -rf ${PROJECT_SOURCE_DIR}/Makefile
        COMMAND rm -rf ${PROJECT_SOURCE_DIR}/CTestTestfile.cmake
        COMMAND rm -rf ${PROJECT_SOURCE_DIR}/install_manifest.txt
        COMMAND rm -rf ${PROJECT_SOURCE_DIR}/cmake_install.cmake
        COMMAND rm -rf ${PROJECT_SOURCE_DIR}/CMakeCache.txt
        COMMAND rm -rf ${PROJECT_SOURCE_DIR}/*.cbp
        COMMAND rm -rf ${PROJECT_SOURCE_DIR}/tidy-out.yaml
        COMMENT "Clean temporary and build files")

find_program(VALGRIND_FOUND valgrind)
if (VALGRIND_FOUND)
    add_custom_target(valgrind
            COMMAND valgrind --leak-check=full --show-leak-kinds=all
            --track-origins=yes
            ${PROJECT_SOURCE_DIR}/build/simplelist_test)
endif ()

find_program(CLOC_FOUND cloc)
if (CLOC_FOUND)
    add_custom_target(stats
            COMMAND cloc ${PROJECT_SOURCE_DIR}/src
            ${PROJECT_SOURCE_DIR}/include
            ${PROJECT_SOURCE_DIR}/test
            COMMENT "Code statistics")
endif ()

find_program(LYZARD_FOUND lizard)
if (LYZARD_FOUND)
    add_custom_target(cyclo
            COMMAND lizard ${PROJECT_SOURCE_DIR}/src/
            ${PROJECT_SOURCE_DIR}/include/
            COMMENT "Code Complexity")
endif ()

find_program(DOXYGEN_FOUND doxygen)
if (DOXYGEN_FOUND)
    add_custom_target(doc
            COMMAND doxygen ${PROJECT_SOURCE_DIR}/doxygen.cfg
            COMMENT "Code documentation")
endif ()

find_program(INFER_FOUND infer)
if (INFER_FOUND)
    add_custom_target(infer
            COMMAND make
            COMMAND infer run --compilation-database compile_commands.json
            COMMENT "Infer Static Analysis")
endif ()

find_program(CPPCHECK_FOUND cppcheck)
if (CPPCHECK_FOUND)
    add_custom_target(check
            COMMAND cppcheck --enable=all --std=c++14
            ${PROJECT_SOURCE_DIR}/include/*
            ${PROJECT_SOURCE_DIR}/include/impl/*
            ${PROJECT_SOURCE_DIR}/src/*
            COMMENT "Cppcheck Static Analysis")
endif ()

find_program(CLANG_FORMAT_FOUND clang-format)
if (CLANG_FORMAT_FOUND)
    file(GLOB_RECURSE FILES_TO_FORMAT
            ${PROJECT_SOURCE_DIR}/src/*.cpp
            ${PROJECT_SOURCE_DIR}/test/*.cpp
            ${PROJECT_SOURCE_DIR}/include/*.hpp)
    add_custom_target(format
            COMMAND clang-format -i ${FILES_TO_FORMAT}
            COMMENT "Clang-format style formatter")
endif ()

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    find_program(SCANBUILD_FOUND scan-build)
    if (SCANBUILD_FOUND)
        add_custom_target(scan
                COMMAND scan-build -o ${PROJECT_SOURCE_DIR}/scan-build-out/ make -j4
                COMMENT "scan-build Static Analysis")
    endif ()

    find_program(CLANGTIDY_FOUND clang-tidy)
    if (CLANGTIDY_FOUND)
        find_program(PYTHON3_FOUND clang-tidy)
        if (PYTHON3_FOUND)
            add_custom_target(tidy
                    COMMAND python3 ${PROJECT_SOURCE_DIR}/run-clang-tidy.py
                    -export-fixes=${PROJECT_SOURCE_DIR}/tidy-out.yaml
                    COMMENT "clang-tidy Linter")
        else ()
            add_custom_target(tidy
                    COMMAND python ${PROJECT_SOURCE_DIR}/run-clang-tidy.py
                    -export-fixes=${PROJECT_SOURCE_DIR}/tidy-out.yaml
                    COMMENT "clang-tidy Linter")
        endif ()
    endif ()
endif ()

# ------------------------------------------------------------------------------
### BUILD ###

SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)
enable_language(CXX)

include_directories(${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/lib)

# Add condition for test generation
add_executable(simplelist_test
        ${PROJECT_SOURCE_DIR}/test/Test.cpp)

# Add file one by one to enable full intellisense
add_library(simplelistlib
        include/Node.hpp include/SentinelNode.hpp include/List.hpp include/OrderedList.hpp include/UnorderedList.hpp
        include/impl/List.i.hpp include/impl/Node.i.hpp include/impl/OrderedList.i.hpp
        include/impl/SentinelNode.i.hpp include/impl/UnorderedList.i.hpp)

set_target_properties(simplelistlib PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(simplelist_test simplelistlib)

install(TARGETS simplelist_test RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin/
        ARCHIVE DESTINATION ${PROJECT_SOURCE_DIR}/)


# ------------------------------------------------------------------------------
### TESTS ###

enable_testing()

option(ENABLE_UNIT_TESTS "Enable unit tests" ON)

ADD_TEST(NAME NodeTest1
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/build
        COMMAND ./simplelist_test [node_ctor])

ADD_TEST(NAME NodeTest2
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/build
        COMMAND ./simplelist_test [node_op])

ADD_TEST(NAME NodeTest3
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/build
        COMMAND ./simplelist_test [node_value])

ADD_TEST(NAME NodeTest4
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/build
        COMMAND ./simplelist_test [node_next])

ADD_TEST(NAME NodeTest5
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/build
        COMMAND ./simplelist_test [node_prev])

ADD_TEST(NAME NodeTest6
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/build
        COMMAND ./simplelist_test [append_next])

ADD_TEST(NAME NodeTest7
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/build
        COMMAND ./simplelist_test [append_prev])

ADD_TEST(NAME UnorderedListTest1
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/build
        COMMAND ./simplelist_test [ul_first])

ADD_TEST(NAME UnorderedListTest2
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/build
        COMMAND ./simplelist_test [ul_empty])

ADD_TEST(NAME UnorderedListTest3
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/build
        COMMAND ./simplelist_test [ul_add_back])

ADD_TEST(NAME UnorderedListTest4
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/build
        COMMAND ./simplelist_test [ul_add_front])

ADD_TEST(NAME UnorderedListTest5
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/build
        COMMAND ./simplelist_test [ul_remove_back])

ADD_TEST(NAME UnorderedListTest6
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/build
        COMMAND ./simplelist_test [ul_remove_front])

ADD_TEST(NAME UnorderedListTest7
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/build
        COMMAND ./simplelist_test [ul_remove])

ADD_TEST(NAME UnorderedListTest8
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/build
        COMMAND ./simplelist_test [ul_create_from_array])

ADD_TEST(NAME ListTest1
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/build
        COMMAND ./simplelist_test [l_apply])

ADD_TEST(NAME OrderedListTest1
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/build
        COMMAND ./simplelist_test [ol_add])

ADD_TEST(NAME OrderedListTest2
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/build
        COMMAND ./simplelist_test [ol_remove_value])

ADD_TEST(NAME OrderedListTest3
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/build
        COMMAND ./simplelist_test [ol_remove_front])

find_program(VALGRIND_FOUND valgrind)
if (VALGRIND_FOUND)
    ADD_TEST(NAME ValgrindTest1
            WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/build
            COMMAND valgrind --leak-check=full --show-leak-kinds=all
            --track-origins=yes
            ./simplelist_test [node_ctor])

    ADD_TEST(NAME ValgrindTest2
            WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/build
            COMMAND valgrind --leak-check=full --show-leak-kinds=all
            --track-origins=yes
            ./simplelist_test [node_ctor])

    ADD_TEST(NAME ValgrindTest3
            WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/build
            COMMAND valgrind --leak-check=full --show-leak-kinds=all
            --track-origins=yes
            ./simplelist_test [node_op])

    ADD_TEST(NAME ValgrindTest4
            WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/build
            COMMAND valgrind --leak-check=full --show-leak-kinds=all
            --track-origins=yes
            ./simplelist_test [node_value])

    ADD_TEST(NAME ValgrindTest5
            WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/build
            COMMAND valgrind --leak-check=full --show-leak-kinds=all
            --track-origins=yes
            ./simplelist_test [node_next])

    ADD_TEST(NAME ValgrindTest6
            WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/build
            COMMAND valgrind --leak-check=full --show-leak-kinds=all
            --track-origins=yes
            ./simplelist_test [node_prev])

    ADD_TEST(NAME ValgrindTest7
            WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/build
            COMMAND valgrind --leak-check=full --show-leak-kinds=all
            --track-origins=yes
            ./simplelist_test [append_next])

    ADD_TEST(NAME ValgrindTest8
            WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/build
            COMMAND valgrind --leak-check=full --show-leak-kinds=all
            --track-origins=yes
            ./simplelist_test [append_prev])

    ADD_TEST(NAME ValgrindTest9
            WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/build
            COMMAND valgrind --leak-check=full --show-leak-kinds=all
            --track-origins=yes
            ./simplelist_test [ul_first])

    ADD_TEST(NAME ValgrindTest10
            WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/build
            COMMAND valgrind --leak-check=full --show-leak-kinds=all
            --track-origins=yes
            ./simplelist_test [ul_empty])

    ADD_TEST(NAME ValgrindTest11
            WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/build
            COMMAND valgrind --leak-check=full --show-leak-kinds=all
            --track-origins=yes
            ./simplelist_test [ul_add_back])

    ADD_TEST(NAME ValgrindTest12
            WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/build
            COMMAND valgrind --leak-check=full --show-leak-kinds=all
            --track-origins=yes
            ./simplelist_test [ul_add_front])

    ADD_TEST(NAME ValgrindTest13
            WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/build
            COMMAND valgrind --leak-check=full --show-leak-kinds=all
            --track-origins=yes
            ./simplelist_test [ul_remove_back])

    ADD_TEST(NAME ValgrindTest14
            WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/build
            COMMAND valgrind --leak-check=full --show-leak-kinds=all
            --track-origins=yes
            ./simplelist_test [ul_remove_front])

    ADD_TEST(NAME ValgrindTest15
            WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/build
            COMMAND valgrind --leak-check=full --show-leak-kinds=all
            --track-origins=yes
            ./simplelist_test [ul_remove])

    ADD_TEST(NAME ValgrindTest16
            WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/build
            COMMAND valgrind --leak-check=full --show-leak-kinds=all
            --track-origins=yes
            ./simplelist_test [ul_create_from_array])

    ADD_TEST(NAME ValgrindTest17
            WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/build
            COMMAND valgrind --leak-check=full --show-leak-kinds=all
            --track-origins=yes
            ./simplelist_test [l_apply])

    ADD_TEST(NAME ValgrindTest18
            WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/build
            COMMAND valgrind --leak-check=full --show-leak-kinds=all
            --track-origins=yes
            ./simplelist_test [ol_add])

    ADD_TEST(NAME ValgrindTest19
            WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/build
            COMMAND valgrind --leak-check=full --show-leak-kinds=all
            --track-origins=yes
            ./simplelist_test [ol_remove_value])

    ADD_TEST(NAME ValgrindTest20
            WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/build
            COMMAND valgrind --leak-check=full --show-leak-kinds=all
            --track-origins=yes
            ./simplelist_test [ol_remove_front])
endif ()
