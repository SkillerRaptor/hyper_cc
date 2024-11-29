#-------------------------------------------------------------------------------------------
# Copyright (c) 2024, SkillerRaptor
#
# SPDX-License-Identifier: MIT
#-------------------------------------------------------------------------------------------
set(SOURCES
        src/hcc/lexer.c)

set(HEADERS
        include/hcc/lexer.h
        include/hcc/token.h)

hyper_cc_define_library(hcc_lexer)
target_link_libraries(hcc_lexer PRIVATE hcc_core)