/*
 * Copyright (c) 2024, SkillerRaptor
 *
 * SPDX-License-Identifier: MIT
 */

#include "hcc/result.h"

const char *hcc_result_description(enum HccResult result)
{
    switch (result)
    {
    case HCC_RESULT_ERROR:
        return "unknown";
    case HCC_RESULT_BAD_PARAMETER:
        return "bad parameter";
    case HCC_RESULT_BAD_OPERATION:
        return "bad operation";
    case HCC_RESULT_NO_MEMORY:
        return "no memory";
    case HCC_RESULT_OK:
    default:
        return "none";
    }
}