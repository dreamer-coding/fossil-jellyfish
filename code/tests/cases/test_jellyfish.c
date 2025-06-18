/*
 * -----------------------------------------------------------------------------
 * Project: Fossil Logic
 *
 * This file is part of the Fossil Logic project, which aims to develop high-
 * performance, cross-platform applications and libraries. The code contained
 * herein is subject to the terms and conditions defined in the project license.
 *
 * Author: Michael Gene Brockus (Dreamer)
 *
 * Copyright (C) 2024 Fossil Logic. All rights reserved.
 * -----------------------------------------------------------------------------
 */
#include <fossil/pizza/framework.h>
#include "fossil/ai/framework.h"

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Utilities
// * * * * * * * * * * * * * * * * * * * * * * * *
// Setup steps for things like test fixtures and
// mock objects are set here.
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST_SUITE(c_jellyfish_fixture);

FOSSIL_SETUP(c_jellyfish_fixture) {
    // Setup the test fixture
}

FOSSIL_TEARDOWN(c_jellyfish_fixture) {
    // Teardown the test fixture
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Cases
// * * * * * * * * * * * * * * * * * * * * * * * *
// The test cases below are provided as samples, inspired
// by the Meson build system's approach of using test cases
// as samples for library usage.
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST_CASE(c_test_jellyfish_reset) {
    jellyfish_ai_t ai;
    fossil_jellyfish_initialize(&ai, "resettable");
    fossil_jellyfish_store_memory(&ai, "key", "value");
    fossil_jellyfish_set_context(&ai, "context");
    fossil_jellyfish_reset(&ai);
    ASSUME_ITS_TRUE(ai.memory_count == 0);
    ASSUME_ITS_TRUE(ai.personality[0] == '\0');
    ASSUME_ITS_TRUE(ai.context[0] == '\0');
    ASSUME_ITS_TRUE(!ai.is_initialized);
}

FOSSIL_TEST_CASE(c_test_jellyfish_export_import_memory) {
    jellyfish_ai_t ai;
    fossil_jellyfish_initialize(&ai, "exporter");
    fossil_jellyfish_store_memory(&ai, "k1", "v1");
    fossil_jellyfish_store_memory(&ai, "k2", "v2");
    bool exported = fossil_jellyfish_export_memory(&ai, "test_mem.txt");
    ASSUME_ITS_TRUE(exported);

    jellyfish_ai_t ai2;
    fossil_jellyfish_initialize(&ai2, "importer");
    bool imported = fossil_jellyfish_import_memory(&ai2, "test_mem.txt");
    ASSUME_ITS_TRUE(imported);
    ASSUME_ITS_TRUE(strcmp(fossil_jellyfish_retrieve_memory(&ai2, "k1"), "v1") == 0);
    ASSUME_ITS_TRUE(strcmp(fossil_jellyfish_retrieve_memory(&ai2, "k2"), "v2") == 0);
    remove("test_mem.txt");
}

FOSSIL_TEST_CASE(c_test_jellyfish_memory_count) {
    jellyfish_ai_t ai;
    fossil_jellyfish_initialize(&ai, "counter");
    ASSUME_ITS_TRUE(fossil_jellyfish_memory_count(&ai) == 0);
    fossil_jellyfish_store_memory(&ai, "a", "1");
    fossil_jellyfish_store_memory(&ai, "b", "2");
    ASSUME_ITS_TRUE(fossil_jellyfish_memory_count(&ai) == 2);
}

FOSSIL_TEST_CASE(c_test_jellyfish_remove_memory) {
    jellyfish_ai_t ai;
    fossil_jellyfish_initialize(&ai, "remover");
    fossil_jellyfish_store_memory(&ai, "foo", "bar");
    bool removed = fossil_jellyfish_remove_memory(&ai, "foo");
    ASSUME_ITS_TRUE(removed);
    ASSUME_ITS_TRUE(fossil_jellyfish_retrieve_memory(&ai, "foo") == NULL);
    bool not_found = fossil_jellyfish_remove_memory(&ai, "baz");
    ASSUME_ITS_TRUE(!not_found);
}

FOSSIL_TEST_CASE(c_test_jellyfish_list_memory_keys) {
    jellyfish_ai_t ai;
    fossil_jellyfish_initialize(&ai, "lister");
    fossil_jellyfish_store_memory(&ai, "k1", "v1");
    fossil_jellyfish_store_memory(&ai, "k2", "v2");
    char keys[4][MAX_INPUT_SIZE];
    int count = fossil_jellyfish_list_memory_keys(&ai, keys, 4);
    ASSUME_ITS_TRUE(count == 2);
    ASSUME_ITS_TRUE((strcmp(keys[0], "k1") == 0 && strcmp(keys[1], "k2") == 0) ||
                    (strcmp(keys[0], "k2") == 0 && strcmp(keys[1], "k1") == 0));
}

FOSSIL_TEST_CASE(c_test_jellyfish_get_context) {
    jellyfish_ai_t ai;
    fossil_jellyfish_initialize(&ai, "contextual");
    fossil_jellyfish_set_context(&ai, "deep sea");
    const char* ctx = fossil_jellyfish_get_context(&ai);
    ASSUME_ITS_TRUE(strcmp(ctx, "deep sea") == 0);
}

FOSSIL_TEST_CASE(c_test_jellyfish_get_personality) {
    jellyfish_ai_t ai;
    fossil_jellyfish_initialize(&ai, "quirky");
    const char* pers = fossil_jellyfish_get_personality(&ai);
    ASSUME_ITS_TRUE(strcmp(pers, "quirky") == 0);
}

FOSSIL_TEST_CASE(c_test_jellyfish_is_initialized) {
    jellyfish_ai_t ai;
    ASSUME_NOT_TRUE(fossil_jellyfish_is_initialized(&ai));
    fossil_jellyfish_initialize(&ai, "aware");
    ASSUME_ITS_TRUE(fossil_jellyfish_is_initialized(&ai));
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *
FOSSIL_TEST_GROUP(c_jellyfish_tests) {    
    // Generic ToFu Fixture
    FOSSIL_TEST_ADD(c_jellyfish_fixture, c_test_jellyfish_reset);
    FOSSIL_TEST_ADD(c_jellyfish_fixture, c_test_jellyfish_export_import_memory);
    FOSSIL_TEST_ADD(c_jellyfish_fixture, c_test_jellyfish_memory_count);
    FOSSIL_TEST_ADD(c_jellyfish_fixture, c_test_jellyfish_remove_memory);
    FOSSIL_TEST_ADD(c_jellyfish_fixture, c_test_jellyfish_list_memory_keys);
    FOSSIL_TEST_ADD(c_jellyfish_fixture, c_test_jellyfish_get_context);
    FOSSIL_TEST_ADD(c_jellyfish_fixture, c_test_jellyfish_get_personality);
    FOSSIL_TEST_ADD(c_jellyfish_fixture, c_test_jellyfish_is_initialized);

    FOSSIL_TEST_REGISTER(c_jellyfish_fixture);
} // end of tests
