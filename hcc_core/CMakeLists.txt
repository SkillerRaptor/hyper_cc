#-------------------------------------------------------------------------------------------
# Copyright (c) 2024, SkillerRaptor
#
# SPDX-License-Identifier: MIT
#-------------------------------------------------------------------------------------------
set(SOURCES
        src/hcc/result.c)

set(HEADERS
        include/hcc/prerequisites.h
        include/hcc/result.h)

hyper_cc_define_library(hcc_core)