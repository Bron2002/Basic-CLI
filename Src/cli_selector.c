//
// Created by bronislav on 06.11.21.
//
#include <string.h>
#include <stdio.h>
#include "cli_command.h"
#include "cli_conf.h"

/**
 * Array with commands.
 */
extern cli_command commands[];

/**
 * Array, where will be written command name only.
 */
char *commandOnly[LENGTH_0F_COMMAND];

cli_command *findCommand(const char *name)
{
    for (int i = 0; i < NB_OF_COMMANDS; i++)
    {
        if (strcmp(name, commands[i].name) == 0)
        {
            return &commands[i];
        }
    }

    return NULL;
}

void cli_exec(const char *commandStr)
{
    memset(commandOnly, 0, LENGTH_0F_COMMAND);

    sscanf(commandStr, "%s ", commandOnly);

    cli_command *c = findCommand(commandOnly);
    if (c)
    {
        c->func(&commandStr[strlen(commandOnly) + 1]);
    } else
    {
        printf("Can`t find command \"%s\"\n", commandStr);
    }
}

char cli_hint(const char *commandStr, char *outStr)
{
    char res = 0;
    char shift = 0;
    for (int i = 0; i < NB_OF_COMMANDS; ++i)
    {
        if (strstr(commands[i].name, commandStr) == commands[i].name)
        {
            shift += sprintf(&outStr[shift], "%s ", commands[i].name);
            res++;
        }
    }
    return res;
}
