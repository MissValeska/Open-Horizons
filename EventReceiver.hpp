#ifndef EVENTRECEIVER_HPP_INCLUDED
#define EVENTRECEIVER_HPP_INCLUDED

#include <irrlicht.h>

using namespace irr;

class EventReceiver : public IEventReceiver
{


public:
    // We'll create a struct to record info on the mouse state
    struct SMouseState
     {
        core::position2di Position;
        bool LeftButtonDown;
        SMouseState() : LeftButtonDown(false) { }
    } MouseState;

    // This is the one method that we have to implement
    virtual bool OnEvent(const SEvent& event)
    {
        // Remember the mouse state
        if (event.EventType == irr::EET_MOUSE_INPUT_EVENT)
        {
            switch(event.MouseInput.Event)
            {
            case EMIE_LMOUSE_PRESSED_DOWN:
                MouseState.LeftButtonDown = true;
                break;

            case EMIE_LMOUSE_LEFT_UP:
                MouseState.LeftButtonDown = false;
                break;

            case EMIE_MOUSE_MOVED:
                MouseState.Position.X = event.MouseInput.X;
                MouseState.Position.Y = event.MouseInput.Y;
                break;

            default:
                // We won't use the wheel
                break;
            }
        }

        // The state of each connected joystick is sent to us
        // once every run() of the Irrlicht device.  Store the
        // state of the first joystick, ignoring other joysticks.
        // This is currently only supported on Windows and Linux.
        if (event.EventType == irr::EET_JOYSTICK_INPUT_EVENT
            && event.JoystickEvent.Joystick == 0)
        {
            JoystickState = event.JoystickEvent;
        }
        // Enumeration for UP, DOWN, PRESSED and RELEASED key states. Also used for mouse button states.
        enum keyStatesENUM {UP, DOWN, PRESSED, RELEASED};

        // Keyboard key states.
        keyStatesENUM keyState[KEY_KEY_CODES_COUNT];

        EKEY_CODE keyCode;

        // Remember whether each key is down or up
        if (event.EventType == irr::EET_KEY_INPUT_EVENT)
            KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;

            return false;

}
    const SEvent::SJoystickEvent & GetJoystickState(void) const
    {
        return JoystickState;
    }

    const SMouseState & GetMouseState(void) const
    {
        return MouseState;
    }

    // This is used to check whether a key is being held down
    virtual bool IsKeyDown(EKEY_CODE keyCode) const
    {
        return KeyIsDown[keyCode];
    }

    EventReceiver()
    {
        for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
            KeyIsDown[i] = false;

    }

private:
    // We use this array to store the current state of each key

    bool KeyIsDown[KEY_KEY_CODES_COUNT];

    //Joystick State
    SEvent::SJoystickEvent JoystickState;
};

#endif // EVENTRECEIVER_HPP_INCLUDED
