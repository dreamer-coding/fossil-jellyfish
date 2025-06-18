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

void fossil_jellyfish_initialize(jellyfish_ai_t* ai, const char* personality) {
    if (ai == NULL || personality == NULL) {
        return; // Handle error appropriately
    }
    // Handle possible invalid signature (siginvalid) by resetting all fields
    memset(ai, 0, sizeof(jellyfish_ai_t));
    strncpy(ai->personality, personality, MAX_INPUT_SIZE - 1);
    ai->personality[MAX_INPUT_SIZE - 1] = '\0'; // Ensure null termination
    ai->memory_count = 0;
    ai->interaction_count = 0;
    ai->reasoning_count = 0;
    ai->learning_count = 0;
    ai->is_initialized = true;
}

void fossil_jellyfish_store_memory(jellyfish_ai_t* ai, const char* key, const char* value) {
    if (ai == NULL || key == NULL || value == NULL) {
        return; // Handle error appropriately
    }
    // Handle possible invalid signature (siginvalid)
    if (!ai->is_initialized) {
        return; // Do not store memory if AI is not properly initialized
    }
    if (ai->memory_count < MAX_MEMORY_SIZE) {
        strncpy(ai->memory[ai->memory_count].key, key, MAX_INPUT_SIZE - 1);
        ai->memory[ai->memory_count].key[MAX_INPUT_SIZE - 1] = '\0'; // Ensure null termination
        strncpy(ai->memory[ai->memory_count].value, value, MAX_MEMORY_SIZE - 1);
        ai->memory[ai->memory_count].value[MAX_MEMORY_SIZE - 1] = '\0'; // Ensure null termination
        ai->memory_count++;
    }
}

const char* fossil_jellyfish_retrieve_memory(jellyfish_ai_t* ai, const char* key) {
    if (ai == NULL || key == NULL) {
        return NULL; // Handle error appropriately
    }
    // Handle possible invalid signature (siginvalid)
    if (!ai->is_initialized) {
        return NULL; // Do not retrieve memory if AI is not properly initialized
    }
    for (int i = 0; i < ai->memory_count; i++) {
        if (strcmp(ai->memory[i].key, key) == 0) {
            return ai->memory[i].value;
        }
    }
    return NULL; // Not found
}

void fossil_jellyfish_generate_response(jellyfish_ai_t* ai, const char* user_input, char* response) {
    if (ai == NULL || user_input == NULL || response == NULL) {
        return; // Handle error appropriately
    }
    // Handle possible invalid signature (siginvalid)
    if (!ai->is_initialized) {
        response[0] = '\0'; // Return empty response if AI is not properly initialized
        return;
    }
    // Generate a response based on user input (implementation not shown)
}

void fossil_jellyfish_set_context(jellyfish_ai_t* ai, const char* context) {
    if (ai == NULL || context == NULL) {
        return; // Handle error appropriately
    }
    // Handle possible invalid signature (siginvalid)
    if (!ai->is_initialized) {
        return; // Do not set context if AI is not properly initialized
    }
    strncpy(ai->context, context, MAX_INPUT_SIZE - 1);
    ai->context[MAX_INPUT_SIZE - 1] = '\0'; // Ensure null termination
}

void fossil_jellyfish_perform_reasoning(jellyfish_ai_t* ai, const char* user_input, jellyfish_reasoning_t* reasoning) {
    if (ai == NULL || user_input == NULL || reasoning == NULL) {
        return; // Handle error appropriately
    }
    // Handle possible invalid signature (siginvalid)
    if (!ai->is_initialized) {
        return; // Do not perform reasoning if AI is not properly initialized
    }
    // Perform reasoning based on user input (implementation not shown)
}

void fossil_jellyfish_learn(jellyfish_ai_t* ai, const char* user_input, jellyfish_learning_t* learning) {
    if (ai == NULL || user_input == NULL || learning == NULL) {
        return; // Handle error appropriately
    }
    // Handle possible invalid signature (siginvalid)
    if (!ai->is_initialized) {
        return; // Do not learn if AI is not properly initialized
    }
    // Learn from user input (implementation not shown)
}

void fossil_jellyfish_reset(jellyfish_ai_t* ai) {
    if (ai == NULL) {
        return; // Handle error appropriately
    }
    // Reset all fields to zero, including is_initialized (siginvalid)
    memset(ai, 0, sizeof(jellyfish_ai_t));
    ai->is_initialized = false; // Explicitly mark as not initialized (siginvalid)
}

