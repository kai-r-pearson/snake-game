#include "DrawSnakeSSD1306.h"

// BITMAPS
// 'apple', 4x4px
const int bmp_apple_w = 4;
const int bmp_apple_h = 4;
const unsigned char bmp_apple [] PROGMEM = {
	0x60, 0xf0, 0xf0, 0x60
};

// 'lvl' 13x4px
const int bmp_lvl_w = 12;
const int bmp_lvl_h = 4;
const unsigned char bmp_lvl [] PROGMEM = {
	0x95, 0x00, 0x95, 0x10, 0x95, 0x00, 0xe9, 0xd0
};

// 'scr', 13x5px
const int bmp_scr_w = 13;
const int bmp_scr_h = 5;
const unsigned char bmp_scr [] PROGMEM = {
	0xee, 0xe0, 0x8a, 0xa8, 0xe8, 0xc0, 0x2a, 0xa8, 0xee, 0xa0
};

// DRAW
void drawGame(Adafruit_SSD1306 display, Game game, int level) {
    drawGrid(display, game);
    // drawLvl(display, level);
    drawScr(display, game->length);
}
void drawSnake(Adafruit_SSD1306 display, int x, int y) {
  display.fillRect(SIZE*x + 2, SIZE*y + 2, SIZE, SIZE, SSD1306_WHITE);
}
void drawApple(Adafruit_SSD1306 display, int x, int y) {
  display.drawBitmap(SIZE*x + 2, SIZE*y + 2, bmp_apple, bmp_apple_w, bmp_apple_h, SSD1306_WHITE);
}

void drawLvl(Adafruit_SSD1306 display, int level) {
  char lvl_x = COLS*SIZE + BORDER;
  char lvl_y = 1;
  char str[4];
  sprintf(str, "%02d", level);
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.drawBitmap(lvl_x, lvl_y, bmp_lvl, bmp_lvl_w, bmp_lvl_h, SSD1306_WHITE);
  display.setCursor(lvl_x, lvl_y + 6);
  display.write(str);
}

void drawScr(Adafruit_SSD1306 display, int score) {
  char scr_x = COLS*SIZE + BORDER;
  char scr_y = 27;
  char str[4];
  sprintf(str, "%02d", score);
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.drawBitmap(scr_x, scr_y, bmp_scr, bmp_scr_w, bmp_scr_h, SSD1306_WHITE);
  display.setCursor(scr_x, scr_y + 6);
  display.write(str);
}

void drawPostScore(Adafruit_SSD1306 display, Game game) {
  // Post game over menu
  char str[4];
  sprintf(str, "%02d", game->length);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(2, display.height()/4);
  display.write("SCORE: ");
  display.setTextSize(2);
  display.setCursor(display.width()/2, 5);
  display.write(str);
}

void drawGrid(Adafruit_SSD1306 display, Game game) {
  display.drawRect(1, 1, COLS*SIZE + 2, ROWS*SIZE + 2, SSD1306_WHITE);

  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      if (game->grid[i][j] > 0) {
        drawSnake(display, j, i);
      } else if (game->grid[i][j] == APPLE) {
        drawApple(display, j, i);
      }
    }
  }
}

void drawByKai(Adafruit_SSD1306 display) {
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(display.width()/4, display.height()/2);
  display.write("by Kai");
}

void flashInverted(Adafruit_SSD1306 display) {
  for(char i = 0; i < 3; i++) {
    display.invertDisplay(true);
    delay(100);
    display.invertDisplay(false);
    delay(100);
  }
}