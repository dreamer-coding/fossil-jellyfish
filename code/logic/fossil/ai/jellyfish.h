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
#ifndef FOSSIL_JELLYFISH_AI_H
#define FOSSIL_JELLYFISH_AI_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_INPUT_SIZE 256
#define MAX_RESPONSE_SIZE 512
#define MAX_MEMORY_SIZE 1000

#ifdef __cplusplus
extern "C"
{
#endif

// *****************************************************************************
// Type definitions
// *****************************************************************************

// Define data structures for Jellyfish AI
typedef struct {
    char key[MAX_INPUT_SIZE];
    char value[MAX_MEMORY_SIZE];
} jellyfish_memory_t;

typedef struct {
    char user_input[MAX_INPUT_SIZE];
    char ai_response[MAX_RESPONSE_SIZE];
} jellyfish_interaction_t;

typedef struct {
    char hypothesis[MAX_RESPONSE_SIZE];
    char evidence[MAX_RESPONSE_SIZE];
} jellyfish_reasoning_t;

typedef struct {
    char concepts[MAX_INPUT_SIZE];
    char details[MAX_RESPONSE_SIZE];
} jellyfish_learning_t;

typedef struct {
    jellyfish_memory_t memory[MAX_MEMORY_SIZE];
    jellyfish_interaction_t interactions[MAX_MEMORY_SIZE];
    jellyfish_reasoning_t reasoning[MAX_MEMORY_SIZE];
    jellyfish_learning_t learning[MAX_MEMORY_SIZE];
    int memory_count;
    int interaction_count;
    int reasoning_count;
    int learning_count;
    char context[MAX_INPUT_SIZE];
    char personality[MAX_INPUT_SIZE];
    bool is_initialized;
} jellyfish_ai_t;

// *****************************************************************************
// Function prototypes
// *****************************************************************************

// AI training, learning, and response function prototypes

/**
 * @brief Initialize the Jellyfish AI with a given personality.
 *
 * @param ai Pointer to the jellyfish_ai_t structure to initialize.
 * @param personality String representing the AI's personality.
 */
void fossil_jellyfish_initialize(jellyfish_ai_t* ai, const char* personality);

/**
 * @brief Store a key-value pair in the AI's memory.
 *
 * @param ai Pointer to the jellyfish_ai_t structure.
 * @param key Key string to identify the memory.
 * @param value Value string to store.
 */
void fossil_jellyfish_store_memory(jellyfish_ai_t* ai, const char* key, const char* value);

/**
 * @brief Retrieve a value from the AI's memory by key.
 *
 * @param ai Pointer to the jellyfish_ai_t structure.
 * @param key Key string to look up.
 * @return Pointer to the value string, or NULL if not found.
 */
const char* fossil_jellyfish_retrieve_memory(jellyfish_ai_t* ai, const char* key);

/**
 * @brief Generate a response based on user input.
 *
 * @param ai Pointer to the jellyfish_ai_t structure.
 * @param user_input Input string from the user.
 * @param response Output buffer for the AI's response.
 */
void fossil_jellyfish_generate_response(jellyfish_ai_t* ai, const char* user_input, char* response);

/**
 * @brief Set the context for the AI.
 *
 * @param ai Pointer to the jellyfish_ai_t structure.
 * @param context String representing the new context.
 */
void fossil_jellyfish_set_context(jellyfish_ai_t* ai, const char* context);

/**
 * @brief Perform reasoning based on user input.
 *
 * @param ai Pointer to the jellyfish_ai_t structure.
 * @param user_input Input string from the user.
 * @param reasoning Output structure for reasoning results.
 */
void fossil_jellyfish_perform_reasoning(jellyfish_ai_t* ai, const char* user_input, jellyfish_reasoning_t* reasoning);

/**
 * @brief Learn from user input.
 *
 * @param ai Pointer to the jellyfish_ai_t structure.
 * @param user_input Input string from the user.
 * @param learning Output structure for learning results.
 */
void fossil_jellyfish_learn(jellyfish_ai_t* ai, const char* user_input, jellyfish_learning_t* learning);

/**
 * @brief Reset the AI to its initial state.
 *
 * @param ai Pointer to the jellyfish_ai_t structure.
 */
void fossil_jellyfish_reset(jellyfish_ai_t* ai);

/**
 * @brief Export the AI's memory to a file.
 *
 * @param ai Pointer to the jellyfish_ai_t structure.
 * @param filename Name of the file to export to.
 * @return true on success, false on failure.
 */
bool fossil_jellyfish_export_memory(jellyfish_ai_t* ai, const char* filename);

/**
 * @brief Import memory into the AI from a file.
 *
 * @param ai Pointer to the jellyfish_ai_t structure.
 * @param filename Name of the file to import from.
 * @return true on success, false on failure.
 */
bool fossil_jellyfish_import_memory(jellyfish_ai_t* ai, const char* filename);

/**
 * @brief Get the current number of memories stored.
 *
 * @param ai Pointer to the jellyfish_ai_t structure.
 * @return Number of memories stored.
 */
int fossil_jellyfish_memory_count(jellyfish_ai_t* ai);

/**
 * @brief Remove a memory entry by key.
 *
 * @param ai Pointer to the jellyfish_ai_t structure.
 * @param key Key string of the memory to remove.
 * @return true if removed, false if not found.
 */
bool fossil_jellyfish_remove_memory(jellyfish_ai_t* ai, const char* key);

/**
 * @brief List all memory keys.
 *
 * @param ai Pointer to the jellyfish_ai_t structure.
 * @param keys Output array to fill with keys.
 * @param max_keys Maximum number of keys to list.
 * @return Number of keys listed.
 */
int fossil_jellyfish_list_memory_keys(jellyfish_ai_t* ai, char keys[][MAX_INPUT_SIZE], int max_keys);

/**
 * @brief Get the AI's current context.
 *
 * @param ai Pointer to the jellyfish_ai_t structure.
 * @return Pointer to the context string.
 */
const char* fossil_jellyfish_get_context(jellyfish_ai_t* ai);

/**
 * @brief Get the AI's current personality.
 *
 * @param ai Pointer to the jellyfish_ai_t structure.
 * @return Pointer to the personality string.
 */
const char* fossil_jellyfish_get_personality(jellyfish_ai_t* ai);

/**
 * @brief Check if the AI is initialized.
 *
 * @param ai Pointer to the jellyfish_ai_t structure.
 * @return true if initialized, false otherwise.
 */
bool fossil_jellyfish_is_initialized(jellyfish_ai_t* ai);


#ifdef __cplusplus
}
#include <stdexcept>
#include <vector>
#include <string>

