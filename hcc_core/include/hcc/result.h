/*
 * Copyright (c) 2024, SkillerRaptor
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef HCC_RESULT_H
#define HCC_RESULT_H

#include <hcc/prerequisites.h>

HCC_EXTERN_C_BEGIN

enum HccResult
{
    HCC_RESULT_OK,
    HCC_RESULT_ERROR,
    HCC_RESULT_BAD_PARAMETER,
    HCC_RESULT_BAD_OPERATION,
    HCC_RESULT_NO_MEMORY,
};

const char *hcc_result_description(enum HccResult result);

HCC_EXTERN_C_END

#endif // HCC_RESULT_H