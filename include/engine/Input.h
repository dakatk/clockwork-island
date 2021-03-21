#ifndef CLOCKWORKISLAND_INPUT_H__
#define CLOCKWORKISLAND_INPUT_H__

#include <stdbool.h>
#include <stdint.h>

#define KEY_1           0x1
#define KEY_2           0x2
#define KEY_3           0x4
#define KEY_4           0x8
#define KEY_5           0x10
#define KEY_0           0x20
#define KEY_LEFT        0x40
#define KEY_RIGHT       0x80
#define KEY_Z           0x100
#define KEY_A           0x200
#define KEY_S           0x400
#define KEY_F1          0x800
#define KEY_QUIT        0x1000

#define BUTTON_LEFT     0x1
#define BUTTON_RIGHT    0x2
#define BUTTON_MIDDLE   0x4

extern int Input_MouseX;
extern int Input_MouseY;

void Input_Capture();

bool Input_KeyPressed(int key);
bool Input_KeyTyped(int key);

uint16_t Input_KeysBuffer();

bool Input_ButtonPressed(int button);

#endif /* CLOCKWORKISLAND_INPUT_H__ */