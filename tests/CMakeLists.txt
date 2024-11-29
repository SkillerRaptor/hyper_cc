#-------------------------------------------------------------------------------------------
# Copyright (c) 2024, SkillerRaptor
#
# SPDX-License-Identifier: MIT
#-------------------------------------------------------------------------------------------
set(SOURCES
        src/lexer.cpp)

set(HEADERS
)

hyper_cc_define_executable(hcc_tests)
target_link_libraries(
        hcc_tests
        PRIVATE
        Catch2::Catch2WithMain
        hcc_core
        hcc_lexer)