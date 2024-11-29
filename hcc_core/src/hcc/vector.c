/*
 * Copyright (c) 2024, SkillerRaptor
 *
 * SPDX-License-Identifier: MIT
 */

#include "hcc/vector.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

enum HccResult hcc_vector_init(struct HccVector *vector, size_t element_size)
{
    if (vector == NULL)
    {
        return HCC_RESULT_BAD_PARAMETER;
    }

    if (element_size == 0)
    {
        return HCC_RESULT_BAD_PARAMETER;
    }

    vector->size = 0;
    vector->capacity = 2;

    vector->element_size = element_size;
    vector->data = malloc(vector->capacity * vector->element_size);

    if (vector->data == NULL)
    {
        return HCC_RESULT_NO_MEMORY;
    }

    return HCC_RESULT_OK;
}

void hcc_vector_free(struct HccVector *vector)
{
    if (vector == NULL)
    {
        return;
    }

    free(vector->data);
}

static enum HccResult hcc_vector_reallocate(struct HccVector *vector, size_t new_capacity)
{
    if (vector == NULL)
    {
        return HCC_RESULT_BAD_PARAMETER;
    }

    if (new_capacity == 0)
    {
        return HCC_RESULT_BAD_PARAMETER;
    }

    if (new_capacity < vector->size)
    {
        vector->size = new_capacity;
    }

    void *new_data = malloc(new_capacity * vector->element_size);
    memcpy(new_data, vector->data, vector->size * vector->element_size);
    free(vector->data);

    vector->data = new_data;
    vector->capacity = new_capacity;

    return HCC_RESULT_OK;
}

enum HccResult hcc_vector_push_back(struct HccVector *vector, void *element)
{
    if (vector == NULL)
    {
        return HCC_RESULT_BAD_PARAMETER;
    }

    if (element == NULL)
    {
        return HCC_RESULT_BAD_PARAMETER;
    }

    enum HccResult result = HCC_RESULT_OK;

    if (vector->size == vector->capacity)
    {
        if ((result = hcc_vector_reallocate(vector, vector->capacity + vector->capacity / 2)) != HCC_RESULT_OK)
        {
            return result;
        }
    }

    vector->size += 1;

    void *ptr = NULL;
    if ((result = hcc_vector_get(vector, vector->size - 1, &ptr)) != HCC_RESULT_OK)
    {
        return result;
    }

    memcpy(ptr, element, vector->element_size);

    return HCC_RESULT_OK;
}

enum HccResult hcc_vector_get(struct HccVector *vector, size_t index, void **element)
{
    if (vector == NULL)
    {
        return HCC_RESULT_BAD_PARAMETER;
    }

    if (index >= vector->size)
    {
        return HCC_RESULT_BAD_PARAMETER;
    }

    if (element == NULL)
    {
        return HCC_RESULT_BAD_PARAMETER;
    }

    *element = ((uint8_t *) vector->data) + (index * vector->element_size);

    return HCC_RESULT_OK;
}
