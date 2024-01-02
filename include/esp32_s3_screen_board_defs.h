/// Author: Noxoreos
/// File: esp32_s3_screen_board_defs.h
///
/// Board:
/// - ESP32-8048S043-C_I
/// - ESP32-S3-WROOM-1
/// - 4.3inch Display Board with 800x480px, 8M PSRAM and 16M Flash

// Include guard
#ifndef __ESP32_S3_SCREEN_BOARD_DEFS_H__
#define __ESP32_S3_SCREEN_BOARD_DEFS_H__

// -----------------------------------------------------------------------------
// Remove definitions
// -----------------------------------------------------------------------------

// SPI
#ifdef SPI0_CS
#  undef SPI0_CS
#endif

#ifdef SPI0_MOSI
#  undef SPI0_MOSI
#endif

#ifdef SPI0_CLK
#  undef SPI0_CLK
#endif

#ifdef SPI0_SCK
#  undef SPI0_SCK
#endif

#ifdef SPI0_MISO
#  undef SPI0_MISO
#endif

#ifdef SPI_CS
#  undef SPI_CS
#endif

#ifdef SPI_MOSI
#  undef SPI_MOSI
#endif

#ifdef SPI_CLK
#  undef SPI_CLK
#endif

#ifdef SPI_SCK
#  undef SPI_SCK
#endif

#ifdef SPI_MISO
#  undef SPI_MISO
#endif

#ifdef SPI_CS0
#  undef SPI_CS0
#endif

#ifdef SPI_MOSI0
#  undef SPI_MOSI0
#endif

#ifdef SPI_CLK0
#  undef SPI_CLK0
#endif

#ifdef SPI_SCK0
#  undef SPI_SCK0
#endif

#ifdef SPI_MISO0
#  define SPI_MISO0 13
#endif

// TFT/IPS Panel (Screen)
#ifdef SCREEN_BL
#  undef SCREEN_BL
#endif

// Others (common stuff)
#ifdef LED_BUILTIN
#  undef LED_BUILTIN
#endif

// -----------------------------------------------------------------------------
// Create new definitions
// -----------------------------------------------------------------------------

#define GND GPIO_NUM_NC              // Ground...
#define VDD GPIO_NUM_NC              // 3.3V (3V3)
#define VDD_PULLUP VDD GPIO_NUM_NC   // 3.3V through 10k pullup
#define CHIP_SIGNAL_LINE GPIO_NUM_NC // Signal coming from on board chip

#define SPI0_CS 19
#define SPI_CS SPI0_CS
#define SPI_CS0 SPI0_CS

#define SPI0_MOSI 11
#define SPI_MOSI SPI0_MOSI
#define SPI_MOSI0 SPI0_MOSI

#define SPI0_CLK 12
#define SPI_CLK SPI0_CLK
#define SPI_CLK0 SPI0_CLK

#define SPI0_SCK SPI0_CLK
#define SPI_SCK SPI0_SCK
#define SPI_SCK0 SPI0_SCK

#define SPI0_MISO 13
#define SPI_MISO SPI0_MISO
#define SPI_MISO0 SPI0_MISO

// UART 0 and 1
#define U0TXD GPIO_NUM_43
#define U0RXD GPIO_NUM_44
#define U1TXD GPIO_NUM_17
#define U1RXD GPIO_NUM_18

// ILI9485 ?? --> more like "ili9488" or "st7796"
// All screen pins (4.3 inch) on board (16bit parallel)
#define SCREEN_PIN_1_BL GPIO_NUM_2
#define SCREEN_PIN_2_BL GPIO_NUM_2
#define SCREEN_PIN_3_GND GND
#define SCREEN_VDD VDD
#define SCREEN_24_R0 GND
#define SCREEN_24_R1 GND
#define SCREEN_24_R2 GND
#define SCREEN_24_R3 GPIO_NUM_45
#define SCREEN_24_R4 GPIO_NUM_48
#define SCREEN_24_R5 GPIO_NUM_47
#define SCREEN_24_R6 GPIO_NUM_21
#define SCREEN_24_R7 GPIO_NUM_14
#define SCREEN_24_G0 GND
#define SCREEN_24_G1 GND
#define SCREEN_24_G2 GPIO_NUM_5
#define SCREEN_24_G3 GPIO_NUM_6
#define SCREEN_24_G4 GPIO_NUM_7
#define SCREEN_24_G5 GPIO_NUM_15
#define SCREEN_24_G6 GPIO_NUM_16
#define SCREEN_24_G7 GPIO_NUM_4
#define SCREEN_24_B0 GND
#define SCREEN_24_B1 GND
#define SCREEN_24_B2 GND
#define SCREEN_24_B3 GPIO_NUM_8
#define SCREEN_24_B4 GPIO_NUM_3
#define SCREEN_24_B5 GPIO_NUM_46
#define SCREEN_24_B6 GPIO_NUM_9
#define SCREEN_24_B7 GPIO_NUM_1
#define SCREEN_PIN_29_GND GND
#define SCREEN_DCLK                                                            \
  GPIO_NUM_42 // DCLK/PCLK Connected through a 0ohm resistor called L2
