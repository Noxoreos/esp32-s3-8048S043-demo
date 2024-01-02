/// Author: Noxoreos
/// File: main.cpp

#define LGFX_PRINTF_ENABLED
#include "main.h"

LGFX_8048S043 lcd;

// Buffer to draw everything to
LGFX_Sprite canvas(&lcd);

char buf[256];

// Variables to limit framerate
ulong lastTime;
ulong currentTime;

// Variables to compute FPS count
ulong frameCountResetTime;
uint16_t frameCount = 0;
uint16_t fps = 0;

// -----------------------------------------------------------------------------

void setup(void)
{
  // Uncomment this to use serial monitor.
  // See "platformio.ini" for MONITOR_SPEED -> defaults to baud 115200bps.
  // Serial.begin(MONITOR_SPEED);
  // Serial.println("Screen demo: 8048S043");

  // Initialize the display panel itself
  lcd.init();

  lcd.setColorDepth(16);  // 16 bit is the maximum of the screen and the default
  lcd.setBrightness(128); // about half brightness

  // This is only used for unbuffered text output
  lcd.setFont(&fonts::FreeSans18pt7b);
  lcd.setTextColor(TFT_MAGENTA);

  // Handle all write actions in one write cycle
  lcd.startWrite();
  lcd.clearDisplay(TFT_BLACK);

  sprintf((char*) buf, "... Touchscreen calibration ...\n");
  lcd.setTextDatum(lgfx::ML_DATUM); // same as middle_left
  // Center text manually because CC_DATUM and MC_DATUM don't behave properly
  lcd.setCursor(
    (lcd.width() >> 1) - (lcd.textWidth(buf) >> 1),
    lcd.height() >> 1
  );

  lcd.println(buf);
  lcd.endWrite();

  // Calibrate the touch panel to properly match the display
  lcd.calibrateTouch<uint32_t>(nullptr, TFT_WHITE, TFT_BLACK, 50);

  // Finally reset the screen to avoid issues when using transparency
  lcd.startWrite();
  lcd.clearDisplay(TFT_BLACK);
  lcd.endWrite();

  // Set up the draw buffer
  canvas.setColorDepth(16);

  // DMA, which would be default can't be used as it is not big enough
  // Using PSRAM instead. But it comes with a performance hit because
  // communication to PSRAM is done via SPI. The screen itself could be
  // much faster because it's connected in parallel.
  canvas.setPsram(true);

  // Cover the whole screen size
  canvas.createSprite(lcd.width(), lcd.height());

  // Use the same font and font color for the whole demo
  canvas.setFont(&fonts::FreeSans18pt7b);
  canvas.setTextColor(TFT_MAGENTA);

  lastTime = millis();
  frameCountResetTime = lastTime;
} // void setup();

// -----------------------------------------------------------------------------

// Max 5 touches supported by this screen
lgfx::v1::touch_point_t touchPoints[5];

