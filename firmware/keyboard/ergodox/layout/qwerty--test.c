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
KEYS__FHOTKEY( 7 );  // language
//KEYS__FHOTKEY( 8 );  // mute
//KEYS__FHOTKEY( 9 );  // volD
//KEYS__FHOTKEY( 10 ); // volU
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
KEYS__ALT_SHIFTED( next, KEYBOARD__2_At );
KEYS__ALT_SHIFTED( prev, KEYBOARD__6_Caret );
KEYS__ALT_SHIFTED( media, KEYBOARD__3_Pound );
KEYS__ALT_SHIFTED( thumbU, KEYBOARD__4_Dollar );
KEYS__ALT_SHIFTED( thumbD, KEYBOARD__5_Percent);

KEYS__LAYER__PUSH_POP_KEY(2, enter);
KEYS__LAYER__PUSH_POP_KEY(3, play);

// change language and retype
void P(swpLang) (void) {
  uint8_t count = KF(recent_keys_length)();
  for (int i = 0; i < count; ++i) {
    usb__kb__set_key(true, KEYBOARD__DeleteBackspace);
    usb__kb__send_report();
    usb__kb__set_key(false, KEYBOARD__DeleteBackspace);
    usb__kb__send_report();
  }
  P(hf7)();
  usb__kb__send_report();
  R(hf7)();
  usb__kb__send_report();
  timer__schedule_cycles(20, KF(repeat_recent_keys));
}
void R(swpLang) (void) { }


