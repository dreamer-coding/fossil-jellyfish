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
#ifndef FOSSIL_JELLYFISH_AI_CORE_H
#define FOSSIL_JELLYFISH_AI_CORE_H

#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#ifdef __cplusplus
extern "C" {
#endif

// Activation functions
typedef enum {
    ACTIVATION_RELU,       // Rectified Linear Unit
    ACTIVATION_SIGMOID,    // Sigmoid
    ACTIVATION_TANH,       // Hyperbolic tangent
    ACTIVATION_LEAKY_RELU, // Leaky ReLU with alpha = 0.01
    ACTIVATION_SOFTMAX,    // Softmax is only used for the output layer
    ACTIVATION_ELU         // Exponential Linear Unit
} fossil_jellyfish_activation_t;

// Neural network layer structure
typedef struct {
    int32_t num_neurons;        // Number of neurons in the layer
    double* weights;            // Weight values for the layer
    double* biases;             // Bias values for the layer
    double* outputs;            // Output values for the layer
    double* deltas;             // Error terms for backpropagation
    fossil_jellyfish_activation_t activation; // Activation function for the layer
    double dropout_rate;        // Dropout rate for regularization
    double* normalized_outputs; // Batch normalization outputs
    double* gamma;              // Scaling parameter for batch normalization
    double* beta;               // Shifting parameter for batch normalization
} fossil_jellyfish_layer_t;

// Neural network structure
typedef struct {
    int32_t num_layers;                // Number of layers in the network
    fossil_jellyfish_layer_t** layers; // Array of pointers to the layers
} fossil_jellyfish_network_t;

// Function declarations

/**
 * @brief Creates a neural network with the specified number of layers and neurons per layer.
 * 
 * @param num_layers The number of layers in the network.
 * @param neurons_per_layer An array containing the number of neurons in each layer.
 * @param activations An array containing the activation functions for each layer.
 * @return A pointer to the created neural network.
 */
fossil_jellyfish_network_t* fossil_jellyfish_create_network(int32_t num_layers, int32_t* neurons_per_layer, fossil_jellyfish_activation_t* activations);

/**
 * @brief Frees the memory allocated for the neural network.
 * 
 * @param network A pointer to the neural network to be freed.
 */
void fossil_jellyfish_free_network(fossil_jellyfish_network_t* network);

/**
 * @brief Performs dropout on the given layer during training.
 * 
 * @param layer A pointer to the layer.
 * @param dropout_rate The dropout rate (probability of dropping a neuron).
 */
void fossil_jellyfish_apply_dropout(fossil_jellyfish_layer_t* layer, double dropout_rate);

/**
 * @brief Applies batch normalization to the outputs of the layer.
 * 
 * @param layer A pointer to the layer.
 */
void fossil_jellyfish_apply_batch_normalization(fossil_jellyfish_layer_t* layer);

/**
 * @brief Calculates the Mean Squared Error (MSE) for the network's predictions.
 * 
 * @param network A pointer to the neural network.
 * @param expected_output An array of expected output values.
 * @return The calculated Mean Squared Error.
 */
double fossil_jellyfish_calculate_error(fossil_jellyfish_network_t* network, double* expected_output);

/**
 * @brief Updates the learning rate dynamically based on decay.
 * 
 * @param learning_rate The initial learning rate.
 * @param epoch The current training epoch.
 * @param decay_rate The rate at which the learning rate decays.
 * @return The updated learning rate.
 */
double fossil_jellyfish_update_learning_rate(double learning_rate, int32_t epoch, double decay_rate);

/**
 * @brief Clips the gradients to avoid exploding gradients during backpropagation.
 * 
 * @param layer A pointer to the neural network layer.
 * @param clip_value The threshold value for clipping.
 */
void fossil_jellyfish_clip_gradients(fossil_jellyfish_layer_t* layer, double clip_value);

/**
 * @brief Performs a forward pass through the neural network with the given input.
 * 
 * @param network A pointer to the neural network.
 * @param input An array of input values.
 */
void fossil_jellyfish_forward(fossil_jellyfish_network_t* network, double* input);

/**
 * @brief Performs backpropagation on the neural network with the given expected output and learning rate.
 * 
 * @param network A pointer to the neural network.
 * @param expected_output An array of expected output values.
 * @param learning_rate The learning rate for the backpropagation algorithm.
 */
void fossil_jellyfish_backpropagate(fossil_jellyfish_network_t* network, double* expected_output, double learning_rate);

/**
 * @brief Trains the neural network with the given inputs and expected outputs for a specified number of samples and epochs.
 * 
 * @param network A pointer to the neural network.
 * @param inputs An array of input values.
 * @param expected_output An array of expected output values.
 * @param num_samples The number of samples in the training data.
 * @param num_epochs The number of epochs to train the network.
 * @param learning_rate The learning rate for the training algorithm.
 */
void fossil_jellyfish_train(fossil_jellyfish_network_t* network, double* inputs, double* expected_output, int32_t num_samples, int32_t num_epochs, double learning_rate);

/**
 * @brief Applies the specified activation function to the given value.
 * 
 * @param value The input value.
 * @param activation The activation function to be applied.
 * @return The result of the activation function.
 */
double fossil_jellyfish_activate(double value, fossil_jellyfish_activation_t activation);

/**
 * @brief Computes the derivative of the specified activation function for the given value.
 * 
 * @param value The input value.
 * @param activation The activation function whose derivative is to be computed.
 * @return The derivative of the activation function.
 */
double fossil_jellyfish_activate_derivative(double value, fossil_jellyfish_activation_t activation);

/**
 * @brief Saves the current state of the fossil jellyfish network to a file.
 *
 * @param network A pointer to the fossil jellyfish network to be saved.
 * @param file_path The path to the file where the network state will be saved.
 * @return An integer indicating the success or failure of the save operation.
 */
int32_t fossil_jellyfish_save(fossil_jellyfish_network_t* network, const char* file_path);

/**
 * @brief Loads the fossil jellyfish network state from a file.
 *
 * @param file_path The path to the file from which the network state will be loaded.
 * @return A pointer to the loaded fossil jellyfish network.
 */
fossil_jellyfish_network_t* fossil_jellyfish_load(const char* file_path);

#ifdef __cplusplus
}
#endif

#endif /* FOSSIL_JELLYFISH_AI_CORE_H */
