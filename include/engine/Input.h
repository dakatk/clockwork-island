#ifndef CLOCKWORKISLAND_INPUT_H__
#define CLOCKWORKISLAND_INPUT_H__

#include <stdbool.h>

#define KEY_LEFT 0
#define KEY_RIGHT 1
#define KEY_Z 2
#define KEY_A 3
#define KEY_S 4
#define KEY_F1 5
#define KEY_QUIT 31

#define BUTTON_LEFT 0
#define BUTTON_RIGHT 1
#define BUTTON_MIDDLE 2

extern int Input_MouseX;
extern int Input_MouseY;

void Input_Capture();

bool Input_KeyPressed(int key);
bool Input_KeyTyped(int key);

bool Input_ButtonPressed(int button);

#endif /* CLOCKWORKISLAND_INPUT_H__ */