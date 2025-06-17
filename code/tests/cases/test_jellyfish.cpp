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

FOSSIL_TEST_SUITE(cpp_jellyfish_fixture);

FOSSIL_SETUP(cpp_jellyfish_fixture) {
    // Setup the test fixture
}

FOSSIL_TEARDOWN(cpp_jellyfish_fixture) {
    // Teardown the test fixture
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Cases
// * * * * * * * * * * * * * * * * * * * * * * * *
// The test cases below are provided as samples, inspired
// by the Meson build system's approach of using test cases
// as samples for library usage.
// * * * * * * * * * * * * * * * * * * * * * * * *

using fossil::ai::Jellyfish;

FOSSIL_TEST_CASE(cpp_test_jellyfish_reset) {
    Jellyfish ai("resettable");
    ai.store_memory("key", "value");
    ai.set_context("context");
    ai.reset();
    ASSUME_ITS_TRUE(ai.memory_count() == 0);
    ASSUME_ITS_TRUE(ai.get_personality().empty());
    ASSUME_ITS_TRUE(ai.get_context().empty());
    ASSUME_ITS_TRUE(!ai.is_initialized());
}

FOSSIL_TEST_CASE(cpp_test_jellyfish_export_import_memory) {
    Jellyfish ai("exporter");
    ai.store_memory("k1", "v1");
    ai.store_memory("k2", "v2");
    bool exported = ai.export_memory("test_mem.txt");
    ASSUME_ITS_TRUE(exported);

    Jellyfish ai2("importer");
    bool imported = ai2.import_memory("test_mem.txt");
    ASSUME_ITS_TRUE(imported);
    ASSUME_ITS_TRUE(ai2.retrieve_memory("k1") == "v1");
    ASSUME_ITS_TRUE(ai2.retrieve_memory("k2") == "v2");
    remove("test_mem.txt");
}

FOSSIL_TEST_CASE(cpp_test_jellyfish_memory_count) {
    Jellyfish ai("counter");
    ASSUME_ITS_TRUE(ai.memory_count() == 0);
    ai.store_memory("a", "1");
    ai.store_memory("b", "2");
    ASSUME_ITS_TRUE(ai.memory_count() == 2);
}

FOSSIL_TEST_CASE(cpp_test_jellyfish_remove_memory) {
    Jellyfish ai("remover");
    ai.store_memory("foo", "bar");
    bool removed = ai.remove_memory("foo");
    ASSUME_ITS_TRUE(removed);
    ASSUME_ITS_TRUE(ai.retrieve_memory("foo").empty());
    bool not_found = ai.remove_memory("baz");
    ASSUME_ITS_TRUE(!not_found);
}

FOSSIL_TEST_CASE(cpp_test_jellyfish_list_memory_keys) {
    Jellyfish ai("lister");
    ai.store_memory("k1", "v1");
    ai.store_memory("k2", "v2");
    auto keys = ai.list_memory_keys();
    ASSUME_ITS_TRUE(keys.size() == 2);
    ASSUME_ITS_TRUE(
        (keys[0] == "k1" && keys[1] == "k2") ||
        (keys[0] == "k2" && keys[1] == "k1")
    );
}

FOSSIL_TEST_CASE(cpp_test_jellyfish_get_context) {
    Jellyfish ai("contextual");
    ai.set_context("deep sea");
    ASSUME_ITS_TRUE(ai.get_context() == "deep sea");
}

FOSSIL_TEST_CASE(cpp_test_jellyfish_get_personality) {
    Jellyfish ai("quirky");
    ASSUME_ITS_TRUE(ai.get_personality() == "quirky");
}

FOSSIL_TEST_CASE(cpp_test_jellyfish_is_initialized) {
    // To test uninitialized, we need to bypass the constructor.
    // We'll just check initialized after construction.
    Jellyfish ai("aware");
    ASSUME_ITS_TRUE(ai.is_initialized());
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *
FOSSIL_TEST_GROUP(cpp_jellyfish_tests) {    
    // Generic ToFu Fixture
    FOSSIL_TEST_ADD(cpp_jellyfish_fixture, cpp_test_jellyfish_reset);
    FOSSIL_TEST_ADD(cpp_jellyfish_fixture, cpp_test_jellyfish_export_import_memory);
    FOSSIL_TEST_ADD(cpp_jellyfish_fixture, cpp_test_jellyfish_memory_count);
    FOSSIL_TEST_ADD(cpp_jellyfish_fixture, cpp_test_jellyfish_remove_memory);
    FOSSIL_TEST_ADD(cpp_jellyfish_fixture, cpp_test_jellyfish_list_memory_keys);
    FOSSIL_TEST_ADD(cpp_jellyfish_fixture, cpp_test_jellyfish_get_context);
    FOSSIL_TEST_ADD(cpp_jellyfish_fixture, cpp_test_jellyfish_get_personality);
    FOSSIL_TEST_ADD(cpp_jellyfish_fixture, cpp_test_jellyfish_is_initialized);

    FOSSIL_TEST_REGISTER(cpp_jellyfish_fixture);
} // end of tests
