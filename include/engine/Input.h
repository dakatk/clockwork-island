#ifndef ENGINE_INPUT_H__
#define ENGINE_INPUT_H__

#include <cstdint>

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

namespace engine
{
    class Input
    {
    private:
        static int mouseX;
        static int mouseY;

        static uint16_t keysBuffer;
        static uint16_t prevKeysBuffer;
        static uint8_t mouseBuffer;

    public:
        static int GetMouseX();
        static int GetMouseY();

        static void Capture();
        static uint16_t KeysBuffer();

        static bool KeyPressed(uint16_t key);
        static bool KeyTyped(uint16_t key);
        static bool ButtonPressed(uint8_t button);
    };
}

#endif /* ENGINE_INPUT_H__ */