namespace fossil {

namespace ai {

    class Jellyfish {
    private:
        jellyfish_ai_t ai_;
    public:
        /**
         * @brief Constructor to initialize the Jellyfish AI with a personality.
         *
         * @param personality String representing the AI's personality.
         * @throws std::runtime_error if initialization fails.
         */
        Jellyfish(const std::string& personality) {
            fossil_jellyfish_initialize(&ai_, personality.c_str());
            if (!fossil_jellyfish_is_initialized(&ai_)) {
                throw std::runtime_error("Failed to initialize Jellyfish AI");
            }
        }

        /**
         * @brief Destructor to clean up the Jellyfish AI.
         */
        ~Jellyfish() {
            // No explicit cleanup needed as the C API handles it
            // However, you could call reset() if you want to ensure a clean state
            fossil_jellyfish_reset(&ai_);
        }

        /**
         * @brief Store a key-value pair in the AI's memory.
         *
         * @param key Key string to identify the memory.
         * @param value Value string to store.
         */
        void store_memory(const std::string& key, const std::string& value) {
            fossil_jellyfish_store_memory(&ai_, key.c_str(), value.c_str());
        }

        /**
         * @brief Retrieve a value from the AI's memory by key.
         *
         * @param key Key string to look up.
         * @return Value string if found, empty string otherwise.
         */
        std::string retrieve_memory(const std::string& key) {
            const char* value = fossil_jellyfish_retrieve_memory(&ai_, key.c_str());
            return value ? std::string(value) : std::string();
        }