#define SCREEN_PCLK SCREEN_DCLK
#define SCREEN_DISP VDD_PULLUP
#define SCREEN_HSYNC GPIO_NUM_39
#define SCREEN_VSYNC GPIO_NUM_41
#define SCREEN_DE GPIO_NUM_40
#define SCREEN_EN SCREEN_DE
#define SCREEN_NC GPIO_NUM_NC // Not connected
#define SCREEN_36_GND GND
#define SCREEN_X1 CHIP_SIGNAL_LINE // Touch X+
#define SCREEN_Y1 CHIP_SIGNAL_LINE // Touch Y+
#define SCREEN_X2 CHIP_SIGNAL_LINE // Touch X-
#define SCREEN_Y2 CHIP_SIGNAL_LINE // Touch Y-
#define SCREEN_41_GND GND
#define SCREEN_42_GND GND
// 24 bit (R8G8B8) to 16 bit (R5G6B5) color remapping
#define SCREEN_R0 SCREEN_24_R3
#define SCREEN_R1 SCREEN_24_R4
#define SCREEN_R2 SCREEN_24_R5
#define SCREEN_R3 SCREEN_24_R6
#define SCREEN_R4 SCREEN_24_R7
#define SCREEN_G0 SCREEN_24_G2
#define SCREEN_G1 SCREEN_24_G3
#define SCREEN_G2 SCREEN_24_G4
#define SCREEN_G3 SCREEN_24_G5
#define SCREEN_G4 SCREEN_24_G6
#define SCREEN_G5 SCREEN_24_G7
#define SCREEN_B0 SCREEN_24_B3
#define SCREEN_B1 SCREEN_24_B4
#define SCREEN_B2 SCREEN_24_B5
#define SCREEN_B3 SCREEN_24_B6
#define SCREEN_B4 SCREEN_24_B7
// More definitions
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 480
#define SCREEN_BL SCREEN_PIN_1_BL // Both backlight pins are controlled together

// TP / Touch-Panel (GT911 type - capacitive touch panel)
// - (FPC1) via I2C -> on 6 pin FPC connector
#define TP_INT                                                                 \
  GPIO_NUM_18 // Touch Panel "INT" (interrupt signal) is directly connected to
              // GPIO18 through a 0ohm resistor!
#undef TP_INT // NOTE: Not using the INT-pin, see next line
#define TP_INT GPIO_NUM_NC // Define INT pin on the GT911 as unused!
#define TP_MODULE TOUCH_GT911
#define TP_SCL                                                                 \
  GPIO_NUM_20 // TP_SCL is physically connected to GPIO20, 3.3V pull-up!
#define TP_SDA                                                                 \
  GPIO_NUM_19 // TP_SDA is physically connected to GPIO19, 3.3V pull-up!
#define TP_RST GPIO_NUM_38
#define TP_ROTATION ROTATION_NORMAL
#define TP_MAP_X1 480
#define TP_MAP_X2 0
#define TP_MAP_Y1 272
#define TP_MAP_Y2 0
// - There is also a "XPT2046" (U1) Chip via SPI on the board, not sure why, but
// it is connected to the ESP32-S3-module ...
#define TP_CS GPIO_NUM_38 // Touch Panel "/CS" is directly connected to GPIO38!
#define TP_CLK SPI0_CLK
#define TP_BUSY GPIO_NUM_NC
#define TP_DIN SPI0_MOSI
#define TP_OUT SPI0_MISO
#define TP_IRQ                                                                 \
  GPIO_NUM_18 // Touch Panel "/PENIRQ" is directly connected to GPIO18, 3.3V
              // pull-up!

// TF/SD-Card (SPI)
#define TF_CS GPIO_NUM_10 // 3.3V pull-up
#define TF_CLK SPI0_CLK   // CLX
#define TF_CMD SPI0_MOSI  // D-IN, 3.3V pull-up
#define TF_DAT0 SPI0_MISO // D-OUT, 3.3V pull-up
#define TF_DAT1           // NOT CONNECTED, 3.3V pull-up

// Use the screens back light as "built in LED" for "blink-tests"
#define LED_BUILTIN SCREEN_BL

#endif // __ESP32_S3_SCREEN_BOARD_DEFS_H__
