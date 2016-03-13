#ifndef __Led_Matrix_h_
#define __Led_Matrix_h_

#include "Arduino.h"
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

#define LED_MATRIX_FRAME_INTERVAL 200
#define LED_BUFFER_LENGTH 100

enum MatrixProgram
{
  mpStatic,
  mpScrollLeft,
  mpScrollRight,
  mpScrollUp,
  mpScrollDown,
  mpFlash,
  MatrixProgram_Count
};

class Led_Matrix: public Adafruit_GFX
{
public:
  Led_Matrix(uint16_t width, uint16_t height, uint8_t cols, uint8_t rows, uint16_t buffer_length =
  LED_BUFFER_LENGTH);
  virtual ~Led_Matrix();

  void begin();

  virtual void drawPixel(int16_t x, int16_t y, uint16_t color);

  void clear();
  void writeDisplay();
  void setBrightness(uint8_t b);

  void clearText();
  void addText(const char * text);

  void resetFrame();

  void test();
  void run(MatrixProgram program = mpScrollLeft, uint16_t rate =
  LED_MATRIX_FRAME_INTERVAL);

private:
  Led_Matrix(const Led_Matrix & rhs);
  Led_Matrix & operator=(const Led_Matrix & rhs);

  void drawPixel(Adafruit_LEDBackpack & device, int16_t x, int16_t y, uint16_t color);
  void scroll(int16_t x, int16_t y);

  uint8_t m_rows;
  uint8_t m_cols;
  Adafruit_LEDBackpack ** m_device;
  int16_t m_frame;
  uint32_t m_millis;

  uint16_t m_max_length;
  char * m_text;
};

Led_Matrix & operator<<(Led_Matrix & ledm, const char * string);
Led_Matrix & operator<<(Led_Matrix & ledm, const String & string);
Led_Matrix & operator<<(Led_Matrix & ledm, const __FlashStringHelper * ifsh);
Led_Matrix & operator<<(Led_Matrix & ledm, int16_t number);
Led_Matrix & operator<<(Led_Matrix & ledm, char character);

#endif // __Led_Matrix_h_
