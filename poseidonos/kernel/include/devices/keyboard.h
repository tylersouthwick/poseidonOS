#ifndef DEVICES_KEYBOARD_H
#define DEVICES_KEYBOARD_H

/******************************Key codes***************************/
#define KEY_CAPSLOCK 			1
#define KEY_SHIFT					2
#define KEY_ALT						3
#define KEY_SCROLL_LOCK		4
#define KEY_NUMLOCK				5
#define KEY_CONTROL				6

#define KEY_KEYPAD_NUMLOCK KEY_NUMLOCK
#define KEY_RIGHT_SHIFT KEY_SHIFT
#define KEY_LEFT_ALT KEY_ALT
#define KEY_LEFT_SHIFT KEY_SHIFT
#define KEY_LEFT_CONTROL KEY_CONTROL

#define KEY_F1 'f'
#define KEY_F2 'f'
#define KEY_F3 'f'
#define KEY_F4 'f'
#define KEY_F5 'f'
#define KEY_F6 'f'
#define KEY_F7 'f'
#define KEY_F8 'f'
#define KEY_F9 'f'
#define KEY_F10 'f'
#define KEY_F11 'f'
#define KEY_F12 'f'

#define KEY_ESC 13

#define KEY_1 '1'
#define KEY_2 '2'
#define KEY_3 '3'
#define KEY_4 '4'
#define KEY_5 '5'
#define KEY_6 '6'
#define KEY_7 '7'
#define KEY_8 '8'
#define KEY_9 '9'
#define KEY_0 '0'

#define KEY_A 'a'
#define KEY_B 'b'
#define KEY_C 'c'
#define KEY_D 'd'
#define KEY_E 'e'
#define KEY_F 'f'
#define KEY_G 'g'
#define KEY_H 'h'
#define KEY_I 'i'
#define KEY_J 'j'
#define KEY_K 'k'
#define KEY_L 'l'
#define KEY_M 'm'
#define KEY_N 'n'
#define KEY_O 'o'
#define KEY_P 'p'
#define KEY_Q 'q'
#define KEY_R 'r'
#define KEY_S 's'
#define KEY_T 't'
#define KEY_U 'u'
#define KEY_V 'v'
#define KEY_W 'w'
#define KEY_X 'x'
#define KEY_Y 'y'
#define KEY_Z 'z'

#define KEY_KEYPAD_1 '1'
#define KEY_KEYPAD_2 '2'
#define KEY_KEYPAD_3 '3'
#define KEY_KEYPAD_4 '4'
#define KEY_KEYPAD_5 '5'
#define KEY_KEYPAD_6 '6'
#define KEY_KEYPAD_7 '7'
#define KEY_KEYPAP_8 '8'
#define KEY_KEYPAD_9 '9'
#define KEY_KEYPAD_0 '0'

#define KEY_HYPHEN '-'
#define KEY_EQUALS '='
#define KEY_BACKSPACE '\b'
#define KEY_TAB '\t'
#define KEY_SEMI_COLEN ';'
#define KEY_APOSTOPHE '\''
#define KEY_TICK '`'
#define KEY_KEYPAD_PLUS '+'
#define KEY_KEYPAD_PERIOD '.'
#define KEY_KEYPAD_HYPHEN '-'
#define KEY_HYPHEN '-'
#define KEY_EQUALS '='
#define KEY_BACKSPACE '\b'
#define KEY_TAB '\t'
#define KEY_COMMA ','
#define KEY_PERIOD '.'
#define KEY_SLASH '/'
#define KEY_KEYPAD_ASTRISK '*'
#define KEY_SPACEBAR ' '
#define KEY_OPEN_SQUARE_BRACKET '['
#define KEY_CLOSE_SQUARE_BRACKET ']'
#define KEY_ENTER '\n'

void keyboard_init(void);
void keyboard_irq(void);

#endif

