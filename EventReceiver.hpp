#ifndef EVENTRECEIVER_HPP_INCLUDED
#define EVENTRECEIVER_HPP_INCLUDED

#include <irrlicht/irrlicht.h>
#include "DriverSelectionConfiguration.hpp"

using namespace irr;

		// Declare a structure to hold some context for the event receiver so that it
		// has it available inside its OnEvent() method.
struct SAppContext
		{
		    IrrlichtDevice *device;
		    s32             counter;
		    irr::gui::IGUIListBox*    listbox;
		};

        // Define some values that we'll use to identify individual GUI controls.
enum
		{
   		 GUI_ID_QUIT_BUTTON = 101,
   		GUI_ID_NEW_WINDOW_BUTTON,
   		 GUI_ID_FILE_OPEN_BUTTON,
    		GUI_ID_TRANSPARENCY_SCROLL_BAR,
                GUI_ID_START_BUTTON
		};

void setSkinTransparency(s32 alpha, irr::gui::IGUISkin * skin)
		{
    		for (s32 i=0; i<irr::gui::EGDC_COUNT ; ++i)
    		{
        	video::SColor col = skin->getColor((irr::gui::EGUI_DEFAULT_COLOR)i);
        	col.setAlpha(alpha);
        	skin->setColor((irr::gui::EGUI_DEFAULT_COLOR)i, col);
    		}
	}

class EventReceiver : public IEventReceiver
{
	public:

		EventReceiver(SAppContext & context) : Context(context) { }

		//!< We'll create a struct to record info on the mouse state
		struct SMouseState
		{
			core::position2di Position;
			bool LeftButtonDown;
			SMouseState() : Position(), LeftButtonDown(false) { }
		} MouseState;

		//!< This is the one method that we have to implement
		virtual bool OnEvent(const SEvent& event)
		{
			//!< Remember the mouse state
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
						//!< We won't use the wheel
						break;
				}
			}

	if (event.EventType == EET_GUI_EVENT)
        {
            s32 id = event.GUIEvent.Caller->getID();
            irr::gui::IGUIEnvironment* env = Context.device->getGUIEnvironment();

            switch(event.GUIEvent.EventType)
            {
	case irr::gui::EGET_SCROLL_BAR_CHANGED:
                if (id == GUI_ID_TRANSPARENCY_SCROLL_BAR)
                {
                    s32 pos = ((irr::gui::IGUIScrollBar*)event.GUIEvent.Caller)->getPos();
                    setSkinTransparency(pos, env->getSkin());
                }
                break;

	case irr::gui::EGET_BUTTON_CLICKED:
                switch(id)
                {
                case GUI_ID_QUIT_BUTTON:
                    Context.device->closeDevice();
                    fatal("Quit Button Pressed, Quitting.", 0);
                    return true;
                    
                case GUI_ID_START_BUTTON:
                    Context.device->closeDevice();
                    return true;

                case GUI_ID_NEW_WINDOW_BUTTON:
                    {
                    Context.listbox->addItem(L"Window created");
                    Context.counter += 30;
                    if (Context.counter > 200)
                        Context.counter = 0;

                    irr::gui::IGUIWindow* window = env->addWindow(
                        irr::core::rect<s32>(100 + Context.counter, 100 + Context.counter, 300 + Context.counter, 200 + Context.counter),
                        false, // modal?
                        L"Test window");

                    env->addStaticText(L"Please close me",
                        irr::core::rect<s32>(35,35,140,50),
                        true, // border?
                        false, // wordwrap?
                        window);
                    }
                    return true;

                case GUI_ID_FILE_OPEN_BUTTON:
                    Context.listbox->addItem(L"File open");
                    // There are some options for the file open dialog
                    // We set the title, make it a modal window, and make sure
                    // that the working directory is restored after the dialog
                    // is finished.
                    env->addFileOpenDialog(L"Please choose a file.", true, 0, -1, true);
                    return true;

                default:
                    return false;
                }
                break;

            case irr::gui::EGET_FILE_SELECTED:
                {
                    // show the model filename, selected in the file dialog
                    irr::gui::IGUIFileOpenDialog* dialog =
                        (irr::gui::IGUIFileOpenDialog*)event.GUIEvent.Caller;
                    Context.listbox->addItem(dialog->getFileName());
                }
                break;

            default:
                break;
            }
        }
        //return false;

			//!< The state of each connected joystick is sent to us
			//!< once every run() of the Irrlicht device.  Store the
			//!< state of the first joystick, ignoring other joysticks.
			//!< This is currently only supported on Windows and Linux.
			if(event.EventType == irr::EET_JOYSTICK_INPUT_EVENT
					&& event.JoystickEvent.Joystick == 0)
			{
				JoystickState = event.JoystickEvent;
			}

			//!< Remember whether each key is down or up
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

		//!< This is used to check whether a key is being held down
		virtual bool IsKeyDown(EKEY_CODE keyCode) const
		{
			return KeyIsDown[keyCode];
		}

        EventReceiver() : Context(Context), MouseState(), JoystickState()
		{
			for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
				KeyIsDown[i] = false;

		}

	private:
		//!< We use this array to store the current state of each key

		bool KeyIsDown[KEY_KEY_CODES_COUNT];

		//!<Joystick State
		SEvent::SJoystickEvent JoystickState;

        SAppContext & Context;
};

#endif //!< EVENTRECEIVER_HPP_INCLUDED
