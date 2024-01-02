/// Author: Noxoreos
/// File: main.h

#ifndef __MAIN_H__
#define __MAIN_H__

#include "esp32_s3_screen_board_8048S043.h"

#include <Arduino.h>

// Serial is already used for something else up until here. Therefore ...
// ... override the definition for it to use Serial0 instead
#define Serial Serial0

#endif // __MAIN_H__