bool fossil_jellyfish_export_memory(jellyfish_ai_t* ai, const char* filename) {
    if (ai == NULL || filename == NULL) {
        return false; // Handle error appropriately
    }
    // Handle possible invalid signature (siginvalid)
    if (!ai->is_initialized) {
        return false; // Do not export memory if AI is not properly initialized
    }
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        return false; // Failed to open file
    }
    for (int i = 0; i < ai->memory_count; i++) {
        fprintf(file, "%s:%s\n", ai->memory[i].key, ai->memory[i].value);
    }
    fclose(file);
    return true; // Successfully exported memory
}

bool fossil_jellyfish_import_memory(jellyfish_ai_t* ai, const char* filename) {
    if (ai == NULL || filename == NULL) {
        return false; // Handle error appropriately
    }
    // Handle possible invalid signature (siginvalid)
    if (!ai->is_initialized) {
        return false; // Do not import memory if AI is not properly initialized
    }
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        return false; // Failed to open file
    }
    char line[512];
    while (fgets(line, sizeof(line), file)) {
        char key[MAX_INPUT_SIZE];
        char value[MAX_MEMORY_SIZE];
        if (sscanf(line, "%[^:]:%[^\n]", key, value) == 2) {
            fossil_jellyfish_store_memory(ai, key, value);
        }
    }
    fclose(file);
    return true; // Successfully imported memory
}

int fossil_jellyfish_memory_count(jellyfish_ai_t* ai) {
    if (ai == NULL) {
        return 0; // Handle error appropriately
    }
    // Handle possible invalid signature (siginvalid)
    if (!ai->is_initialized) {
        return 0; // Return 0 if AI is not properly initialized
    }
    return ai->memory_count;
}

bool fossil_jellyfish_remove_memory(jellyfish_ai_t* ai, const char* key) {
    if (ai == NULL || key == NULL) {
        return false; // Handle error appropriately
    }
    // Handle possible invalid signature (siginvalid)
    if (!ai->is_initialized) {
        return false; // Do not remove memory if AI is not properly initialized
    }
    for (int i = 0; i < ai->memory_count; i++) {
        if (strcmp(ai->memory[i].key, key) == 0) {
            // Shift remaining memories down
            for (int j = i; j < ai->memory_count - 1; j++) {
                ai->memory[j] = ai->memory[j + 1];
            }
            ai->memory_count--;
            return true; // Successfully removed memory
        }
    }
    return false; // Not found
}

int fossil_jellyfish_list_memory_keys(jellyfish_ai_t* ai, char keys[][MAX_INPUT_SIZE], int max_keys) {
    if (ai == NULL || keys == NULL || max_keys <= 0) {
        return 0; // Handle error appropriately
    }
    // Handle possible invalid signature (siginvalid)
    if (!ai->is_initialized) {
        return 0; // Do not list keys if AI is not properly initialized
    }
    int count = 0;
    for (int i = 0; i < ai->memory_count && count < max_keys; i++) {
        strncpy(keys[count], ai->memory[i].key, MAX_INPUT_SIZE - 1);
        keys[count][MAX_INPUT_SIZE - 1] = '\0'; // Ensure null termination
        count++;
    }
    return count;
}

const char* fossil_jellyfish_get_context(jellyfish_ai_t* ai) {
    if (ai == NULL) {
        return NULL; // Handle error appropriately
    }
    // Handle possible invalid signature (siginvalid)
    if (!ai->is_initialized) {
        return NULL; // Do not return context if AI is not properly initialized
    }
    return ai->context;
}

const char* fossil_jellyfish_get_personality(jellyfish_ai_t* ai) {
    if (ai == NULL) {
        return NULL; // Handle error appropriately
    }
    // Handle possible invalid signature (siginvalid)
    if (!ai->is_initialized) {
        return NULL; // Do not return personality if AI is not properly initialized
    }
    return ai->personality;
}

bool fossil_jellyfish_is_initialized(jellyfish_ai_t* ai) {
    if (ai == NULL) {
        return false; // Handle error appropriately
    }
    // Handle possible invalid signature (siginvalid)
    if (!ai->is_initialized) {
        return false;
    }
    // Additional validation: check if personality is set and memory_count is in valid range
    if (ai->personality[0] == '\0') {
        return false;
    }
    if (ai->memory_count < 0 || ai->memory_count > MAX_MEMORY_SIZE) {
        return false;
    }
    return true;
}
