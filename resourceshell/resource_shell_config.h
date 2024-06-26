#pragma once

// Size of the input command buffer
#define RESOURCE_SHELL_INPUT_SIZE 64
// Size of the output response buffer
#define RESOURCE_SHELL_OUTPUT_SIZE 1024
// Maximum number of arguments in the input
#define RESOURCE_SHELL_MAX_ARGS 10
// Size of command history buffer (recall previous commands with `!`)
#define RESOURCE_SHELL_COMMAND_HISTORY_LENGTH 1
// Size of the shared general purpose array used by command handlers
#define RESOURCE_SHELL_TEMP_ARRAY_SIZE (RESOURCE_SHELL_INPUT_SIZE * 2)
// Define this to include help strings into the executable
#define RESOURCE_SHELL_ENABLE_HELP
