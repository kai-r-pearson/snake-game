#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <Snake.h>
// #include <DrawSnakeSSD1306.h>

using namespace std;

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define BORDER 4

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library.
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET -1		// Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Adafruit_SSD1306 *p_display;

int level;
int period;

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

// FUNCTION DECLARATIONS
void drawSnake(int x, int y);
void drawApple(int x, int y);
void drawLvl(int level);
void drawScr(int score);
void drawPostScore(Game game);
void drawGrid(Game game);
void flashInverted(Adafruit_SSD1306 display);

void setup()
{
	Serial.begin(115200);

	// SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
	if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
	{
		Serial.println(F("SSD1306 allocation failed"));
		for (;;)
			; // Don't proceed, loop forever
	}

	// Clear initial display buffer contents --
	// the library initializes this with an Adafruit splash screen.
	display.clearDisplay();

	level = 0;
	period = 1000;
}

void loop()
{
	Game game = newGame();

	while (!game->gameOver)
	{

		char inputChar = 'w';
		drawGrid(game);
		drawLvl(level);
		drawScr(game->length);
		display.display();
		display.clearDisplay();

		tick(inputChar, game);
		delay(40);
	}

	// test test test

  // test github 


	deleteGame(game);
}

void drawSnake(int x, int y) {
  display.fillRect(SIZE*x + 2, SIZE*y + 2, SIZE, SIZE, SSD1306_WHITE);
}
void drawApple(int x, int y) {
  display.drawBitmap(SIZE*x + 2, SIZE*y + 2, bmp_apple, bmp_apple_w, bmp_apple_h, SSD1306_WHITE);
}

void drawLvl(int level) {
  char lvl_x = COLS*SIZE + BORDER;
  char lvl_y = 0;
  char str[4];
  sprintf(str, "%02d", level);
  display.setTextSize(3);
  display.setTextColor(SSD1306_WHITE);
  display.drawBitmap(lvl_x, lvl_y, bmp_lvl, bmp_lvl_w, bmp_lvl_h, SSD1306_WHITE);
  display.setCursor(lvl_x, lvl_y + 6);
  display.write(str);
}

void drawScr(int score) {
  char scr_x = COLS*SIZE + BORDER;
  char scr_y = 32;
  char str[4];
  sprintf(str, "%02d", score);
  display.setTextSize(3);
  display.setTextColor(SSD1306_WHITE);
  display.drawBitmap(scr_x, scr_y, bmp_scr, bmp_scr_w, bmp_scr_h, SSD1306_WHITE);
  display.setCursor(scr_x, scr_y + 6);
  display.write(str);
}

void drawPostScore(Game game) {
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

void drawGrid(Game game) {
  display.drawRect(0, 0, COLS*SIZE + 2, ROWS*SIZE + 2, SSD1306_WHITE);
  display.drawRect(1, 1, COLS*SIZE, ROWS*SIZE, SSD1306_WHITE);

  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      if (game->grid[i][j] > 0) {
        drawSnake(j, i);
      } else if (game->grid[i][j] == APPLE) {
        drawApple(j, i);
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