void loop(void)
{
  // Limit framerate to 30fps (probably won't do much)
  currentTime = millis();

  if (currentTime - frameCountResetTime > 1000) {
    fps = frameCount;
    frameCount = 0;
    frameCountResetTime = currentTime;
  } else {
    frameCount++;
  }

  if (currentTime - lastTime > 1000 / 30) {
    lastTime = currentTime;

    canvas.startWrite();
    canvas.clear(TFT_BLACK);

    uint16_t centerX = (canvas.width() >> 1);
    uint16_t centerY = canvas.height() >> 1;

    // Start out with the rectangle in the middle and move right
    static int x = centerX;
    static int dir = 1;

    // This causes the rectangle to move right and left unless touched
    // -> Touch with two or more fingers to reset back to moving
    auto res = lcd.getTouch(touchPoints, 2);
    if (res > 1 && dir == 0) {
      dir = 1;
      x = centerX;
    } else if (1 == res) {
      // Stop moving when touched and instead place rectangle on touched-x
      dir = 0;
      x = touchPoints->x;
    } else {
      x += dir * 1;
      if (x >= 600 || x <= 200) {
        dir = -dir;
      }
    }

    // Draw the moving demo rectangle and a "center-crosshair"
    canvas.fillRect(x - 100, centerY - 80, 200, 160, TFT_RED);
    canvas.drawFastHLine(x - 100, centerY - 0, 200, TFT_WHITE);
    canvas.drawFastHLine(x - 100, centerY - 1, 200, TFT_WHITE);
    canvas.drawFastVLine(x - 0, centerY - 80, 160, TFT_WHITE);
    canvas.drawFastVLine(x - 1, centerY - 80, 160, TFT_WHITE);

    // Output center position of the moving demo rectangle
    canvas.setTextDatum(lgfx::top_left); // defines the origin point of the tet
    canvas.setCursor( // setCursor is required for text output with println
      x,
      centerY
    );
    sprintf((char*) buf, "x = %d", x);
    canvas.println(buf);

    // Output some test-text with a different background
    canvas.fillRect(0, 0, canvas.width(), canvas.fontHeight(), TFT_CYAN);
    canvas.setTextDatum(lgfx::bottom_left);
    canvas.drawString("_ __|- Test-Text 1 -|__ _", 0, canvas.fontHeight());

    // Output more test-text with a different background - using println instead
    canvas.fillRect(
      0,
      canvas.fontHeight(),
      canvas.width(),
      canvas.fontHeight(),
      TFT_LIGHTGREY
    );
    canvas.setTextDatum(  // use a different origin this time
      lgfx::bottom_center // centering seems not to work on the selected font
    );
    sprintf((char*) buf, "Test-Text 2 -> Centered");
    canvas.setCursor( // output in the center of the canvas
      centerX - (canvas.textWidth(buf) >> 1), // manually adjust to the center
      canvas.fontHeight() * 2 // place this new text right below the first line
    );
    canvas.println(buf);

    // Display the font size in the bottom left corner of the screen
    canvas.setTextDatum(
      lgfx::bottom_left // this tells where the text origin is, not position
    );
    sprintf((char*) buf, "Font height: %d pixels\n", canvas.fontHeight());
    canvas.drawString( // this defines the bottom left coordinates of the screen
      (char*) buf,
      0,
      canvas.height() - 1
    );

    // Try to determine the width of a text
    canvas.setTextDatum(
      lgfx::bottom_left // this tells where the text origin is, not position
    );
    sprintf(
      (char*) buf,
      "Text width of \"test\": %d pixels\n",
      canvas.textWidth("test")
    );
    canvas.drawString( // this defines the bottom left coordinates of the screen
      (char*) buf,
      0,
      canvas.height() - canvas.fontHeight() - 1 // second to last line
    );

    // Show PSRAM info - show below the other test texts with a 10 px gap above
    sprintf(
      (char*) buf,
      "PSRAM-Size: %.02f MB\nFree PSRAM: %.02f MB\n",
      (float) ESP.getPsramSize() / (1024.0f * 1024.0f),
      (float) ESP.getFreePsram() / (1024.0f * 1024.0f)
    );
    canvas.setTextDatum(lgfx::top_left);
    canvas.setCursor(0, canvas.fontHeight() * 2 + 10);
    canvas.print(buf); // This will honor the \n character in the text!

    // Print FPS to the bottom right of the screen
    sprintf((char*) buf, "FPS: %03d", fps);
    canvas.setTextDatum(lgfx::bottom_left); // should normally be bottom_right
    canvas.setCursor( // bottom_right alignment won't work, so position manually
      canvas.width() - canvas.textWidth(buf) - 1, // calculate right alignment
      canvas.height() - 1
    );
    canvas.println(buf);

    // Some demo code for multi-touch (up to 5 fingers)
    // This simply gets all touches at once and prints out their positions
    // auto res = lcd.getTouchRaw(touchPoints, 5);
    // for (byte i = 0; i < 5; i++) {}
    //   sprintf((char*) buf, "Count: %d / Tx: %d / Ty: %d / (id|tid: %d|%d) /
    //   size: %d", res, touchPoints[i].x, touchPoints[i].y, touchPoints[i].id,
    //   i + 1, touchPoints[i].size);

    //   canvas.setTextDatum(lgfx::top_left);
    //   canvas.setCursor(0, 200 + i * canvas.fontHeight());
    //   canvas.println(buf);
    // }

    // Finally push the contents of the draw buffer to the lcd panel
    // This almost eliminates screen flicker
    canvas.endWrite();
    canvas.pushSprite(0, 0, TFT_GREEN); // Use green as color key (transparent)
  }
} // void loop();
