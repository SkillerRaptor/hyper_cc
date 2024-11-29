/*
 * Copyright (c) 2024, SkillerRaptor
 *
 * SPDX-License-Identifier: MIT
 */

#include "hcc/token.h"

const char *hcc_token_type_description(enum HccTokenType type)
{
    switch (type)
    {
    case HCC_TOKEN_TYPE_INTEGER_CONSTANT:
        return "integer constant";
    case HCC_TOKEN_TYPE_PLUS:
        return "plus";
    case HCC_TOKEN_TYPE_INVALID:
    default:
        return "unknown";
    }
}