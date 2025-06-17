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
    // Generate a response based on user input (implementation not shown)
}

void fossil_jellyfish_set_context(jellyfish_ai_t* ai, const char* context) {
    if (ai == NULL || context == NULL) {
        return; // Handle error appropriately
    }
    strncpy(ai->context, context, MAX_INPUT_SIZE - 1);
    ai->context[MAX_INPUT_SIZE - 1] = '\0'; // Ensure null termination
}

void fossil_jellyfish_perform_reasoning(jellyfish_ai_t* ai, const char* user_input, jellyfish_reasoning_t* reasoning) {
    if (ai == NULL || user_input == NULL || reasoning == NULL) {
        return; // Handle error appropriately
    }
    // Perform reasoning based on user input (implementation not shown)
}

void fossil_jellyfish_learn(jellyfish_ai_t* ai, const char* user_input, jellyfish_learning_t* learning) {
    if (ai == NULL || user_input == NULL || learning == NULL) {
        return; // Handle error appropriately
    }
    // Learn from user input (implementation not shown)
}

void fossil_jellyfish_reset(jellyfish_ai_t* ai) {
    if (ai == NULL) {
        return; // Handle error appropriately
    }
    memset(ai, 0, sizeof(jellyfish_ai_t)); // Reset all fields to zero
}

bool fossil_jellyfish_export_memory(jellyfish_ai_t* ai, const char* filename) {
    if (ai == NULL || filename == NULL) {
        return false; // Handle error appropriately
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
    return ai->memory_count;
}

bool fossil_jellyfish_remove_memory(jellyfish_ai_t* ai, const char* key) {
    if (ai == NULL || key == NULL) {
        return false; // Handle error appropriately
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
    return ai->context;
}

const char* fossil_jellyfish_get_personality(jellyfish_ai_t* ai) {
    if (ai == NULL) {
        return NULL; // Handle error appropriately
    }
    return ai->personality;
}

bool fossil_jellyfish_is_initialized(jellyfish_ai_t* ai) {
    if (ai == NULL) {
        return false; // Handle error appropriately
    }
    return ai->is_initialized;
}
