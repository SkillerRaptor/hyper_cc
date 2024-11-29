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

enum HccTokenKind
{
    HCC_TOKEN_KIND_INVALID,

    // Constant
    HCC_TOKEN_KIND_INTEGER_CONSTANT,

    // Punctuator
    // +
    HCC_TOKEN_KIND_PLUS,
};

struct HccToken
{
    // TODO: Add source location
    enum HccTokenKind kind;
    union
    {
        uint64_t integer;
        // TODO: Add other values
    };
};

HCC_EXTERN_C_END

#endif // HCC_TOKEN_H