//
// Created by bronislav on 04.11.21.
//

#include "cli_conf.h"
#include <string.h>
#include "cli_command.h"

// Standard macro.
#define ENTER     0x0D
#define TAB       0x09
#define BACKSPACE 0x7F

// Buffer.
char inputBuffer[INPUT_BUFFER_LENGTH + 1] = {0};
char pointer = 0;
char *prefix = "";
char extString[ALL_COMMAND_LENGTH] = {0};

// External functions.
extern void cli_exec(const char*);
extern char cli_hint(const char*, char*);// Returns nb of available commands.

//

static inline void resetBuffer(void)
{
    // Reset pointer.
    pointer = 0;
    // Reset buffer.
    memset(inputBuffer, 0, INPUT_BUFFER_LENGTH);
}

static inline void initLine(void)
{
    printf("%s#%s", prefix, inputBuffer);
    fflush(stdout);
}

void cli_incomingCharHandler()
{
    char hintRes;
    // Check fulling of buffer.
    if (pointer >= INPUT_BUFFER_LENGTH)
    {
        // If buffer is full, then alert and reset.
        printf("\n!input buffer is full!\n");
        resetBuffer();
    }

    switch (GET_CHAR_ASYNC)
    {
        case ENTER:
            // Go to new line.
            printf("\n");
            // Execute command interpreter.
            cli_exec(inputBuffer);
            // Clean buffer.
            resetBuffer();
            // Initialize line.
            initLine();
            break;

        case BACKSPACE:
            // Check pointer, and remove symbol.
            if (pointer > 0)
            {
                inputBuffer[--pointer] = 0;
                PUT_CHAR_ASYNC(GET_CHAR_ASYNC);
            }
            break;
        case TAB:
            hintRes = cli_hint(inputBuffer, extString);
            if (hintRes == 1)
            {
                strcpy(inputBuffer, extString);
                pointer = strlen(extString);
                printf("\n");
                initLine();
            } else if (hintRes > 1)
            {
                printf("\n%s\n", extString);
                initLine();
            }
            break;
        default:
            // Check incoming symbols.
            if (GET_CHAR_ASYNC < 32 || GET_CHAR_ASYNC > 126)
                return;
            inputBuffer[pointer++] = GET_CHAR_ASYNC;
            PUT_CHAR_ASYNC(GET_CHAR_ASYNC);
            break;
    }
}
