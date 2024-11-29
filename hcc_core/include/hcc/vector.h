/*
 * Copyright (c) 2024, SkillerRaptor
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef HCC_VECTOR_H
#define HCC_VECTOR_H

#include <stddef.h>

#include <hcc/prerequisites.h>
#include <hcc/result.h>

HCC_EXTERN_C_BEGIN

struct HccVector
{
    size_t size;
    size_t capacity;

    size_t element_size;
    void *data;
};

enum HccResult hcc_vector_init(struct HccVector *vector, size_t element_size);
void hcc_vector_free(struct HccVector *vector);

enum HccResult hcc_vector_push_back(struct HccVector *vector, void *element);

enum HccResult hcc_vector_get(struct HccVector *vector, size_t index, void **element);

HCC_EXTERN_C_END

#endif // HCC_VECTOR_H