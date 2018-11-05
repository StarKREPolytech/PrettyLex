cmake_minimum_required(VERSION 3.12)

project(lex C)

set(CMAKE_C_STANDARD 11)

include_directories(main)

include_directories(libs)

#lib4aio:
add_subdirectory(libs/lib4aio)

#Find lex:
FIND_PACKAGE(FLEX REQUIRED)

#Create variable:
set(flexout ../generated/lexer.c)

if (FLEX_FOUND)
    #Print message about Lex is detected!
    message(STATUS "Flex is exists!")
    #Create "flexout" variable for keeping generated C Lex files in the path:
    add_custom_command(
            OUTPUT ${flexout}
            #Execute lex:
            COMMAND ${FLEX_EXECUTABLE}
            #Put in the generated path:
            --outfile=${flexout}
            #From path:
            ../lex/lexer.l
            #Print pretty message about Lex file name:
            COMMENT "Generated lexer"
    )
endif ()

add_executable(
        lex
        #project:
        main/lexer.h
        main/main.c
        #generated lex file:
        generated/lexer.c
)

#link lib4aio:
target_link_libraries(lex lib4aio)