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

#define KEYS__FHOTKEY(num) KEYS__HOTKEY(hf##num,   KEYBOARD__F##num  )
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

//KEYS__HOTKEY( h1, KEYBOARD__1_Exclamation );
//KEYS__HOTKEY( h2, KEYBOARD__2_At);
//KEYS__HOTKEY( h3, KEYBOARD__3_Pound);
//KEYS__HOTKEY( h4, KEYBOARD__4_Dollar);
//KEYS__HOTKEY( h5, KEYBOARD__5_Percent);
KEYS__HOTKEY( h6, KEYBOARD__6_Caret);
KEYS__HOTKEY( h7, KEYBOARD__7_Ampersand);
KEYS__HOTKEY( h8, KEYBOARD__8_Asterisk);
KEYS__HOTKEY( h9, KEYBOARD__9_LeftParenthesis);
KEYS__HOTKEY( h0, KEYBOARD__0_RightParenthesis);

KEYS__HOTKEY( hPause, KEYBOARD__Pause );
KEYS__HOTKEY( hApp, KEYBOARD__Application );

KEYS__DEFAULT( lock, KEYBOARD__Application );

KEYS__HOTKEY( volU, KEYBOARD__F10 );
KEYS__HOTKEY( volD, KEYBOARD__F9 );
KEYS__HOTKEY( mute, KEYBOARD__F8 );

KEYS__ALT_SHIFTED( play, KEYBOARD__1_Exclamation );
KEYS__ALT_SHIFTED( skip, KEYBOARD__2_At );
KEYS__ALT_SHIFTED( media, KEYBOARD__3_Pound );
KEYS__ALT_SHIFTED( thumbU, KEYBOARD__4_Dollar );
KEYS__ALT_SHIFTED( thumbD, KEYBOARD__5_Percent);

KEYS__LAYER__PUSH_POP_KEY(2, enter);
KEYS__LAYER__PUSH_POP_KEY(3, play);

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
 bkslash,        q,        w,        e,        r,        t,      hf6,
     tab,        a,        s,        d,        f,        g,
shL2kcap,        z,        x,        c,        v,        b,      hf7,
    altL,    grave,   lpupo2, shL2kcap,    ctrlL,
                                                       del,       bs,
                                                       nop,      nop, lpupo1,
                                                     space, shL2kcap, lpupo3k,
// right hand ..... ......... ......... ......... ......... ......... .........
              dash,        6,        7,        8,        9,        0,    brktR,
              lpu1,        y,        u,        i,        o,        p,    brktL,
                           h,        j,        k,        l,  semicol,    quote,
              dash,        n,        m,    comma,   period,    slash, shR2kcap,
                                arrowL,   arrowD,   arrowU,   arrowR,     lock,
   hf1,      hf2,
hPause,      nop,      nop,
    bs, shR2kcap,   lpupo2k ),

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
            transp,   transp,      kp7,      kp8,      kp9,    kpSub,   transp,
            transp,   transp,      kp4,      kp5,      kp6,    kpAdd,   transp,
                      transp,      kp1,      kp2,      kp3,    kpMul,   transp,
              lpo1,   transp,      kp0,    equal,    kpDec,    kpDiv,   transp,
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
transp,  semicol,  undersc, asterisk,  undersc,    pound,   transp,
transp,    enter,   transp,   transp,   transp,
                                                              mute,   volU,
                                                  transp,   transp,   volD,
                                                    skip,   transp, thumbD,
// right hand ..... ......... ......... ......... ......... ......... .........
             F12,       F6,       F7,       F8,       F9,      F10,   lpupo4,
          transp,    caret,     plus,      del,      end,    pageU,   transp,
                   undersc,    equal, asterisk,     plus,    colon,   transp,
            hf11,      del,   exclam,      amp,     pipe,  percent,   transp,
                                home,    pageD,    pageU,      end,     hApp,
  hf3,    hf4,
  hf5, transp,   transp,
 guiR, transp,   transp  ),

// ............................................................................

MATRIX_LAYER(  // layer 3 : media keys
// macro, unused,
   K,    nop,
// left hand ...... ......... ......... ......... ......... ......... .........
 btldr,       F1,       F2,       F3,       F4,       F5,      F11,
transp,   transp,   transp,   transp,   transp,   transp,   transp,
transp,   transp,   transp,   transp,   transp,   transp,
transp,   transp,   transp,   transp,   transp,   transp,   transp,
transp,   transp,   transp,   transp,   transp,
                                                            mute,   volU,
                                                transp,   transp,   volD,
                                                 media,   thumbU,    nop,
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
               nop,      nop,      nop,      nop,      nop,      nop,      nop,
               nop,      nop,      nop,      nop,      nop,      nop,      nop,
                         nop,      nop,      nop,      nop,      nop,      nop,
               nop,      nop,      nop,      nop,      nop,      nop,      nop,
                                   nop,      nop,      nop,      nop,      nop,
     nop,      nop,
     nop,      nop,      nop,
     nop,      nop,      nop  ),

// ............................................................................
};

