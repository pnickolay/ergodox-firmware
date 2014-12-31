/* ----------------------------------------------------------------------------
 * Copyright (c) 2013, 2014 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/licenses/MIT.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**                                                                 description
 * My QWERTY layout, at the moment.  I imagine this will evolve over time.
 * Once I'm done with the Arensito layout, it may disappear altogether.
 *
 * Implements the "layout" section of '.../firmware/keyboard.h'
 */


#include "./fragments/includes.part.h"
#include "./fragments/macros.part.h"
#include "./fragments/types.part.h"
#include "./fragments/variables.part.h"


// ----------------------------------------------------------------------------
// keys
// ----------------------------------------------------------------------------

#include "./fragments/keys.part.h"


// ----------------------------------------------------------------------------
// LED control
// ----------------------------------------------------------------------------

#include "./fragments/led-control.part.h"


// ----------------------------------------------------------------------------
// matrix control
// ----------------------------------------------------------------------------

#include "./fragments/matrix-control.part.h"

// --- special keycode --------------------------------------------------------

#define KEYS__FHOTKEY(num) KEYS__HOTKEY( h##num,   KEYBOARD__F##num  )
KEYS__FHOTKEY( 1 );
KEYS__FHOTKEY( 2 );
KEYS__FHOTKEY( 3 );
KEYS__FHOTKEY( 4 );
KEYS__FHOTKEY( 5 );
KEYS__FHOTKEY( 6 );
KEYS__FHOTKEY( 7 );
//KEYS__FHOTKEY( 8 );
//KEYS__FHOTKEY( 9 );
//KEYS__FHOTKEY( 10 );
KEYS__FHOTKEY( 11 );
KEYS__FHOTKEY( 12 );
KEYS__HOTKEY( h13, KEYBOARD__Pause );
KEYS__HOTKEY( h14, KEYBOARD__Application );

KEYS__DEFAULT( lock, KEYBOARD__Application );

KEYS__HOTKEY( volU, KEYBOARD__F10 );
KEYS__HOTKEY( volD, KEYBOARD__F9 );
KEYS__HOTKEY( mute, KEYBOARD__F8 );

KEYS__ALT_SHIFTED( play, KEYBOARD__1_Exclamation );
KEYS__ALT_SHIFTED( skip, KEYBOARD__2_At );
KEYS__ALT_SHIFTED( media, KEYBOARD__3_Pound );

// ----------------------------------------------------------------------------
// layout
// ----------------------------------------------------------------------------

