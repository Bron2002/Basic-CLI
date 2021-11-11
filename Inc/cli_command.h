//
// Created by bronislav on 10.11.21.
//

#ifndef CLI_CLI_COMMAND_H
#define CLI_CLI_COMMAND_H

//
// Structure of command.
//
typedef struct {
    char *name;
    char (*func)(const char *);
} cli_command;

// Number of commands.
#define NB_OF_COMMANDS 4

// Max command length.
#define LENGTH_0F_COMMAND 6

// Summary length of commands names.
#define ALL_COMMAND_LENGTH 23

#endif //CLI_CLI_COMMAND_H