        /**
         * @brief Generate a response based on user input.
         *
         * @param user_input Input string from the user.
         * @return AI's response string.
         */
        std::string generate_response(const std::string& user_input) {
            char buffer[MAX_RESPONSE_SIZE] = {0};
            fossil_jellyfish_generate_response(&ai_, user_input.c_str(), buffer);
            return std::string(buffer);
        }

        /**
         * @brief Set the context for the AI.
         *
         * @param context String representing the new context.
         */
        void set_context(const std::string& context) {
            fossil_jellyfish_set_context(&ai_, context.c_str());
        }

        /**
         * @brief Perform reasoning based on user input.
         *
         * @param user_input Input string from the user.
         * @param reasoning Output structure for reasoning results.
         */
        void perform_reasoning(const std::string& user_input, jellyfish_reasoning_t& reasoning) {
            fossil_jellyfish_perform_reasoning(&ai_, user_input.c_str(), &reasoning);
        }

        /**
         * @brief Learn from user input.
         *
         * @param user_input Input string from the user.
         * @param learning Output structure for learning results.
         */
        void learn(const std::string& user_input, jellyfish_learning_t& learning) {
            fossil_jellyfish_learn(&ai_, user_input.c_str(), &learning);
        }

        /**
         * @brief Reset the AI to its initial state.
         */
        void reset() {
            fossil_jellyfish_reset(&ai_);
        }

        /**
         * @brief Export the AI's memory to a file.
         *
         * @param filename Name of the file to export to.
         * @return true if successful, false otherwise.
         */
        bool export_memory(const std::string& filename) {
            return fossil_jellyfish_export_memory(&ai_, filename.c_str());
        }

        /**
         * @brief Import memory into the AI from a file.
         *
         * @param filename Name of the file to import from.
         * @return true if successful, false otherwise.
         */
        bool import_memory(const std::string& filename) {
            return fossil_jellyfish_import_memory(&ai_, filename.c_str());
        }

        /**
         * @brief Get the current number of memories stored.
         *
         * @return Number of memories stored.
         */
        int memory_count() {
            return fossil_jellyfish_memory_count(&ai_);
        }

        /**
         * @brief Remove a memory entry by key.
         *
         * @param key Key string to identify the memory.
         * @return true if successful, false otherwise.
         */
        bool remove_memory(const std::string& key) {
            return fossil_jellyfish_remove_memory(&ai_, key.c_str());
        }

        /**
         * @brief List all memory keys.
         *
         * @return Vector of all memory keys.
         */
        std::vector<std::string> list_memory_keys() {
            char keys[MAX_MEMORY_SIZE][MAX_INPUT_SIZE] = {{0}};
            int count = fossil_jellyfish_list_memory_keys(&ai_, keys, MAX_MEMORY_SIZE);
            std::vector<std::string> result;
            for (int i = 0; i < count; ++i) {
                result.emplace_back(keys[i]);
            }
            return result;
        }

        /**
         * @brief Get the AI's current context.
         *
         * @return The context string of the AI.
         */
        std::string get_context() {
            const char* context = fossil_jellyfish_get_context(&ai_);
            return context ? std::string(context) : std::string();
        }

        /**
         * @brief Get the AI's current personality.
         *
         * @return The personality string of the AI.
         */
        std::string get_personality() {
            const char* personality = fossil_jellyfish_get_personality(&ai_);
            return personality ? std::string(personality) : std::string();
        }

        /**
         * @brief Check if the AI is initialized.
         *
         * @return true if initialized, false otherwise.
         */
        bool is_initialized() {
            return fossil_jellyfish_is_initialized(&ai_);
        }
    };

} // namespace ai

} // namespace fossil

#endif

#endif /* fossil_fish_FRAMEWORK_H */
