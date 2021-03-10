#ifndef CLOCKWORKISLAND_KEYBOARD_H__
#define CLOCKWORKISLAND_KEYBOARD_H__

#include <stdbool.h>

#define KEY_LEFT 0
#define KEY_RIGHT 1
#define KEY_Z 2
#define KEY_A 3
#define KEY_S 4
#define KEY_F1 5
#define KEY_QUIT 31

void Keyboard_CaptureInput();
bool Keyboard_KeyPressed(int key);
bool Keyboard_KeyTyped(int key);

#endif /* CLOCKWORKISLAND_KEYBOARD_H__ */