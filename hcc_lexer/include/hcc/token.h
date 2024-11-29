/*
 * Copyright (c) 2024, SkillerRaptor
 *
 * SPDX-License-Identifier: MIT
 */

// NOTE: https://learn.microsoft.com/en-us/cpp/c-language/lexical-grammar?view=msvc-170

#ifndef HCC_TOKEN_H
#define HCC_TOKEN_H

#include <stdint.h>

#include <hcc/prerequisites.h>

HCC_EXTERN_C_BEGIN

enum HccTokenType
{
    HCC_TOKEN_TYPE_INVALID,

    // Constant
    HCC_TOKEN_TYPE_INTEGER_CONSTANT,

    // Punctuator
    // +
    HCC_TOKEN_TYPE_PLUS,
};

struct HccToken
{
    // TODO: Add source location
    enum HccTokenType type;
    union
    {
        uint64_t integer;
        // TODO: Add other values
    } data;
};

const char *hcc_token_type_description(enum HccTokenType type);

HCC_EXTERN_C_END

#endif // HCC_TOKEN_H