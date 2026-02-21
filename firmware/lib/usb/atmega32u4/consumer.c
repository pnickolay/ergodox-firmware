/* ----------------------------------------------------------------------------
 * Released under The MIT License (see "doc/licenses/MIT.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**                                                                 description
 * Implements the "consumer control" section of '.../firmware/lib/usb.h'
 */

#include <stdint.h>
#include "./keyboard/from-pjrc/usb.h"
#include "../../usb.h"

// ----------------------------------------------------------------------------

uint8_t usb__consumer__press(uint16_t usage_code) {
    consumer_key = usage_code;
    return usb_consumer_send();
}

uint8_t usb__consumer__release(void) {
    consumer_key = 0;
    return usb_consumer_send();
}
