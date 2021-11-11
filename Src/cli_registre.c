
#include "cli_command.h"
#include "stm32f103xe.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * Bellow functions provide commands invoking.
 * They have signature: char name(const char *args);
 * @param
 * args - string parameter, that should be parsed.
 * @returns
 * exit code.
 */

/**
 * The method prints help string.
 *
 * @param args - no uses.
 * @return 0
 */
char help(const char *args)
{
    printf("STM32 CLI, designed by Bronislav\n");
    return 0;
}

/**
 * Implements Software Reset of MCU.
 *
 * @param args - no uses.
 * @return nothing
 */
char reset(const char *args)
{
    NVIC_SystemReset();
    return 0;
}

/**
 * Prints parameters.
 *
 * @param args string to print.
 * @return 0
 */
char echo(const char *args)
{
    printf("%s\n", args);
    return 0;
}

/**
 *  The method switches pin output state.
 *  ports: GPIO[A-G]
 *  pins: [0-15]
 *  state: 1 - set, 0 - reset.
 * @param args switch [A-G][0-15] {0|1}
 * @return 0
 */
char switch_(const char *args)
{
    char port;
    int pin, state;

    if (strstr(args, "-h"))
    {
        printf("switch [A-G][0-15] {0|1}\n set according Port`s pin to state 0 or 1\n");
        return 0;
    }

    if (sscanf(args, "%c%d %d\n", &port, &pin, &state) != 3)
    {
        printf("Wrong number of argument.\n");
        return 1;
    }

    if (state)
        ((GPIO_TypeDef*)(APB2PERIPH_BASE + 0x400 + 0x400 * (port-'A'+1)))->ODR |= 1 << pin;
    else
        ((GPIO_TypeDef*)(APB2PERIPH_BASE + 0x400 + 0x400 * (port-'A'+1)))->ODR &= ~(1 << pin);

    return 0;
}


/**
 * Array of commands with according string names.
 */
cli_command commands[NB_OF_COMMANDS] = {
        {.func = help, .name = "help"},
        {.func = reset, .name = "reset"},
        {.func = echo, .name = "echo"},
        {.func = switch_, .name = "switch"}
};
