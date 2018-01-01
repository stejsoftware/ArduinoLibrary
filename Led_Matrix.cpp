#include "Led_Matrix.h"

#define swap(a, b) { int16_t t = a; a = b; b = t; }

Led_Matrix::Led_Matrix(uint16_t width, uint16_t height, uint8_t cols, uint8_t rows, uint16_t buffer_length) :
    Adafruit_GFX(width, height),

    m_rows(rows),
    m_cols(cols),

    m_device(NULL),

    m_frame(0),
    m_millis(0),

    m_max_length(buffer_length),
    m_text(NULL)
{
  m_text = new char[m_max_length];
  memset(m_text, 0, m_max_length);
}

Led_Matrix::~Led_Matrix()
{
  delete[] m_device;
  delete[] m_text;
}

void Led_Matrix::begin()
{
  setTextSize(1);
  setTextWrap(false);     // we don't want text to wrap so it scrolls nicely
  setTextColor(LED_ON);

  m_device = new Adafruit_LEDBackpack*[m_rows];
  uint8_t next_add = 0x70;

  if( m_device != NULL )
  {
    for( uint8_t r = 0; r < m_rows; r++ )
    {
      m_device[r] = new Adafruit_LEDBackpack[m_cols];

      if( m_device[r] != NULL )
      {
        for( uint8_t c = 0; c < m_cols; c++ )
        {
          m_device[r][c].begin(next_add++);
          m_device[r][c].clear();
          m_device[r][c].writeDisplay();
        }
      }
    }
  }
}

void Led_Matrix::drawPixel(int16_t x, int16_t y, uint16_t color)
{
  if( (y < 0) || (y >= height()) )
    return;
  if( (x < 0) || (x >= width()) )
    return;

  uint16_t device_x = (x % 8);
  uint16_t device_y = (y % 8);
  uint8_t col = floor(x / 8);
  uint8_t row = floor(y / 8);

  drawPixel(m_device[row][col], device_x, device_y, color);
}

void Led_Matrix::drawPixel(Adafruit_LEDBackpack & device, int16_t x, int16_t y, uint16_t color)
{
  if( (y < 0) || (y >= 8) )
    return;
  if( (x < 0) || (x >= 8) )
    return;

  // check rotation, move pixel around if necessary
  switch( getRotation() )
  {
  case 1:
    swap(x, y)
    ;
    x = 8 - x - 1;
    break;
  case 2:
    x = 8 - x - 1;
    y = 8 - y - 1;
    break;
  case 3:
    swap(x, y)
    ;
    y = 8 - y - 1;
    break;
  }

  // wrap around the x
  x += 7;
  x %= 8;

  if( color )
  {
    device.displaybuffer[y] |= 1 << x;
  }
  else
  {
    device.displaybuffer[y] &= ~(1 << x);
  }
}

void Led_Matrix::clear()
{
  for( uint8_t r = 0; r < m_rows; r++ )
  {
    for( uint8_t c = 0; c < m_cols; c++ )
    {
      m_device[r][c].clear();
    }
  }
}

void Led_Matrix::writeDisplay()
{
  for( uint8_t r = 0; r < m_rows; r++ )
  {
    for( uint8_t c = 0; c < m_cols; c++ )
    {
      m_device[r][c].writeDisplay();
    }
  }
}

void Led_Matrix::setBrightness(uint8_t b)
{
  for( uint8_t r = 0; r < m_rows; r++ )
  {
    for( uint8_t c = 0; c < m_cols; c++ )
    {
      m_device[r][c].setBrightness(b);
    }
  }
}

void Led_Matrix::test()
{
  for( uint8_t r = 0; r < height(); r++ )
  {
    for( uint8_t c = 0; c < width(); c++ )
    {
      clear();
      drawPixel(c, r, 1);
      writeDisplay();
      delay(50);
    }
  }
}

void Led_Matrix::scroll(int16_t x, int16_t y)
{
  clear();
  setCursor(x, y);
  print(m_text);
  print(" ");
  print(m_text);
}

void Led_Matrix::run(MatrixProgram program, uint16_t rate)
{
  if( (millis() - m_millis) > rate )
  {
    m_millis = millis();

    if( m_text != NULL )
    {
      switch( program )
      {
      case mpScrollLeft:
        scroll(m_frame, 0);
        m_frame--;
        break;

      case mpScrollRight:
        scroll(m_frame, 0);
        m_frame++;
        break;

      case mpScrollUp:
        scroll(0, m_frame);
        m_frame--;
        break;

      case mpScrollDown:
        scroll(0, m_frame);
        m_frame++;
        break;

      case mpStatic:
        clear();
        setCursor(0, 0);
        print(m_text);
        break;
      }

      writeDisplay();

      uint8_t text_width = (strlen(m_text) * 6);

      if( m_frame < (0 - text_width) )
      {
        m_frame = 5;
      }
      else if( m_frame > width() )
      {
        m_frame = (0 - text_width);
      }
    } // endif m_text is not null
  }
}

void Led_Matrix::clearText()
{
  if( m_text != NULL )
  {
    memset(m_text, 0, m_max_length);
  }
}

void Led_Matrix::resetFrame()
{
  m_frame = 0;
}

void Led_Matrix::addText(const char * text)
{
  if( (text != NULL) && (m_text != NULL) )
  {
    uint16_t text_length = strlen(text);
    uint16_t curr_length = strlen(m_text);
    uint16_t bytes_to_copy = min(m_max_length - curr_length - 1, text_length);

    if( bytes_to_copy > 0 )
    {
      strncpy(m_text + curr_length, text, bytes_to_copy);
    }
  }
}

Led_Matrix & operator<<(Led_Matrix & ledm, const char * string)
{
  ledm.addText(string);

  return ledm;
}

Led_Matrix & operator<<(Led_Matrix & ledm, const String & string)
{
  uint8_t length = string.length() + 1;
  char * text = new char[length];

  string.toCharArray(text, length);
  ledm.addText(text);

  delete text;

  return ledm;
}

Led_Matrix & operator<<(Led_Matrix & ledm, const __FlashStringHelper * ifsh)
{
  const char PROGMEM
  * text_P = (const char PROGMEM *)ifsh;
  uint16_t length = strlen_P(text_P) + 1;
  char * text = new char[length];

  strncpy_P(text, text_P, length);
  ledm.addText(text);

  delete text;

  return ledm;
}

Led_Matrix & operator<<(Led_Matrix & ledm, int16_t number)
{
  char text[10] =
  { '\0' };

  snprintf(text, sizeof(text), "%d", number);
  ledm.addText(text);

  return ledm;
}

Led_Matrix & operator<<(Led_Matrix & ledm, char character)
{
  char text[] =
  { character, '\0' };

  ledm.addText(text);

  return ledm;
}
