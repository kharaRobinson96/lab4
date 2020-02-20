/*******************************************************************
 * 
 * C code framework for ESOS user-interface (UI) service
 * 
 *    requires the EMBEDDED SYSTEMS target rev. F14
 * 
 * ****************************************************************/
#include <esos_f14ui.h>

#include <esos.h>

#include "esos_pic24.h"

#include <revF14.h>

#include <stdio.h>

#
define MINIMUM_LED_FLASH_PERIOD 100# define DEBOUNCE_PERIOD 15

_st_esos_uiF14Data_t _st_esos_uiF14Data;

// PRIVATE FUNCTIONS
inline void _esos_uiF14_setRPGCounter(int16_t i16_newValue) {
  _st_esos_uiF14Data.i16_RPGCounter = i16_newValue;
}
inline int16_t _esos_uiF14_getLastRPGCounter(void) {
  return (_st_esos_uiF14Data.i16_lastRPGCounter);
}
inline void _esos_uiF14_setLastRPGCounter(int16_t i16_newRPGCounter) {
  _st_esos_uiF14Data.i16_lastRPGCounter = i16_newRPGCounter;
}
inline uint16_t _esos_uiF14_getRPGPeriod(void) {
  return (_st_esos_uiF14Data.u16_RPGPeriodMs);
}

// PUBLIC SWITCH FUNCTIONS
inline BOOL esos_uiF14_isSW1Pressed(void) {
  return (_st_esos_uiF14Data.b_SW1Pressed == TRUE);
}

inline BOOL esos_uiF14_isSW1Released(void) {
  return (_st_esos_uiF14Data.b_SW1Pressed == FALSE);
}

inline BOOL esos_uiF14_isSW1DoublePressed(void) {
  if (_st_esos_uiF14Data.b_SW1DoublePressed == TRUE) {
    _st_esos_uiF14Data.b_SW1DoublePressed = FALSE;
    return TRUE;
  } else {
    return FALSE;
  }
}

inline BOOL esos_uiF14_isSW2Pressed(void) {
  return (_st_esos_uiF14Data.b_SW2Pressed == TRUE);
}

inline BOOL esos_uiF14_isSW2Released(void) {
  return (_st_esos_uiF14Data.b_SW2Pressed == FALSE);
}

inline BOOL esos_uiF14_isSW2DoublePressed(void) {
  if (_st_esos_uiF14Data.b_SW2DoublePressed == TRUE) {
    _st_esos_uiF14Data.b_SW2DoublePressed = FALSE;
    return TRUE;
  } else {
    return FALSE;
  }
}

inline BOOL esos_uiF14_isSW3Pressed(void) {
  return (_st_esos_uiF14Data.b_SW3Pressed == TRUE);
}

inline BOOL esos_uiF14_isSW3Released(void) {
  return (_st_esos_uiF14Data.b_SW3Pressed == FALSE);
}

inline BOOL esos_uiF14_isSW3DoublePressed(void) {
  if (_st_esos_uiF14Data.b_SW3DoublePressed == TRUE) {
    _st_esos_uiF14Data.b_SW3DoublePressed = FALSE;
    return TRUE;
  } else {
    return FALSE;
  }
}

// PUBLIC LED FUNCTIONS
inline BOOL esos_uiF14_isLED1On(void) {
  return (_st_esos_uiF14Data.b_LED1On);
}

inline BOOL esos_uiF14_isLED1Off(void) {
  return (_st_esos_uiF14Data.b_LED1On);
}

inline void esos_uiF14_turnLED1On(void) {
  _st_esos_uiF14Data.b_LED1On = TRUE;
  return;
}

inline void esos_uiF14_turnLED1Off(void) {
  _st_esos_uiF14Data.b_LED1On = FALSE;
  return;
}

inline void esos_uiF14_toggleLED1(void) {
  _st_esos_uiF14Data.b_LED1On ^= 1;
  return;
}

inline void esos_uiF14_flashLED1(uint16_t u16_period1) {
  //Choose a reasonable minimum period
  if (u16_period1 < MINIMUM_LED_FLASH_PERIOD) {
    u16_period1 = MINIMUM_LED_FLASH_PERIOD;
  }
  _st_esos_uiF14Data.u16_LED1FlashPeriod = u16_period1;
  return;
}

inline uint16_t esos_uiF14_getLED1Period(void) {
  return _st_esos_uiF14Data.u16_LED1FlashPeriod;
}

