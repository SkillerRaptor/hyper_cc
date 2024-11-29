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

    std::vector<HccToken> tokens = {};
    while (!hcc_lexer_is_at_end(&lexer))
    {
        HccToken token = {};
        REQUIRE(hcc_lexer_next_token(&lexer, &token) == HCC_RESULT_OK);

        tokens.push_back(token);
    }

    return tokens;
}

void compare_tokens(const std::span<const HccToken> tokens, const std::span<const HccToken> expected_tokens)
{
    REQUIRE(tokens.size() == expected_tokens.size());

    for (size_t index = 0; index < tokens.size(); ++index)
    {
        const HccToken &token = tokens[index];
        const HccToken &expected_token = expected_tokens[index];

        REQUIRE(token.type == expected_token.type);

        switch (token.type)
        {
        case HCC_TOKEN_TYPE_INTEGER_CONSTANT:
            REQUIRE(token.data.integer == expected_token.data.integer);
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
            .type = HCC_TOKEN_TYPE_INTEGER_CONSTANT,
            .data = {
                .integer = 1,
            },
        },
        HccToken{
            .type = HCC_TOKEN_TYPE_PLUS,
        },
        HccToken{
            .type = HCC_TOKEN_TYPE_INTEGER_CONSTANT,
            .data = {
                .integer = 2,
            },
        },
    };

    compare_tokens(tokens, expected_tokens);
}