/**
 * record mouse click sequence
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#define MAX_CLICKS 50
static bool is_recording = false;
static uint16_t mem_seq[10][MAX_CLICKS+1];
static uint16_t current_seq[MAX_CLICKS];
static uint16_t start_time;
static int current_num = 0;
static int debug_i = -1;

void P(rec) (void) {
  is_recording = !is_recording;

  if (is_recording) {
    kb__led__on(1);
    current_num = 0;
    start_time = timer__get_hardware_ticks();
  } else {
    kb__led__off(1);
  }
}
void R(rec) (void) { }

void P(clk) (void) {
  if (is_recording) {
    current_seq[current_num++] = timer__get_hardware_ticks() - start_time;
    if (current_num == MAX_CLICKS)
      P(rec)();
  } else if (debug_i != -1) {
    int diff = current_seq[debug_i] - (int)(timer__get_hardware_ticks() - start_time);
    if (diff < 0)
      kb__led__on(1);
    else if (diff > 0)
      kb__led__on(2);
    else
      kb__led__all_off();
  }

  KF(mouse_left_click)(0, 0);
}
void R(clk) (void) { }

void P(dclk) (void) { P(clk)(); P(clk)(); }
void R(dclk) (void) { }

static bool inf_click = false;
void infClick(void) {
  if (!inf_click)
    return;
  P(clk)();
  timer__schedule_cycles(1, infClick);
}
void P(iclk) (void) {
  inf_click = true;
  infClick();
}
void R(iclk) (void) { inf_click = false; }

void P(cur) (void) {
  if (is_recording)
    return;

  start_time = timer__get_hardware_ticks();
  for (int i = 0; i < current_num; ++i) {
    while( timer__get_hardware_ticks() - start_time < current_seq[i]) ;
    debug_i = i;
    P(clk)();
  }
  debug_i = -1;
}
void R(cur) (void) { }

static bool is_looping = false;
void loopCur(void) {
  if (is_looping) {
    P(cur)();
    timer__schedule_cycles(10, loopCur);
  }
}
void P(loop) (void) {
  if (is_recording)
    return;

  is_looping = true;
  loopCur();
}
void R(loop) (void) { }

void P(sloop) (void) {
  if (is_recording)
    return;

  kb__led__all_off();
  is_looping = false;
}
void R(sloop) (void) { }

static uint16_t skp_time;
void P(skp) (void) {
  skp_time = timer__get_milliseconds();
}
void R(skp) (void) {
  if (timer__get_milliseconds() - skp_time > 500)
    return;

  KF(mouse_left_click)(0, 0);
}

static bool editing_interval = false;
static uint16_t change_speed = 1;
void P(mUp) (void) {
  if (editing_interval) {
    change_speed <<= 1;
    if (change_speed == 0)
      change_speed = 1 << 15;
    return;
  }

  KF(mouse_move)(0, -30);
}
void R(mUp) (void) { }
void P(mDw) (void) {
  if (editing_interval) {
    change_speed >>= 1;
    if (change_speed == 0)
      change_speed = 1;
    return;
  }

  KF(mouse_move)(0, 30);
}
void R(mDw) (void) { }
void P(mLf) (void) {
  if (editing_interval) {
    current_seq[current_num - 1] -= change_speed;
    return;
  }

  KF(mouse_move)(-30, 0);
}
void R(mLf) (void) { }
void P(mRt) (void) {
  if (editing_interval) {
    current_seq[current_num - 1] += change_speed;
    return;
  }

  KF(mouse_move)(30, 0);
}
void R(mRt) (void) { }
void P(mDel) (void) {
  if (current_num) --current_num;
}
void R(mDel) (void) { }
void P(mAppend) (void) {
  if (is_recording)
    P(rec)();
  P(cur)();
  is_recording = true;
  kb__led__on(1);
}
void R(mAppend) (void) { }

void P(mTT) (void) {
  editing_interval = !editing_interval;
}
void R(mTT) (void) { }

void save_seq(int pos) {
  mem_seq[pos][0] = current_num;
  for (int i = 0; i < current_num; ++i)
    mem_seq[pos][i + 1] = current_seq[i];
}

void play_seq(int pos) {
  if (!is_recording)
    start_time = timer__get_hardware_ticks();

  for (int i = 0; i < mem_seq[pos][0]; ++i) {
    while( timer__get_hardware_ticks() - start_time < mem_seq[pos][i + 1] );
    P(clk)();
  }
}

bool mem_store = false;
void P(mstore) (void) { mem_store = true; }
void R(mstore) (void) { mem_store = false; }

#define MMEM(n) \
void P(mmem##n) (void) { \
  if (mem_store) save_seq(n); \
  else play_seq(n); \
} \
void R(mmem##n) (void) { }

MMEM(0);
MMEM(1);
MMEM(2);
MMEM(3);
MMEM(4);
MMEM(5);
MMEM(6);
MMEM(7);
MMEM(8);
MMEM(9);


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
   hf3,      nop,      nop,
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
transp,  semicol,  undersc, asterisk,  undersc,    pound,  swpLang,
transp,    enter,   transp,   transp,   transp,
                                                              prev,   next,
                                                  transp,   transp, thumbD,
                                                  transp,   transp,   next,
// right hand ..... ......... ......... ......... ......... ......... .........
             F12,       F6,       F7,       F8,       F9,      F10,     lpu4,
          transp,    caret,     plus,  percent,      end,    pageU,   transp,
                   undersc,    equal,    kpMul,    kpAdd,    colon, dblQuote,
            hf11,      del,   exclam,      amp,     pipe, question,   transp,
                                home,    pageD,    pageU,      end,     hApp,
hPause,    hf4,
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
  mstore,    mmem1,    mmem2,    mmem3,    mmem4,    mmem5,      nop,
     nop,      nop,      nop,      mUp,      nop,      nop,      nop,
     nop,      nop,      mLf,      mDw,      mRt,      nop,
     nop,      nop,      nop,      nop,      nop,      nop,      nop,
     nop,      nop,      nop,      nop,      nop,
                                                                mDel,  mAppend,
                                                       nop,      nop,      nop,
                                                       skp,      nop,      mTT,
// right hand ..... ......... ......... ......... ......... ......... .........
               nop,    mmem6,    mmem7,    mmem8,    mmem9,    mmem0,      nop,
               nop,      nop,      nop,      nop,      nop,      nop,      nop,
                         nop,      clk,      clk,     dclk,     dclk,      nop,
              lpo4,      nop,      nop,      nop,      nop,      nop,      nop,
                                   nop,      nop,      nop,      nop,      nop,
    loop,    sloop,
     nop,      nop,      nop,
     rec,      cur,      iclk  ),

// ............................................................................
};

