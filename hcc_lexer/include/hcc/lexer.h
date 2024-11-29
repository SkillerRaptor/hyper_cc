/*
 * Copyright (c) 2024, SkillerRaptor
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef HCC_LEXER_H
#define HCC_LEXER_H

#include <stdbool.h>
#include <stddef.h>

#include <hcc/prerequisites.h>
#include <hcc/result.h>

#include "hcc/token.h"

HCC_EXTERN_C_BEGIN

struct HccLexer
{
    const char *code;
    size_t code_size;

    uint32_t start_index;
    uint32_t current_index;

    uint32_t line;
};

enum HccResult hcc_lexer_init(struct HccLexer *lexer, const char *code);
void hcc_lexer_free(struct HccLexer *lexer);

enum HccResult hcc_lexer_next_token(struct HccLexer *lexer, struct HccToken *token);

bool hcc_lexer_is_at_end(struct HccLexer *lexer);

HCC_EXTERN_C_END

#endif // HCC_LEXER_H