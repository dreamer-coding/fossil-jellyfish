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
#include <fossil/test/framework.h>

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

FOSSIL_TEST_CASE(c_test_jellyfish_initialize) {
    jellyfish_ai_t ai;
    fossil_jellyfish_initialize(&ai, "friendly");
    ASSUME_ITS_TRUE(strcmp(ai.personality, "friendly") == 0);
}

FOSSIL_TEST_CASE(c_test_jellyfish_store_memory) {
    jellyfish_ai_t ai;
    fossil_jellyfish_initialize(&ai, "neutral");
    fossil_jellyfish_store_memory(&ai, "greeting", "hello");
    const char* value = fossil_jellyfish_retrieve_memory(&ai, "greeting");
    ASSUME_ITS_TRUE(strcmp(value, "hello") == 0);
}

FOSSIL_TEST_CASE(c_test_jellyfish_retrieve_memory) {
    jellyfish_ai_t ai;
    fossil_jellyfish_initialize(&ai, "neutral");
    fossil_jellyfish_store_memory(&ai, "farewell", "goodbye");
    const char* value = fossil_jellyfish_retrieve_memory(&ai, "farewell");
    ASSUME_ITS_TRUE(strcmp(value, "goodbye") == 0);
}

FOSSIL_TEST_CASE(c_test_jellyfish_generate_response) {
    jellyfish_ai_t ai;
    char response[256];
    fossil_jellyfish_initialize(&ai, "friendly");
    fossil_jellyfish_generate_response(&ai, "How are you?", response);
    ASSUME_ITS_TRUE(strlen(response) > 0); // Ensure a response is generated
}


// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *
FOSSIL_TEST_GROUP(c_jellyfish_tests) {    
    // Generic ToFu Fixture
    // FOSSIL_TEST_ADD(c_jellyfish_fixture, c_test_jellyfish_initialize);
    // FOSSIL_TEST_ADD(c_jellyfish_fixture, c_test_jellyfish_store_memory);
    // FOSSIL_TEST_ADD(c_jellyfish_fixture, c_test_jellyfish_retrieve_memory);
    // FOSSIL_TEST_ADD(c_jellyfish_fixture, c_test_jellyfish_generate_response);

    FOSSIL_TEST_REGISTER(c_jellyfish_fixture);
} // end of tests
