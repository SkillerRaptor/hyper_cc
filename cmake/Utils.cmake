#-------------------------------------------------------------------------------------------
# Copyright (c) 2024, SkillerRaptor
#
# SPDX-License-Identifier: MIT
#-------------------------------------------------------------------------------------------

function(hyper_cc_group_source SOURCE)
    foreach (item IN ITEMS ${SOURCE})
        get_filename_component(src_path "${item}" PATH)
        string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "" group_path "${src_path}")
        string(REPLACE ".." "\\" group_path "${group_path}")
        source_group("${group_path}" FILES "${item}")
    endforeach ()
endfunction()

function(hyper_cc_define_executable target)
    hyper_cc_group_source(${SOURCES})
    if (HEADERS)
        hyper_cc_group_source(${HEADERS})
    endif ()

    add_executable(${target} ${SOURCES} ${HEADERS})
    target_link_libraries(${target} PRIVATE ProjectOptions ProjectWarnings)
    target_include_directories(${target} PUBLIC include)

    if (WIN32)
        target_compile_definitions(
                ${target}
                PUBLIC
                -D_CRT_SECURE_NO_WARNINGS
                -D_CRT_NONSTDC_NO_DEPRECATE)
    endif ()
endfunction()

function(hyper_cc_define_library target)
    hyper_cc_group_source(${SOURCES})
    if (HEADERS)
        hyper_cc_group_source(${HEADERS})
    endif ()

    add_library(${target} STATIC ${SOURCES} ${HEADERS})
    target_link_libraries(${target} PRIVATE ProjectOptions ProjectWarnings)
    target_include_directories(${target} PUBLIC include)

    if (WIN32)
        target_compile_definitions(
                ${target}
                PUBLIC
                -D_CRT_SECURE_NO_WARNINGS
                -D_CRT_NONSTDC_NO_DEPRECATE)
    endif ()
endfunction()
