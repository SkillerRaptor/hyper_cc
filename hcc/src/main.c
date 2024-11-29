/*
 * Copyright (c) 2024, SkillerRaptor
 *
 * SPDX-License-Identifier: MIT
 */

#include <stdio.h>

#include <hcc/lexer.h>

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

    struct HccToken token = { 0 };
    while (!hcc_lexer_is_at_end(&lexer))
    {
        if ((result = hcc_lexer_next_token(&lexer, &token)) != HCC_RESULT_OK)
        {
            fprintf(stderr, "failed to query next token: %s\n", hcc_result_description(result));
            return -1;
        }

        switch (token.type)
        {
        case HCC_TOKEN_TYPE_INTEGER_CONSTANT:
            printf("%s (%llu)\n", hcc_token_type_description(token.type), token.data.integer);
            break;
        default:
            printf("%s\n", hcc_token_type_description(token.type));
            break;
        }
    }

    return 0;
}