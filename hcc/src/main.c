/*
 * Copyright (c) 2024, SkillerRaptor
 *
 * SPDX-License-Identifier: MIT
 */

#include <stdio.h>

#include <hcc/lexer.h>
#include <hcc/vector.h>

int main(void)
{
    enum HccResult result = HCC_RESULT_OK;

    const char *code = "1 + 2";

    struct HccLexer lexer = { 0 };
    if ((result = hcc_lexer_init(&lexer, code)) != HCC_RESULT_OK)
    {
        fprintf(stderr, "failed to initialize lexer: %s\n", hcc_result_description(result));
        return -1;
    }

    struct HccVector tokens = { 0 };
    if ((result = hcc_vector_init(&tokens, sizeof(struct HccToken))) != HCC_RESULT_OK)
    {
        fprintf(stderr, "failed to initialize vector: %s\n", hcc_result_description(result));
        return -1;
    }

    if ((result = hcc_lex_tokens(&lexer, &tokens)) != HCC_RESULT_OK)
    {
        fprintf(stderr, "failed to lex tokens: %s\n", hcc_result_description(result));
        return -1;
    }

    for (size_t i = 0; i < tokens.size; i++)
    {
        struct HccToken *token = { 0 };
        if ((result = hcc_vector_get(&tokens, i, &token)) != HCC_RESULT_OK)
        {
            return result;
        }

        switch (token->type)
        {
        case HCC_TOKEN_TYPE_INTEGER_CONSTANT:
            printf("%s (%llu)\n", hcc_token_type_description(token->type), token->data.integer);
            break;
        default:
            printf("%s\n", hcc_token_type_description(token->type));
            break;
        }
    }

    hcc_vector_free(&tokens);
    hcc_lexer_free(&lexer);

    return 0;
}