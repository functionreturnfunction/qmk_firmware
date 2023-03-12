#include "functionreturnfunction.h"

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    switch (keycode) {
      case CX1:
        SEND_STRING(SS_LCTL("x") "1");
        return false;
      case CX2:
        SEND_STRING(SS_LCTL("x") "2");
        return false;
      case CX3:
        SEND_STRING(SS_LCTL("x") "3");
        return false;
      case CXO:
        SEND_STRING(SS_LCTL("x") "o");
        return false;
      case CXB:
        SEND_STRING(SS_LCTL("x") "b");
        return false;
      case CXCS:
        SEND_STRING(SS_LCTL("xs"));
        return false;
      case CXCF:
        SEND_STRING(SS_LCTL("xf"));
        return false;
      case MARROW:
        SEND_STRING("->");
        return false;
      case EARROW:
        SEND_STRING("=>");
        return false;
    }
  }
  return true;
}