inline BOOL esos_uiF14_isLED2On(void) {
  return (_st_esos_uiF14Data.b_LED2On);
}

inline BOOL esos_uiF14_isLED2Off(void) {
  return (_st_esos_uiF14Data.b_LED2On);
}

inline void esos_uiF14_turnLED2On(void) {
  _st_esos_uiF14Data.b_LED2On = TRUE;
  return;
}

inline void esos_uiF14_turnLED2Off(void) {
  _st_esos_uiF14Data.b_LED2On = FALSE;
  return;
}

inline void esos_uiF14_toggleLED2(void) {
  _st_esos_uiF14Data.b_LED2On ^= 1;
  return;
}

inline void esos_uiF14_flashLED2(uint16_t u16_period2) {
  //Choose a reasonable minimum period
  if (u16_period2 < MINIMUM_LED_FLASH_PERIOD) {
    u16_period2 = MINIMUM_LED_FLASH_PERIOD;
  }
  _st_esos_uiF14Data.u16_LED2FlashPeriod = u16_period2;
  return;
}

inline uint16_t esos_uiF14_getLED2Period(void) {
  return _st_esos_uiF14Data.u16_LED2FlashPeriod;
}

inline BOOL esos_uiF14_isLED3On(void) {
  return (_st_esos_uiF14Data.b_LED3On);
}

inline BOOL esos_uiF14_isLED3Off(void) {
  return (_st_esos_uiF14Data.b_LED3On);
}

inline void esos_uiF14_turnLED3On(void) {
  //LED3 is low active
  _st_esos_uiF14Data.b_LED3On = TRUE;
  return;
}

inline void esos_uiF14_turnLED3Off(void) {
  _st_esos_uiF14Data.b_LED3On = FALSE;
  return;
}

inline void esos_uiF14_toggleLED3(void) {
  _st_esos_uiF14Data.b_LED3On ^= 1;
  return;
}

inline void esos_uiF14_flashLED3(uint16_t u16_period3) {
  //Choose a reasonable minimum period
  if (u16_period3 < MINIMUM_LED_FLASH_PERIOD) {
    u16_period3 = MINIMUM_LED_FLASH_PERIOD;
  }
  _st_esos_uiF14Data.u16_LED3FlashPeriod = u16_period3;
  return;
}

inline uint16_t esos_uiF14_getLED3Period(void) {
  return _st_esos_uiF14Data.u16_LED3FlashPeriod;
}

/****** RED, GREEN, and YELLOW functions *******/

inline void esos_uiF14_turnRedLEDOn(void) {
  //Red LED is LED1
  esos_uiF14_turnLED1On();
}

inline void esos_uiF14_turnRedLEDOff(void) {
  esos_uiF14_turnLED1Off();
}

inline void esos_uiF14_turnGreenLEDOn(void) {
  //Green LED is LED3
  esos_uiF14_turnLED3On();
}

inline void esos_uiF14_turnGreenLEDOff(void) {
  esos_uiF14_turnLED3Off();
}

inline void esos_uiF14_turnYellowLEDOn(void) {
  //Yellow LED is LED2
  esos_uiF14_turnLED2On();
}

inline void esos_uiF14_turnYellowLEDOff(void) {
  esos_uiF14_turnLED2Off();
}

// PUBLIC RPG FUNCTIONS

inline int16_t esos_uiF14_getRPGCounter_i16(void) {
  return _st_esos_uiF14Data.i16_RPGCounter;
}

inline BOOL esos_uiF14_isRPGTurning(void) {
  return !(_st_esos_uiF14Data.b_RPGNotMoving);
}

inline BOOL esos_uiF14_isRPGTurningSlow(void) {
  return _st_esos_uiF14Data.b_RPGSlow;
}

inline BOOL esos_uiF14_isRPGTurningMedium(void) {
  return _st_esos_uiF14Data.b_RPGMedium;
}

inline BOOL esos_uiF14_isRPGTurningFast(void) {
  return _st_esos_uiF14Data.b_RPGFast;
}

inline BOOL esos_uiF14_isRPGTurningCW(void) {
  return _st_esos_uiF14Data.b_RPGCW;
}

inline BOOL esos_uiF14_isRPGTurningCCW(void) {
  return _st_esos_uiF14Data.b_RPGCCW;
}

inline uint16_t esos_uiF14_getRPGPeriod(void) {
  return _st_esos_uiF14Data.u16_RPGPeriodMs;
}

