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
#include "fossil/jellyfish/jellyfish.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

// Utility functions for activations
double fossil_jellyfish_activate(double value, fossil_jellyfish_activation_t activation) {
    switch (activation) {
        case ACTIVATION_RELU:
            return value > 0 ? value : 0;
        case ACTIVATION_SIGMOID:
            return 1.0 / (1.0 + exp(-value));
        case ACTIVATION_TANH:
            return tanh(value);
        default:
            return value;
    }
}

double fossil_jellyfish_activate_derivative(double value, fossil_jellyfish_activation_t activation) {
    switch (activation) {
        case ACTIVATION_RELU:
            return value > 0 ? 1 : 0;
        case ACTIVATION_SIGMOID:
            return value * (1 - value);  // Sigmoid derivative
        case ACTIVATION_TANH:
            return 1 - value * value;  // Tanh derivative
        default:
            return value;
    }
}

// Creates a new neural network
fossil_jellyfish_network_t* fossil_jellyfish_create_network(int32_t num_layers, int32_t* neurons_per_layer, fossil_jellyfish_activation_t* activations) {
    if (num_layers <= 0 || neurons_per_layer == NULL || activations == NULL) {
        return NULL; // Invalid input
    }

    fossil_jellyfish_network_t* network = (fossil_jellyfish_network_t*)malloc(sizeof(fossil_jellyfish_network_t));
    if (network == NULL) {
        return NULL; // Memory allocation failed
    }
    
    network->num_layers = num_layers;
    network->layers = (fossil_jellyfish_layer_t**)malloc(num_layers * sizeof(fossil_jellyfish_layer_t*));
    if (network->layers == NULL) {
        free(network);
        return NULL; // Memory allocation failed
    }

    for (int32_t i = 0; i < num_layers; i++) {
        fossil_jellyfish_layer_t* layer = (fossil_jellyfish_layer_t*)malloc(sizeof(fossil_jellyfish_layer_t));
        if (layer == NULL) {
            fossil_jellyfish_free_network(network);
            return NULL; // Memory allocation failed
        }

        layer->num_neurons = neurons_per_layer[i];
        layer->activation = activations[i];

        if (i > 0) {  // Skip weights and biases for the input layer
            layer->weights = (double*)malloc(neurons_per_layer[i] * neurons_per_layer[i-1] * sizeof(double));
            layer->biases = (double*)malloc(neurons_per_layer[i] * sizeof(double));
            layer->deltas = (double*)calloc(neurons_per_layer[i], sizeof(double));

            if (layer->weights == NULL || layer->biases == NULL || layer->deltas == NULL) {
                fossil_jellyfish_free_network(network);
                return NULL; // Memory allocation failed
            }
        } else {
            layer->weights = NULL;
            layer->biases = NULL;
            layer->deltas = NULL;
        }

        layer->outputs = (double*)calloc(neurons_per_layer[i], sizeof(double));
        if (layer->outputs == NULL) {
            fossil_jellyfish_free_network(network);
            return NULL; // Memory allocation failed
        }

        network->layers[i] = layer;
    }

    return network;
}

// Frees up memory allocated for the network
void fossil_jellyfish_free_network(fossil_jellyfish_network_t* network) {
    if (network == NULL) return;

    for (int i = 0; i < network->num_layers; i++) {
        fossil_jellyfish_layer_t* layer = network->layers[i];
        if (layer != NULL) {
            free(layer->biases);
            free(layer->weights);
            free(layer->deltas);
            free(layer->outputs); // Added free for outputs
            free(layer);
        }
    }
    
    free(network->layers);
    network->layers = NULL;
    
    free(network);
    network = NULL;
}

// Applies dropout to the layer during training
void fossil_jellyfish_apply_dropout(fossil_jellyfish_layer_t* layer, double dropout_rate) {
    if (!layer || dropout_rate < 0 || dropout_rate > 1) {
        fprintf(stderr, "Invalid arguments to fossil_jellyfish_apply_dropout\n");
        return;
    }
    for (int32_t i = 0; i < layer->num_neurons; i++) {
        if ((double)rand() / RAND_MAX < dropout_rate) {
            layer->outputs[i] = 0;
        }
    }
}