static layout_t layout PROGMEM = {
// ............................................................................

    MATRIX_LAYER(  // layer 0 : default
// macro, unused,
       K,    nop,
// left hand ...... ......... ......... ......... ......... ......... .........
     esc,        1,        2,        3,        4,        5,    equal,
 bkslash,        q,        w,        e,        r,        t,      h6,
     tab,        a,        s,        d,        f,        g,
shL2kcap,        z,        x,        c,        v,        b,      h7,
    altL,    grave, lpupo2l2, shL2kcap,    ctrlL,
                                                        bs,     del,
                                                       nop,      nop, lpu1l1,
                                                     space, shL2kcap, lpupo3l3,
// right hand ..... ......... ......... ......... ......... ......... .........
              dash,        6,        7,        8,        9,        0,    brktR,
               nop,        y,        u,        i,        o,        p,    brktL,
                           h,        j,        k,        l,  semicol,    quote,
              dash,        n,        m,    comma,   period,    slash, shR2kcap,
                                arrowL,   arrowD,   arrowU,   arrowR,     lock,
    h1,       h2,
   h13,      nop,      nop,
    bs, shR2kcap,  lpupo2l2  ),

// ............................................................................

    MATRIX_LAYER(  // layer 1 : number pad
// macro, unused,
       K,    nop,
// left hand ...... ......... ......... ......... ......... ......... .........
  transp,   transp,   transp,   transp,   transp,   transp,   transp,
  transp,   transp,   transp,   transp,   transp,   transp,   transp,
  transp,   transp,   transp,   transp,   transp,   transp,
  transp,   transp,   transp,   transp,   transp,   transp,   transp,
  transp,   transp,   transp,   transp,   transp,
                                                              transp,   transp,
                                                    transp,   transp,   nop,
                                                    transp,   transp,   transp,
// right hand ..... ......... ......... ......... ......... ......... .........
            transp,   transp,        7,        8,        9,     dash,   transp,
            transp,   transp,        7,        8,        9,     plus,   transp,
                      transp,        4,        5,        6, asterisk,   transp,
            lpo1l1,   transp,        0,    equal,   period,    slash,   transp,
                                transp,   transp,   transp,   transp,   transp,
  transp,   transp,
  transp,   transp,   transp,
  transp,   transp,   transp  ),

// ............................................................................

  MATRIX_LAYER(  // layer 2 : symbols and function keys
// macro, unused,
     K,    nop,
// left hand ...... ......... ......... ......... ......... ......... .........
transp,       F1,       F2,       F3,       F4,       F5,      F11,
transp, lessThan, grtrThan,   braceL,   braceR,   dollar,   transp,
transp,    brktL,    brktR,   parenL,   parenR,    caret,
transp,  semicol,  undersc, asterisk,  undersc,     plus,   transp,
transp,    enter,   transp,   transp,   transp,
                                                              mute,   volU,
                                                  transp,   transp,   volD,
                                                      bs,    transp,   guiR,
// right hand ..... ......... ......... ......... ......... ......... .........
             F12,       F6,       F7,       F8,       F9,      F10, lpupo4l4,
          transp,    caret,     plus,      del,      end,    pageU,   transp,
                      dash,    equal, asterisk,     plus,  undersc,   transp,
          transp,       bs,   exclam,      amp,     pipe,  percent,   transp,
                                home,    pageD,    pageU,      end,      h14,
h3,   h4,
h5,   transp,   transp,
h12,   h11,   transp  ),

// ............................................................................

MATRIX_LAYER(  // layer 3 : media keys
// macro, unused,
   K,    nop,
// left hand ...... ......... ......... ......... ......... ......... .........
transp,       F1,       F2,       F3,       F4,       F5,      F11,
transp,   transp,   transp,   transp,   transp,   transp,   transp,
transp,   transp,   transp,   transp,   transp,   transp,
transp,   transp,   transp,   transp,   transp,   transp,   transp,
transp,   transp,   transp,   transp,   transp,
                                                            mute,   volU,
                                                transp,   transp,   volD,
                                                 media,   play,     skip,
// right hand ..... ......... ......... ......... ......... ......... .........
           F12,       F6,       F7,       F8,       F9,      F10,      transp,
           transp,   transp,   transp,   transp,   transp,   transp,   transp,
           transp,   transp,   transp,   transp,   transp,   transp,
           transp,   transp,   transp,   transp,   transp,   transp,   transp,
                                 home,    pageD,    pageU,      end,   transp,
transp,   transp,
transp,   transp,   transp,
transp,   transp,   transp  ),

// ............................................................................

    MATRIX_LAYER(  // layer 4 : keyboard functions
// macro, unused,
       K,    nop,
// left hand ...... ......... ......... ......... ......... ......... .........
   btldr,      nop,      nop,      nop,      nop,      nop,      nop,
     nop,      nop,      nop,      nop,      nop,      nop,      nop,
     nop,      nop,      nop,      nop,      nop,      nop,
     nop,      nop,      nop,      nop,      nop,      nop,      nop,
     nop,      nop,      nop,      nop,      nop,
                                                                 nop,      nop,
                                                       nop,      nop,      nop,
                                                       nop,      nop,      nop,
// right hand ..... ......... ......... ......... ......... ......... .........
               nop,      nop,      nop,      nop,      nop,      nop, dmp_sram,
               nop,      nop,      nop,      nop,      nop,      nop, dmp_prog,
                         nop,      nop,      nop,      nop,      nop, dmp_eepr,
               nop,      nop,      nop,      nop,      nop,      nop,      nop,
                                   nop,      nop,      nop,      nop,      nop,
     nop,      nop,
     nop,      nop,      nop,
     nop,      nop,      nop  ),

// ............................................................................
};

