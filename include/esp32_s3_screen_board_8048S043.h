/// Author: Noxoreos
/// File: esp32_s3_screen_board_8048S043.h
///
/// Board:
/// - ESP32-8048S043-C_I
/// - ESP32-S3-WROOM-1
/// - 4.3inch Display Board with 800x480px, 8M PSRAM and 16M Flash
///
/// Additional info:
/// - This file is variation of:
///   https://raw.githubusercontent.com/lovyan03/LovyanGFX/1.1.9/src/lgfx_user/LGFX_ESP32S3_RGB_ESP32-8048S043.h
/// - It is created to handle the user setup, but still use the custom
///   definitions that can be found in "esp32_s3_screen_board_defs.h"
///
/// License: See "LovyanGFX-license.txt" for the license of the original file.

#ifndef __ESP32_S3_SCREEN_BOARD_8048S043_H__
#define __ESP32_S3_SCREEN_BOARD_8048S043_H__

#define LGFX_USE_V1

#include <LovyanGFX.hpp>

#include <lgfx/v1/platforms/esp32s3/Panel_RGB.hpp>
#include <lgfx/v1/platforms/esp32s3/Bus_RGB.hpp>

#include <driver/i2c.h>

#include "esp32_s3_screen_board_defs.h"

class LGFX_8048S043 : public lgfx::LGFX_Device
{
public:
  lgfx::Bus_RGB _bus_instance;
  lgfx::Panel_RGB _panel_instance;
  lgfx::Light_PWM _light_instance;
  lgfx::Touch_GT911 _touch_instance;

  LGFX_8048S043(void)
  {
    {
      auto cfg = _panel_instance.config();

      cfg.memory_width = (uint16_t) SCREEN_WIDTH;
      cfg.memory_height = (uint16_t) SCREEN_HEIGHT;
      cfg.panel_width = (uint16_t) SCREEN_WIDTH;
      cfg.panel_height = (uint16_t) SCREEN_HEIGHT;

      cfg.offset_x = 0;
      cfg.offset_y = 0;

      _panel_instance.config(cfg);
    }

    {
      auto cfg = _panel_instance.config_detail();

      cfg.use_psram = 1;

      _panel_instance.config_detail(cfg);
    }

    {
      auto cfg = _bus_instance.config();
      cfg.panel = &_panel_instance;
      cfg.pin_d0 = SCREEN_B0;
      cfg.pin_d1 = SCREEN_B1;
      cfg.pin_d2 = SCREEN_B2;
      cfg.pin_d3 = SCREEN_B3;
      cfg.pin_d4 = SCREEN_B4;
      cfg.pin_d5 = SCREEN_G0;
      cfg.pin_d6 = SCREEN_G1;
      cfg.pin_d7 = SCREEN_G2;
      cfg.pin_d8 = SCREEN_G3;
      cfg.pin_d9 = SCREEN_G4;
      cfg.pin_d10 = SCREEN_G5;
      cfg.pin_d11 = SCREEN_R0;
      cfg.pin_d12 = SCREEN_R1;
      cfg.pin_d13 = SCREEN_R2;
      cfg.pin_d14 = SCREEN_R3;
      cfg.pin_d15 = SCREEN_R4;

      cfg.pin_henable = SCREEN_EN;
      cfg.pin_vsync = SCREEN_VSYNC;
      cfg.pin_hsync = SCREEN_HSYNC;
      cfg.pin_pclk = SCREEN_PCLK;
      cfg.freq_write = 14000000;

      cfg.hsync_polarity = 0;
      cfg.hsync_front_porch = 8;
      cfg.hsync_pulse_width = 4;
      cfg.hsync_back_porch = 16;
      cfg.vsync_polarity = 0;
      cfg.vsync_front_porch = 4;
      cfg.vsync_pulse_width = 4;
      cfg.vsync_back_porch = 4;
      cfg.pclk_idle_high = 1;
      _bus_instance.config(cfg);
    }
    _panel_instance.setBus(&_bus_instance);

    {
      auto cfg = _light_instance.config();
      cfg.pin_bl = SCREEN_BL;
      _light_instance.config(cfg);
    }
    _panel_instance.light(&_light_instance);

    {
      // GT911 Touch Panel
      auto cfg = _touch_instance.config();
      cfg.x_min = 0;
      cfg.x_max = 800;
      cfg.y_min = 0;
      cfg.y_max = 480;
      // cfg.pin_int = GPIO_NUM_18;
      cfg.bus_shared = false;
      cfg.offset_rotation = 0;
      // I2C接続
      cfg.i2c_port = I2C_NUM_1;
      cfg.pin_sda = TP_SDA;
      cfg.pin_scl = TP_SCL;
      cfg.freq = 400000;
      cfg.i2c_addr = 0x14; // 0x5D , 0x14
      _touch_instance.config(cfg);
      _panel_instance.setTouch(&_touch_instance);
    }

    setPanel(&_panel_instance);
  }

  inline bool setup(
    uint_fast8_t rotation = 1,
    uint8_t brightness = 128,
    int colorDepth = 16)
  {
    if (!this->init()) {
      return false;
    }

    this->setRotation(rotation);
    this->setBrightness(brightness);
    this->setColorDepth(colorDepth);

    return true;
  }
};

#endif // __ESP32_S3_SCREEN_BOARD_8048S043_H__
