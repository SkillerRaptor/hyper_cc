/*
 * Copyright (c) 2024, SkillerRaptor
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#ifdef __cplusplus
#    define HCC_EXTERN_C_BEGIN \
        extern "C"             \
        {
#    define HCC_EXTERN_C_END }
#else
#    define HCC_EXTERN_C_BEGIN
#    define HCC_EXTERN_C_END
#endif