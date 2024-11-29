/*
 * Copyright (c) 2024, SkillerRaptor
 *
 * SPDX-License-Identifier: MIT
 */

#include "hcc/lexer.h"

#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

enum HccResult hcc_lexer_init(struct HccLexer *lexer, const char *code)
{
    if (lexer == NULL)
    {
        return HCC_RESULT_BAD_PARAMETER;
    }

    if (code == NULL)
    {
        return HCC_RESULT_BAD_PARAMETER;
    }

    lexer->code = code;
    lexer->code_size = strlen(code);

    lexer->start_index = 0;
    lexer->current_index = 0;

    lexer->line = 1;

    return HCC_RESULT_OK;
}

enum HccResult hcc_lexer_advance(struct HccLexer *lexer, char *character)
{
    if (hcc_lexer_is_at_end(lexer))
    {
        return HCC_RESULT_ERROR;
    }

    *character = lexer->code[lexer->current_index];
    lexer->current_index += 1;

    return HCC_RESULT_OK;
}

void hcc_lexer_peek(struct HccLexer *lexer, char *character)
{
    if (hcc_lexer_is_at_end(lexer))
    {
        *character = '\0';
        return;
    }

    *character = lexer->code[lexer->current_index];
}

enum HccResult hcc_lexer_lex_number(struct HccLexer *lexer, struct HccToken *token)
{
    enum HccResult result = HCC_RESULT_OK;

    char character = '\0';
    hcc_lexer_peek(lexer, &character);

    while (isdigit(character))
    {
        if ((result = hcc_lexer_advance(lexer, &character)) != HCC_RESULT_OK)
        {
            return result;
        }

        hcc_lexer_peek(lexer, &character);
    }

    // TODO: Handle floating point

    token->type = HCC_TOKEN_TYPE_INTEGER_CONSTANT;
    token->data.integer = strtoll(lexer->code + lexer->start_index, NULL, 10);

    return HCC_RESULT_OK;
}

enum HccResult hcc_lexer_next_token(struct HccLexer *lexer, struct HccToken *token)
{
    enum HccResult result = HCC_RESULT_OK;

    if (lexer == NULL)
    {
        return HCC_RESULT_BAD_PARAMETER;
    }

    if (token == NULL)
    {
        return HCC_RESULT_BAD_PARAMETER;
    }

    lexer->start_index = lexer->current_index;
    token->type = HCC_TOKEN_TYPE_INVALID;

    while (token->type == HCC_TOKEN_TYPE_INVALID)
    {
        char character = '\0';
        if ((result = hcc_lexer_advance(lexer, &character)) != HCC_RESULT_OK)
        {
            return result;
        }

        switch (character)
        {
        case '+':
            token->type = HCC_TOKEN_TYPE_PLUS;
            break;
        case ' ':
        case '\t':
        case '\r':
        case '\f':
            break;
        case '\n':
            lexer->line += 1;
            break;
        default:
            if (isdigit(character))
            {
                if ((result = hcc_lexer_lex_number(lexer, token)) != HCC_RESULT_OK)
                {
                    return result;
                }

                break;
            }

            // TODO: Add diagnostics
            return HCC_RESULT_ERROR;
        }
    }

    return HCC_RESULT_OK;
}

bool hcc_lexer_is_at_end(struct HccLexer *lexer)
{
    return lexer->current_index >= lexer->code_size;
}