// Applies batch normalization to the outputs of the layer
void fossil_jellyfish_apply_batch_normalization(fossil_jellyfish_layer_t* layer) {
    if (!layer || !layer->outputs || !layer->normalized_outputs || !layer->gamma || !layer->beta) {
        fprintf(stderr, "Invalid arguments to fossil_jellyfish_apply_batch_normalization\n");
        return;
    }

    // Calculate the mean
    double mean = 0;
    for (int32_t i = 0; i < layer->num_neurons; i++) {
        mean += layer->outputs[i];
    }
    mean /= layer->num_neurons;

    // Calculate the variance
    double variance = 0;
    for (int32_t i = 0; i < layer->num_neurons; i++) {
        variance += (layer->outputs[i] - mean) * (layer->outputs[i] - mean);
    }
    variance /= layer->num_neurons;

    // Normalize the outputs
    for (int32_t i = 0; i < layer->num_neurons; i++) {
        layer->normalized_outputs[i] = (layer->outputs[i] - mean) / sqrt(variance + 1e-8);
    }

    // Scale and shift the normalized outputs
    for (int32_t i = 0; i < layer->num_neurons; i++) {
        layer->outputs[i] = layer->gamma[i] * layer->normalized_outputs[i] + layer->beta[i];
    }
}

// Calculates the Mean Squared Error (MSE) for the network's predictions
double fossil_jellyfish_calculate_error(fossil_jellyfish_network_t* network, double* expected_output) {
    if (!network || !expected_output) {
        fprintf(stderr, "Invalid arguments to fossil_jellyfish_calculate_error\n");
        return -1;
    }

    fossil_jellyfish_layer_t* output_layer = network->layers[network->num_layers - 1];
    double error = 0;

    for (int32_t i = 0; i < output_layer->num_neurons; i++) {
        double diff = expected_output[i] - output_layer->outputs[i];
        error += diff * diff;
    }

    return error / output_layer->num_neurons;
}

// Updates the learning rate dynamically based on decay
double fossil_jellyfish_update_learning_rate(double learning_rate, int32_t epoch, double decay_rate) {
    if (learning_rate <= 0 || decay_rate < 0) {
        fprintf(stderr, "Invalid arguments to fossil_jellyfish_update_learning_rate\n");
        return learning_rate;
    }
    return learning_rate / (1 + decay_rate * epoch);
}

// Clips the gradients to avoid exploding gradients during backpropagation
void fossil_jellyfish_clip_gradients(fossil_jellyfish_layer_t* layer, double clip_value) {
    if (!layer || clip_value <= 0) {
        fprintf(stderr, "Invalid arguments to fossil_jellyfish_clip_gradients\n");
        return;
    }

    for (int32_t i = 0; i < layer->num_neurons; i++) {
        if (layer->deltas[i] > clip_value) {
            layer->deltas[i] = clip_value;
        } else if (layer->deltas[i] < -clip_value) {
            layer->deltas[i] = -clip_value;
        }
    }
}

// Forward pass through the network
void fossil_jellyfish_forward(fossil_jellyfish_network_t* network, double* input) {
    // Load input into the first layer
    memcpy(network->layers[0]->outputs, input, network->layers[0]->num_neurons * sizeof(double));

    for (int32_t i = 1; i < network->num_layers; i++) {
        fossil_jellyfish_layer_t* prev_layer = network->layers[i - 1];
        fossil_jellyfish_layer_t* layer = network->layers[i];

        for (int32_t j = 0; j < layer->num_neurons; j++) {
            double weighted_sum = 0;
            for (int32_t k = 0; k < prev_layer->num_neurons; k++) {
                weighted_sum += prev_layer->outputs[k] * layer->weights[j * prev_layer->num_neurons + k];
            }
            weighted_sum += layer->biases[j];
            layer->outputs[j] = fossil_jellyfish_activate(weighted_sum, layer->activation);
        }
    }
}

// Backpropagation algorithm to adjust weights and biases
void fossil_jellyfish_backpropagate(fossil_jellyfish_network_t* network, double* expected_output, double learning_rate) {
    fossil_jellyfish_layer_t* output_layer = network->layers[network->num_layers - 1];

    // Calculate deltas for the output layer
    for (int32_t i = 0; i < output_layer->num_neurons; i++) {
        double error = expected_output[i] - output_layer->outputs[i];
        output_layer->deltas[i] = error * fossil_jellyfish_activate_derivative(output_layer->outputs[i], output_layer->activation);
    }

    // Propagate the error backward
    for (int32_t i = network->num_layers - 2; i >= 0; i--) {
        fossil_jellyfish_layer_t* layer = network->layers[i];
        fossil_jellyfish_layer_t* next_layer = network->layers[i + 1];

        for (int32_t j = 0; j < layer->num_neurons; j++) {
            double error = 0;
            for (int32_t k = 0; k < next_layer->num_neurons; k++) {
                error += next_layer->weights[k * layer->num_neurons + j] * next_layer->deltas[k];
            }
            layer->deltas[j] = error * fossil_jellyfish_activate_derivative(layer->outputs[j], layer->activation);
        }

        // Update weights and biases
        for (int32_t j = 0; j < next_layer->num_neurons; j++) {
            for (int32_t k = 0; k < layer->num_neurons; k++) {
                next_layer->weights[j * layer->num_neurons + k] += learning_rate * next_layer->deltas[j] * layer->outputs[k];
            }
            next_layer->biases[j] += learning_rate * next_layer->deltas[j];
        }
    }
}

