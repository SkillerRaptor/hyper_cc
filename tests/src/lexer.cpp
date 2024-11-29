/*
 * Copyright (c) 2024, SkillerRaptor
 *
 * SPDX-License-Identifier: MIT
 */

#include <array>
#include <span>
#include <string_view>

#include <catch2/catch_test_macros.hpp>

#include <hcc/lexer.h>

std::vector<HccToken> lex_tokens(const std::string_view code)
{
    HccLexer lexer = {};
    REQUIRE(hcc_lexer_init(&lexer, code.data()) == HCC_RESULT_OK);

    HccVector hcc_tokens = { 0 };
    REQUIRE(hcc_vector_init(&hcc_tokens, sizeof(struct HccToken)) == HCC_RESULT_OK);
    REQUIRE(hcc_lexer_lex_tokens(&lexer, &hcc_tokens) == HCC_RESULT_OK);

    std::vector<HccToken> tokens = {};
    for (size_t i = 0; i < hcc_tokens.size; i++)
    {
        HccToken *token = {};
        REQUIRE(hcc_vector_get(&hcc_tokens, i, &token) == HCC_RESULT_OK);

        tokens.push_back(*token);
    }

    hcc_vector_free(&hcc_tokens);
    hcc_lexer_free(&lexer);

    return tokens;
}

void compare_tokens(const std::span<const HccToken> tokens, const std::span<const HccToken> expected_tokens)
{
    REQUIRE(tokens.size() == expected_tokens.size());

    for (size_t i = 0; i < tokens.size(); ++i)
    {
        const HccToken &token = tokens[i];
        const HccToken &expected_token = expected_tokens[i];

        REQUIRE(token.kind == expected_token.kind);

        switch (token.kind)
        {
        case HCC_TOKEN_KIND_INTEGER_CONSTANT:
            REQUIRE(token.integer == expected_token.integer);
            break;
        default:
            break;
        }
    }
}

TEST_CASE("Addition")
{
    constexpr std::string_view code = "1 + 2";
    const std::vector<HccToken> tokens = lex_tokens(code);

    constexpr std::array<HccToken, 3> expected_tokens = {
        HccToken{
            .kind = HCC_TOKEN_KIND_INTEGER_CONSTANT,
            .integer = 1,
        },
        HccToken{
            .kind = HCC_TOKEN_KIND_PLUS,
        },
        HccToken{
            .kind = HCC_TOKEN_KIND_INTEGER_CONSTANT,
            .integer = 2,
        },
    };

    compare_tokens(tokens, expected_tokens);
}