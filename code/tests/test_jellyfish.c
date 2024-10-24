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
#include <fossil/unittest/framework.h>
#include <fossil/unittest/assume.h>

#include "fossil/jellyfish/framework.h"

#define TEST_FILE "test_network.fish"
#define NUM_LAYERS 2
#define NUM_NEURONS_LAYER1 3
#define NUM_NEURONS_LAYER2 2

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST(test_create_destroy) {
    fossil_jellyfish_network_t* network = fossil_jellyfish_create_network(2, (int32_t[]){3, 2}, (fossil_jellyfish_activation_t[]){ACTIVATION_RELU, ACTIVATION_SIGMOID});
    ASSUME_NOT_CNULL(network);
    fossil_jellyfish_free_network(network);
}

FOSSIL_TEST(test_forward_pass) {
    fossil_jellyfish_network_t* network = fossil_jellyfish_create_network(2, (int32_t[]){3, 2}, (fossil_jellyfish_activation_t[]){ACTIVATION_RELU, ACTIVATION_SIGMOID});
    ASSUME_NOT_CNULL(network);

    double input[] = {1.0, 2.0, 3.0};
    fossil_jellyfish_forward(network, input);

    fossil_jellyfish_free_network(network);
}

FOSSIL_TEST(test_backpropagation) {
    fossil_jellyfish_network_t* network = fossil_jellyfish_create_network(2, (int32_t[]){3, 2}, (fossil_jellyfish_activation_t[]){ACTIVATION_RELU, ACTIVATION_SIGMOID});
    ASSUME_NOT_CNULL(network);

    double input[] = {1.0, 2.0, 3.0};
    double expected_output[] = {0.0, 1.0};
    fossil_jellyfish_forward(network, input);
    fossil_jellyfish_backpropagate(network, expected_output, 0.1);

    fossil_jellyfish_free_network(network);
}

FOSSIL_TEST(test_train) {
    fossil_jellyfish_network_t* network = fossil_jellyfish_create_network(2, (int32_t[]){3, 2}, (fossil_jellyfish_activation_t[]){ACTIVATION_RELU, ACTIVATION_SIGMOID});
    ASSUME_NOT_CNULL(network);

    double inputs[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    double expected_output[] = {0.0, 1.0, 0.0, 1.0};
    fossil_jellyfish_train(network, inputs, expected_output, 2, 100, 0.1);

    fossil_jellyfish_free_network(network);
}

FOSSIL_TEST(test_save_load) {
    fossil_jellyfish_network_t* network = fossil_jellyfish_create_network(2, (int32_t[]){3, 2}, (fossil_jellyfish_activation_t[]){ACTIVATION_RELU, ACTIVATION_SIGMOID});
    ASSUME_NOT_CNULL(network);

    fossil_jellyfish_save(network, TEST_FILE);
    fossil_jellyfish_network_t* loaded_network = fossil_jellyfish_load(TEST_FILE);

    ASSUME_NOT_CNULL(loaded_network);
    fossil_jellyfish_free_network(loaded_network);
    fossil_jellyfish_free_network(network);
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool (Updated)
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST_GROUP(jellyfish_tests) {
    ADD_TEST(test_create_destroy);
    ADD_TEST(test_forward_pass);
    ADD_TEST(test_backpropagation);
    ADD_TEST(test_train);
    ADD_TEST(test_save_load);
}
