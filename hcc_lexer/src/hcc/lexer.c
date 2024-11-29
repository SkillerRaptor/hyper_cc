/*
 * Copyright (c) 2024, SkillerRaptor
 *
 * SPDX-License-Identifier: MIT
 */

#include "hcc/lexer.h"

#include <ctype.h>
#include <stdlib.h>
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

    lexer->code = strdup(code);
    lexer->code_size = strlen(lexer->code);

    lexer->start_index = 0;
    lexer->current_index = 0;

    lexer->line = 1;

    return HCC_RESULT_OK;
}

void hcc_lexer_free(struct HccLexer *lexer)
{
    if (lexer == NULL)
    {
        return;
    }

    free((void *) lexer->code);
}

static bool hcc_lexer_is_at_end(struct HccLexer *lexer)
{
    return lexer->current_index >= lexer->code_size;
}

static enum HccResult hcc_lexer_advance(struct HccLexer *lexer, char *character)
{
    if (hcc_lexer_is_at_end(lexer))
    {
        return HCC_RESULT_ERROR;
    }

    *character = lexer->code[lexer->current_index];
    lexer->current_index += 1;

    return HCC_RESULT_OK;
}

static char hcc_lexer_peek(struct HccLexer *lexer)
{
    if (hcc_lexer_is_at_end(lexer))
    {
        return '\0';
    }

    return lexer->code[lexer->current_index];
}

static enum HccResult hcc_lexer_lex_number(struct HccLexer *lexer, struct HccToken *token)
{
    enum HccResult result = HCC_RESULT_OK;

    char character = hcc_lexer_peek(lexer);
    while (isdigit(character))
    {
        if ((result = hcc_lexer_advance(lexer, &character)) != HCC_RESULT_OK)
        {
            return result;
        }

        character = hcc_lexer_peek(lexer);
    }

    // TODO: Handle floating point

    token->kind = HCC_TOKEN_KIND_INTEGER_CONSTANT;
    token->integer = strtoll(lexer->code + lexer->start_index, NULL, 10);

    return HCC_RESULT_OK;
}

static enum HccResult hcc_lexer_next_token(struct HccLexer *lexer, struct HccToken *token)
{
    if (lexer == NULL)
    {
        return HCC_RESULT_BAD_PARAMETER;
    }

    if (token == NULL)
    {
        return HCC_RESULT_BAD_PARAMETER;
    }

    enum HccResult result = HCC_RESULT_OK;

    lexer->start_index = lexer->current_index;
    token->kind = HCC_TOKEN_KIND_INVALID;

    while (token->kind == HCC_TOKEN_KIND_INVALID)
    {
        char character = '\0';
        if ((result = hcc_lexer_advance(lexer, &character)) != HCC_RESULT_OK)
        {
            return result;
        }

        switch (character)
        {
        case '+':
            token->kind = HCC_TOKEN_KIND_PLUS;
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

enum HccResult hcc_lexer_lex_tokens(struct HccLexer *lexer, struct HccVector *tokens)
{
    if (lexer == NULL)
    {
        return HCC_RESULT_BAD_PARAMETER;
    }

    if (tokens == NULL)
    {
        return HCC_RESULT_BAD_PARAMETER;
    }

    enum HccResult result = HCC_RESULT_OK;

    while (!hcc_lexer_is_at_end(lexer))
    {
        struct HccToken token = { 0 };
        if ((result = hcc_lexer_next_token(lexer, &token)) != HCC_RESULT_OK)
        {
            return result;
        }

        if ((result = hcc_vector_push_back(tokens, &token)) != HCC_RESULT_OK)
        {
            return result;
        }
    }

    return HCC_RESULT_OK;
}