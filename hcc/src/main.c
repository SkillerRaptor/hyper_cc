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

    if ((result = hcc_lexer_lex_tokens(&lexer, &tokens)) != HCC_RESULT_OK)
    {
        fprintf(stderr, "failed to lex tokens: %s\n", hcc_result_description(result));
        return -1;
    }

    hcc_vector_free(&tokens);
    hcc_lexer_free(&lexer);

    return 0;
}