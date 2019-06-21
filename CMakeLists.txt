cmake_minimum_required(VERSION 3.10)
project(SeuYacc)

set(CMAKE_CXX_STANDARD 11)

add_executable(SeuYacc SEU_Yacc.cpp helper.h LR1ToLALR.h First.h CFGToLRDFA.h Parse_Yacc.h Parsing.h CodeGeneration.h)