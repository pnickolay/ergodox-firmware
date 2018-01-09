/* ----------------------------------------------------------------------------
 * Copyright (c) 2012, 2013 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/licenses/MIT.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**                                                                 description
 * Implements the "basic" section of "../key-functions.h"
 */


#include <stdbool.h>
#include <stdint.h>
#include "../../../../firmware/lib/usb.h"
#include "../../../../firmware/lib/usb/usage-page/keyboard.h"
#include "../key-functions.h"

// ----------------------------------------------------------------------------
// keystroke recording for lang switch

typedef struct {
  uint8_t keycode;
  bool shifted;
} stroke_t;

#define MAX_KEYSTROKES 20
stroke_t recent_keys[MAX_KEYSTROKES];
uint8_t recent_key_num = 0;

void key_functions__recent_keys_reset(void) {
  recent_key_num = 0;
}

uint8_t key_functions__recent_keys_length(void) {
  return recent_key_num;
}

void key_functions__recent_keys_add(uint8_t keycode) {
  static uint16_t last_type_time = 0;

  if (last_type_time + 1000 < timer__get_milliseconds())
    key_functions__recent_keys_reset();
  last_type_time = timer__get_milliseconds();

  if (keycode == KEYBOARD__DeleteBackspace) {
    if (recent_key_num)
      --recent_key_num;
    return;
  }

  if (recent_key_num == MAX_KEYSTROKES)
    return;

  recent_keys[recent_key_num].shifted = usb__kb__read_key(KEYBOARD__LeftShift)
      || usb__kb__read_key(KEYBOARD__RightShift);
  recent_keys[recent_key_num].keycode = keycode;
  ++recent_key_num;
}

void key_functions__repeat_recent_keys(void) {
  bool shift = usb__kb__read_key(KEYBOARD__LeftShift);

  for (int i = 0; i < recent_key_num; ++i) {
    if (shift != recent_keys[i].shifted) {
      shift = recent_keys[i].shifted;
      usb__kb__set_key(shift, KEYBOARD__LeftShift);
    }
    usb__kb__set_key(true, recent_keys[i].keycode);
    usb__kb__send_report();
    usb__kb__set_key(false, recent_keys[i].keycode);
    usb__kb__send_report();
  }

  if (shift) {
    usb__kb__set_key(false, KEYBOARD__LeftShift);
    usb__kb__send_report();
  }
}

// ----------------------------------------------------------------------------

void key_functions__press(uint8_t keycode) {
    usb__kb__set_key(true, keycode);
}

void key_functions__release(uint8_t keycode) {
    usb__kb__set_key(false, keycode);
}

void key_functions__toggle(uint8_t keycode) {
    if (usb__kb__read_key(keycode))
        usb__kb__set_key(false, keycode);
    else
        usb__kb__set_key(true, keycode);
}

