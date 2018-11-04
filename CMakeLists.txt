cmake_minimum_required(VERSION 3.12)

project(lex C)

set(CMAKE_C_STANDARD 11)

#include_directories(${CMAKE_CURRENT_BINARY_DIR})

include_directories(main)

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
        #headers:
        main/myscanner.h
        #source:
        main/myscanner.c
        #generated lex file:
        generated/lexer.c
)

#Passing by Lex files and generate C files:
#Not the best idea because of lex uses global variables:

#if (FLEX_FOUND)
#    message(STATUS "flex is found")
#    #Create "flexout" variable for keeping generated C Lex files in the path:
#    set(flexout ../generated)
#    #Create "lexdir" variable for getting *.l Lex files in the path:
#    file(GLOB lexdir lex/*.l)
#    #Iterates in *.l files:
#    foreach (lexfile ${lexdir})
#        #Invoke Lex programm under each file:
#        get_filename_component(name ${lexfile} NAME)
#        message(STATUS "LEX: ${lexfile}")
#        message(STATUS "NAME: ${lexfile}")
#        add_custom_command(
#                OUTPUT ${flexout}
#                COMMAND ${FLEX_EXECUTABLE}
#                #Collect in the generated path:
#                --outfile=${flexout}/${name}
#                ${lexfile}
#                #Print pretty message about Lex file name:
#                COMMENT "Generate ${lexfile}"
#        )
#        string(".l" ".c" generatedFile ${lexfile})
#        add_executable(${generatedFile})
#    endforeach (lexfile ${lexdir})
#endif ()