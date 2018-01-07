#ifndef __Relay_h_
#define __Relay_h_

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

static const bool flash_program[] = {
  false,true,true,true,false
};

class Relay
{
  public:
    Relay(uint8_t pin, bool on_is_high = true):
      m_pin(pin),
      m_on_is_high(on_is_high),
      m_state(false),
      m_program(NULL),
      m_frame(0)
    {
      pinMode(m_pin, OUTPUT);
      off();
    };
    
    ~Relay()
    {
      pinMode(m_pin, OUTPUT);
      digitalWrite(m_pin, LOW);
    };

    Relay(const Relay & rhs)
    {
      *this = rhs;
    };
    
    Relay & operator=(const Relay & rhs)
    {
      if( this != &rhs )
      {
        this->m_pin = rhs.m_pin;
      }
        
      return *this;
    };

    uint8_t pin() const
    {
      return m_pin;
    };
    
    void on()
    {
      m_program = NULL;
      state(true);
    }
    
    void off()
    {
      m_program = NULL;
      state(false);
    }
    
    void state(bool on)
    {
      if( m_on_is_high )
      {
        m_state = on;
      }
      else
      {
        m_state = !on;        
      }
          
      digitalWrite(m_pin, m_state);
    }

    uint8_t state() const
    {
      bool on;
      
      if( m_on_is_high )
      {
        on = m_state;
      }
      else
      {
        on = !m_state;
      }
      
      return on;
    }
    
    void flash()
    {
      if( m_program == NULL )
      {
        m_program = flash_program;
        m_frame_count = 5;
        m_frame = 0;
      }
    }
  
    void run()
    {     
      if( (m_program != NULL) && (m_frame < m_frame_count) )
      {
        state(m_program[m_frame++]); 
       
        if( m_frame >= m_frame_count )
        {
          m_program = NULL;
        }
      }
    }
    
  private:
    
    uint8_t m_pin;
    bool m_on_is_high;
    bool m_state;
    const bool * m_program;
    uint8_t m_frame;
    uint8_t m_frame_count;
    
    static bool flash_program[5];
};

bool Relay::flash_program[5] = {
  false,true,true,true,false
};

#endif // __Relay_h_