inline void esos_uiF14_setDoublePressPeriod(uint16_t limit) {
  _st_esos_uiF14Data.u16_doublePressUpperMs = limit;
  return;
}

inline void esos_uiF14_setRPGNotMovingToSlowPeriodMs(uint16_t time) {
  _st_esos_uiF14Data.u16_RPGNotMovingToSlowPeriodMs = time;
}

inline void esos_uiF14_setRPGSlowToMediumPeriodMs(uint16_t time) {
  _st_esos_uiF14Data.u16_RPGSlowToMediumPeriodMs = time;
}

inline void esos_uiF14_setRPGMediumToFastPeriodMs(uint16_t time) {
  _st_esos_uiF14Data.u16_RPGMediumToFastPeriodMs = time;
}

// UIF14 task to manage user-interface
ESOS_USER_TASK(__esos_uiF14_task) {
  static uint16_t LED1_counter = 0;
  static uint16_t LED2_counter = 0;
  static uint16_t LED3_counter = 0;

  static BOOL SW1_is_debouncing = 0;
  static BOOL SW1_can_doublepress = FALSE;
  static uint16_t SW1_debounce_counter = 0;

  static BOOL SW2_is_debouncing = 0;
  static BOOL SW2_can_doublepress = FALSE;
  static uint16_t SW2_debounce_counter = 0;

  static BOOL SW3_is_debouncing = 0;
  static BOOL SW3_can_doublepress = FALSE;
  static uint16_t SW3_debounce_counter = 0;

  // init to -1 to disable counters by default
  static int SW1_doublepress_counter = 0;
  static int SW2_doublepress_counter = 0;
  static int SW3_doublepress_counter = 0;

  ESOS_TASK_BEGIN();
  while (TRUE) {

    //printf("run through\N");

    //-------- LED Initial States
    // LED1 (Red) 
    LED1 = _st_esos_uiF14Data.b_LED1On;

    // LED2 (Yellow) 
    LED2 = _st_esos_uiF14Data.b_LED2On;

    // LED3 (Green)    
    LED3 = _st_esos_uiF14Data.b_LED3On;

    //-------- LED flashing ---------
    // For some reason the lab stipulates that the flashing functionality
    // be defined WHOLLY in this task, hence the ugly stuff which follows.
    // This operates on the assumption that this ESOS task is called
    // approximately every 10 ms

    //LEDs should not flash when their flashing period is 0
    if (esos_uiF14_getLED1Period() == 0) {
      LED1_counter = 0;
    } else if (LED1_counter < esos_uiF14_getLED1Period() / 2) { //Count up to half period
      LED1_counter += __ESOS_UIF14_UI_PERIOD_MS;
    } else if (LED1_counter >= esos_uiF14_getLED1Period() / 2) { //Toggle when greater than half period
      esos_uiF14_toggleLED1();
      LED1_counter = 0;
    }

    if (esos_uiF14_getLED2Period() == 0) {
      LED2_counter = 0;
    } else if (LED2_counter < esos_uiF14_getLED2Period() / 2) {
      LED2_counter += __ESOS_UIF14_UI_PERIOD_MS;
    } else if (LED2_counter >= esos_uiF14_getLED2Period() / 2) {
      esos_uiF14_toggleLED2();
      LED2_counter = 0;
    }

    if (esos_uiF14_getLED3Period() == 0) {
      LED3_counter = 0;
    } else if (LED3_counter < esos_uiF14_getLED3Period() / 2) {
      LED3_counter += __ESOS_UIF14_UI_PERIOD_MS;
    } else if (LED3_counter >= esos_uiF14_getLED3Period() / 2) {
      esos_uiF14_toggleLED3();
      LED3_counter = 0;
    }

    //SW1
    if (SW1_is_debouncing) {

      //Debouncing switch
      if (SW1_debounce_counter < DEBOUNCE_PERIOD) {
        SW1_debounce_counter += __ESOS_UIF14_UI_PERIOD_MS;

        //Switch done debouncing
      } else if (SW1_debounce_counter >= DEBOUNCE_PERIOD) {
        SW1_debounce_counter = 0;
        _st_esos_uiF14Data.b_SW1Pressed = SW1_PRESSED;
        SW1_is_debouncing = FALSE;

        if (_st_esos_uiF14Data.b_SW1DoublePressed && SW1_PRESSED) {
          _st_esos_uiF14Data.b_SW1DoublePressed = FALSE;
        }
      }
    }

    if (SW1_can_doublepress) {
      if (SW1_doublepress_counter < _st_esos_uiF14Data.u16_doublePressUpperMs) {
        SW1_doublepress_counter += __ESOS_UIF14_UI_PERIOD_MS;
      } else {
        SW1_doublepress_counter = 0;
        SW1_can_doublepress = FALSE;
      }
    }

    //On a button state change event
    if (SW1_PRESSED != esos_uiF14_isSW1Pressed()) {

      //If the switch is pressed, start the debounce timer
      if (SW1_PRESSED) {
        if (!SW1_is_debouncing) {
          SW1_is_debouncing = TRUE;
        } else if (SW1_can_doublepress) {
          _st_esos_uiF14Data.b_SW1DoublePressed = TRUE;
          SW1_can_doublepress = FALSE;
        }

        //Doublepresses are only possible when the switch is released
      } else if (SW1_RELEASED && !SW1_is_debouncing) {
        _st_esos_uiF14Data.b_SW1Pressed = FALSE;
        SW1_can_doublepress = TRUE;
      }
    }

    //SW2
    if (SW2_is_debouncing) {
      if (SW2_debounce_counter < DEBOUNCE_PERIOD) {
        SW2_debounce_counter += __ESOS_UIF14_UI_PERIOD_MS;
      } else if (SW2_debounce_counter >= DEBOUNCE_PERIOD) {
        SW2_debounce_counter = 0;
        _st_esos_uiF14Data.b_SW2Pressed = SW2_PRESSED;
        SW2_is_debouncing = FALSE;

        if (_st_esos_uiF14Data.b_SW2DoublePressed && SW2_PRESSED) {
          _st_esos_uiF14Data.b_SW2DoublePressed = FALSE;
        }
      }
    }

    if (SW2_can_doublepress) {
      if (SW2_doublepress_counter < _st_esos_uiF14Data.u16_doublePressUpperMs) {
        SW2_doublepress_counter += __ESOS_UIF14_UI_PERIOD_MS;
      } else {
        SW2_doublepress_counter = 0;
        SW2_can_doublepress = FALSE;
      }
    }

    //On a button state change event
    if (SW2_PRESSED != esos_uiF14_isSW2Pressed()) {

      //If the switch is pressed, start the debounce timer
      if (SW2_PRESSED) {
        if (!SW2_is_debouncing) {
          SW2_is_debouncing = TRUE;
        } else if (SW2_can_doublepress) {
          _st_esos_uiF14Data.b_SW2DoublePressed = TRUE;
          SW2_can_doublepress = FALSE;
        }

        //Doublepresses are only possible when the switch is released
      } else if (SW2_RELEASED && !SW2_is_debouncing) {
        _st_esos_uiF14Data.b_SW2Pressed = FALSE;
        SW2_can_doublepress = TRUE;
      }
    }

    //SW3
    if (SW3_is_debouncing) {
      if (SW3_debounce_counter < DEBOUNCE_PERIOD) {
        SW3_debounce_counter += __ESOS_UIF14_UI_PERIOD_MS;
      } else if (SW3_debounce_counter >= DEBOUNCE_PERIOD) {
        SW3_debounce_counter = 0;
        _st_esos_uiF14Data.b_SW3Pressed = SW3_PRESSED;
        SW3_is_debouncing = FALSE;

        if (_st_esos_uiF14Data.b_SW3DoublePressed && SW3_PRESSED) {
          _st_esos_uiF14Data.b_SW3DoublePressed = FALSE;
        }
      }
    }

    if (SW3_can_doublepress) {
      if (SW3_doublepress_counter < _st_esos_uiF14Data.u16_doublePressUpperMs) {
        SW3_doublepress_counter += __ESOS_UIF14_UI_PERIOD_MS;
      } else {
        SW3_doublepress_counter = 0;
        SW3_can_doublepress = FALSE;
      }
    }

    //On a button state change event
    if (SW3_PRESSED != esos_uiF14_isSW3Pressed()) {

      //If the switch is pressed, start the debounce timer
      if (SW3_PRESSED) {
        if (!SW3_is_debouncing) {
          SW3_is_debouncing = TRUE;
        } else if (SW3_can_doublepress) {
          _st_esos_uiF14Data.b_SW3DoublePressed = TRUE;
          SW3_can_doublepress = FALSE;
        }

        //Doublepresses are only possible when the switch is released
      } else if (SW3_RELEASED && !SW3_is_debouncing) {
        _st_esos_uiF14Data.b_SW3Pressed = FALSE;
        SW3_can_doublepress = TRUE;
      }
    }

    //+++++++++++++++RPG++++++++++++++++++++
    //determines if RPG is moving
    if (RPGA != _st_esos_uiF14Data.b_RPGALast) {
      _st_esos_uiF14Data.b_RPGALast = RPGA;

      //determine CW or CCW; remember RPGA just changed
      if ((RPGA == 0 && RPGB == 1) || (RPGA == 1 && RPGB == 0)) {
        _st_esos_uiF14Data.b_RPGCW = TRUE;
        _st_esos_uiF14Data.b_RPGCCW = FALSE;
      } else {
        _st_esos_uiF14Data.b_RPGCW = FALSE;
        _st_esos_uiF14Data.b_RPGCCW = TRUE;
      }

      //update the counter 
      if (_st_esos_uiF14Data.b_RPGCW) {
        _st_esos_uiF14Data.i16_RPGCounter += 1;
      }
      if (_st_esos_uiF14Data.b_RPGCCW) {
        _st_esos_uiF14Data.i16_RPGCounter -= 1;
      }

    }

    ESOS_TASK_WAIT_TICKS(__ESOS_UIF14_UI_PERIOD_MS);
  }
  ESOS_TASK_END();
}

