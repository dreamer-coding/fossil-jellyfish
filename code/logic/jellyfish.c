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
#include "fossil/ai/jellyfish.h"

// Initialization function
void fossil_jellyfish_initialize(jellyfish_ai_t* ai, const char* personality) {
    if (!ai) {
        fprintf(stderr, "Error: AI structure is NULL during initialization.\n");
        return;
    }
    ai->memory_count = 0;
    ai->interaction_count = 0;
    ai->reasoning_count = 0;
    ai->learning_count = 0;
    strncpy(ai->personality, personality, MAX_INPUT_SIZE);
    ai->is_initialized = true;
    printf("Jellyfish AI initialized with personality: %s\n", ai->personality);
}

// Store memory with key existence check
void fossil_jellyfish_store_memory(jellyfish_ai_t* ai, const char* key, const char* value) {
    if (!ai) {
        fprintf(stderr, "Error: AI structure is NULL during memory storage.\n");
        return;
    }
    for (int i = 0; i < ai->memory_count; i++) {
        if (strcmp(ai->memory[i].key, key) == 0) {
            strncpy(ai->memory[i].value, value, MAX_MEMORY_SIZE);
            printf("Memory updated: [%s] -> %s\n", key, value);
            return;
        }
    }
    if (ai->memory_count >= MAX_MEMORY_SIZE) {
        fprintf(stderr, "Error: Memory limit reached. Cannot store more memory.\n");
        return;
    }
    strncpy(ai->memory[ai->memory_count].key, key, MAX_INPUT_SIZE);
    strncpy(ai->memory[ai->memory_count].value, value, MAX_MEMORY_SIZE);
    ai->memory_count++;
    printf("Memory stored: [%s] -> %s\n", key, value);
}

// Retrieve memory
const char* fossil_jellyfish_retrieve_memory(jellyfish_ai_t* ai, const char* key) {
    if (!ai) {
        fprintf(stderr, "Error: AI structure is NULL during memory retrieval.\n");
        return NULL;
    }
    for (int i = 0; i < ai->memory_count; i++) {
        if (strcmp(ai->memory[i].key, key) == 0) {
            return ai->memory[i].value;
        }
    }
    fprintf(stderr, "Warning: Memory key '%s' not found.\n", key);
    return NULL;
}

// Advanced rule-based response generation
void fossil_jellyfish_generate_response(jellyfish_ai_t* ai, const char* user_input, char* response) {
    if (!ai) {
        fprintf(stderr, "Error: AI structure is NULL during response generation.\n");
        strcpy(response, "Jellyfish AI is not initialized.");
        return;
    }
    if (!ai->is_initialized) {
        fprintf(stderr, "Error: Jellyfish AI is not initialized.\n");
        strcpy(response, "Jellyfish AI is not initialized.");
        return;
    }

    if (strstr(user_input, "hello") || strstr(user_input, "hi")) {
        strcpy(response, "Hello! How can I assist you today?");
    } else if (strstr(user_input, "how are you")) {
        strcpy(response, "I'm just a bunch of code, but I'm functioning as expected. How about you?");
    } else {
        const char* memory_response = fossil_jellyfish_retrieve_memory(ai, user_input);
        if (memory_response) {
            snprintf(response, MAX_RESPONSE_SIZE, "Based on what I remember: %s", memory_response);
        } else {
            snprintf(response, MAX_RESPONSE_SIZE, "You said: %s. That's interesting!", user_input);
        }
    }
} 
