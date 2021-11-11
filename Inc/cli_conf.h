//
// Created by bronislav on 10.11.21.
//
#ifndef CLI_CLI_CONF_H
#define CLI_CLI_CONF_H

// Include for config.
#include "usart.h"
#include <stdio.h>

//
// Configure macro.
//

// Number of char, that can be written.
#define INPUT_BUFFER_LENGTH 20
// Returns incoming char.
#define GET_CHAR_ASYNC    (USART3->DR)
// Puts char.
#define PUT_CHAR_ASYNC(X) (USART3->DR = X)

#endif //CLI_CLI_CONF_H