// UIF14 INITIALIZATION FUNCTION
void config_esos_uiF14() {

  _st_esos_uiF14Data.b_SW1Pressed = FALSE;
  _st_esos_uiF14Data.b_SW1DoublePressed = FALSE;
  _st_esos_uiF14Data.b_SW2Pressed = FALSE;
  _st_esos_uiF14Data.b_SW2DoublePressed = FALSE;
  _st_esos_uiF14Data.b_SW3Pressed = FALSE;
  _st_esos_uiF14Data.b_SW3DoublePressed = FALSE;
  _st_esos_uiF14Data.u16_doublePressUpperMs = 350;

  _st_esos_uiF14Data.b_RPGALast = FALSE; // compared to current RPGA, used to detect rotation
  _st_esos_uiF14Data.b_RPGFast = FALSE;
  _st_esos_uiF14Data.b_RPGMedium = FALSE;
  _st_esos_uiF14Data.b_RPGSlow = FALSE;
  _st_esos_uiF14Data.b_RPGNotMoving = TRUE;
  _st_esos_uiF14Data.u16_RPGLastChangeMs = 0; //time of last RPGA change
  _st_esos_uiF14Data.u16_RPGPeriodMs = 0; // time SINCE last RPGA change
  _st_esos_uiF14Data.u16_RPGNotMovingToSlowPeriodMs = 600; //border between not moving and slow
  _st_esos_uiF14Data.u16_RPGSlowToMediumPeriodMs = 400;
  _st_esos_uiF14Data.u16_RPGMediumToFastPeriodMs = 100;
  _st_esos_uiF14Data.b_RPGCW = FALSE;
  _st_esos_uiF14Data.b_RPGCCW = FALSE;
  _st_esos_uiF14Data.i16_RPGCounter = 0; // notice signed int for couting CCW from start
  _st_esos_uiF14Data.i16_lastRPGCounter = 0;
  _st_esos_uiF14Data.b_RPGCWRev = FALSE;
  _st_esos_uiF14Data.b_RPGCCWRev = FALSE;

  _st_esos_uiF14Data.b_LED1On = FALSE;
  _st_esos_uiF14Data.b_LED1Flashing = FALSE;
  _st_esos_uiF14Data.u16_LED1FlashPeriod = FALSE;

  _st_esos_uiF14Data.b_LED2On = FALSE;
  _st_esos_uiF14Data.b_LED2Flashing = FALSE;
  _st_esos_uiF14Data.u16_LED2FlashPeriod = FALSE;

  _st_esos_uiF14Data.b_LED3On = FALSE;
  _st_esos_uiF14Data.b_LED3Flashing = FALSE;
  _st_esos_uiF14Data.u16_LED3FlashPeriod = FALSE;

  //Step 1: setup LEDs
  //
  CONFIG_LED1();
  CONFIG_LED2();
  CONFIG_LED3();

  //Step 2: setup switches
  CONFIG_SW1();
  CONFIG_SW2();
  CONFIG_SW3();

  //Step 3: setup RPG
  CONFIG_RPG();

  esos_RegisterTask(__esos_uiF14_task);
}