// Train the network with gradient descent
void fossil_jellyfish_train(fossil_jellyfish_network_t* network, double* inputs, double* expected_output, int32_t num_samples, int32_t num_epochs, double learning_rate) {
    for (int32_t epoch = 0; epoch < num_epochs; epoch++) {
        for (int32_t i = 0; i < num_samples; i++) {
            fossil_jellyfish_forward(network, &inputs[i * network->layers[0]->num_neurons]);
            fossil_jellyfish_backpropagate(network, &expected_output[i * network->layers[network->num_layers - 1]->num_neurons], learning_rate);
        }
    }
}

int32_t fossil_jellyfish_save(fossil_jellyfish_network_t* network, const char* file_path) {
    FILE *file = fopen(file_path, "wb");
    if (!file) {
        return -1;  // Error opening the file
    }

    // Write the number of layers
    fwrite(&network->num_layers, sizeof(int32_t), 1, file);

    // Write each layer's data
    for (int i = 0; i < network->num_layers; i++) {
        fossil_jellyfish_layer_t* layer = network->layers[i];

        // Write number of neurons
        fwrite(&layer->num_neurons, sizeof(int32_t), 1, file);

        // Write activation function
        fwrite(&layer->activation, sizeof(fossil_jellyfish_activation_t), 1, file);

        // Write biases (size is num_neurons)
        fwrite(layer->biases, sizeof(double), layer->num_neurons, file);

        // Write weights (size is num_neurons * number of neurons in previous layer)
        int32_t prev_layer_neurons = (i == 0) ? 0 : network->layers[i - 1]->num_neurons;
        fwrite(layer->weights, sizeof(double), layer->num_neurons * prev_layer_neurons, file);

        // Optionally save deltas (used in backpropagation)
        fwrite(layer->deltas, sizeof(double), layer->num_neurons, file);
    }

    fclose(file);
    return 0;  // Success
}

fossil_jellyfish_network_t* fossil_jellyfish_load(const char* file_path) {
    FILE *file = fopen(file_path, "rb");
    if (!file) {
        return NULL;  // Error opening the file
    }

    // Read the number of layers
    int32_t num_layers;
    fread(&num_layers, sizeof(int32_t), 1, file);

    // Allocate memory for the network
    fossil_jellyfish_network_t* network = (fossil_jellyfish_network_t*)malloc(sizeof(fossil_jellyfish_network_t));
    network->num_layers = num_layers;
    network->layers = (fossil_jellyfish_layer_t**)malloc(num_layers * sizeof(fossil_jellyfish_layer_t*));

    // Read each layer's data
    for (int i = 0; i < num_layers; i++) {
        // Allocate memory for the layer
        fossil_jellyfish_layer_t* layer = (fossil_jellyfish_layer_t*)malloc(sizeof(fossil_jellyfish_layer_t));

        // Read number of neurons
        fread(&layer->num_neurons, sizeof(int32_t), 1, file);

        // Read activation function
        fread(&layer->activation, sizeof(fossil_jellyfish_activation_t), 1, file);

        // Allocate and read biases
        layer->biases = (double*)malloc(layer->num_neurons * sizeof(double));
        fread(layer->biases, sizeof(double), layer->num_neurons, file);

        // Allocate and read weights (size is num_neurons * number of neurons in previous layer)
        int32_t prev_layer_neurons = (i == 0) ? 0 : network->layers[i - 1]->num_neurons;
        layer->weights = (double*)malloc(layer->num_neurons * prev_layer_neurons * sizeof(double));
        fread(layer->weights, sizeof(double), layer->num_neurons * prev_layer_neurons, file);

        // Allocate and read deltas (if used)
        layer->deltas = (double*)malloc(layer->num_neurons * sizeof(double));
        fread(layer->deltas, sizeof(double), layer->num_neurons, file);

        // Assign the layer to the network
        network->layers[i] = layer;
    }

    fclose(file);
    return network;
}
