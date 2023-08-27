#pragma once

#include "Snake.h"

#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define BORDER 4

void drawGame(Adafruit_SSD1306 display, Game game, int level);
void drawSnake(Adafruit_SSD1306 display, int x, int y);
void drawApple(Adafruit_SSD1306 display, int x, int y);
// void drawLvl(Adafruit_SSD1306 display, int level);
void drawScr(Adafruit_SSD1306 display, int score);
void drawPostScore(Adafruit_SSD1306 display, Game game);
void drawGrid(Adafruit_SSD1306 display, Game game);
void drawByKai(Adafruit_SSD1306 display);
void flashInverted(Adafruit_SSD1306 display);