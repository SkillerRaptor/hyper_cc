#-------------------------------------------------------------------------------------------
# Copyright (c) 2024, SkillerRaptor
#
# SPDX-License-Identifier: MIT
#-------------------------------------------------------------------------------------------
set(SOURCES
        src/main.c)

set(HEADERS
)

hyper_cc_define_executable(hcc)
target_link_libraries(
        hcc
        PRIVATE
        hcc_core
        hcc_lexer)