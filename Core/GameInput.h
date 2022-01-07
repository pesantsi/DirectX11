#pragma once

#include <pch.h>
#include <IGameObject.h>
#include <StepTimer.h>

using namespace CoreProject_API;

namespace CoreProject
{
    class GameInput : IUpdatableObject
    {
    public:

        enum DigitalInput
        {
            kKey_escape = 1,
            kKey_1,
            kKey_2,
            kKey_3,
            kKey_4,
            kKey_5,
            kKey_6,
            kKey_7,
            kKey_8,
            kKey_9,
            kKey_0,
            kKey_minus,
            kKey_equals,
            kKey_back,
            kKey_tab,
            kKey_q,
            kKey_w,
            kKey_e,
            kKey_r,
            kKey_t,
            kKey_y,
            kKey_u,
            kKey_i,
            kKey_o,
            kKey_p,
            kKey_lbracket,
            kKey_rbracket,
            kKey_return,
            kKey_lcontrol,
            kKey_a,
            kKey_s,
            kKey_d,
            kKey_f,
            kKey_g,
            kKey_h,
            kKey_j,
            kKey_k,
            kKey_l,
            kKey_semicolon,
            kKey_apostrophe,
            kKey_grave,
            kKey_lshift,
            kKey_backslash,
            kKey_z,
            kKey_x,
            kKey_c,
            kKey_v,
            kKey_b,
            kKey_n,
            kKey_m,
            kKey_comma,
            kKey_period,
            kKey_slash,
            kKey_rshift,
            kKey_multiply,
            kKey_lalt,
            kKey_space,
            kKey_capital,
            kKey_f1,
            kKey_f2,
            kKey_f3,
            kKey_f4,
            kKey_f5,
            kKey_f6,
            kKey_f7,
            kKey_f8,
            kKey_f9,
            kKey_f10,
            kKey_numlock,
            kKey_scroll,
            kKey_numpad7,
            kKey_numpad8,
            kKey_numpad9,
            kKey_subtract,
            kKey_numpad4,
            kKey_numpad5,
            kKey_numpad6,
            kKey_add,
            kKey_numpad1,
            kKey_numpad2,
            kKey_numpad3,
            kKey_numpad0,
            kKey_decimal,
            kKey_f11,
            kKey_f12,
            kKey_numpadenter,
            kKey_rcontrol,
            kKey_divide,
            kKey_sysrq,
            kKey_ralt,
            kKey_pause,
            kKey_home,
            kKey_up,
            kKey_pgup,
            kKey_left,
            kKey_right,
            kKey_end,
            kKey_down,
            kKey_pgdn,
            kKey_insert,
            kKey_delete,
            kKey_lwin,
            kKey_rwin,
            kKey_apps,

            kNumKeys,

            // gamepad
            kDPadUp = kNumKeys,
            kDPadDown,
            kDPadLeft,
            kDPadRight,
            kStartButton,
            kBackButton,
            kLThumbClick,
            kRThumbClick,
            kLShoulder,
            kRShoulder,
            kAButton,
            kBButton,
            kXButton,
            kYButton,

            // mouse
            kMouse0,
            kMouse1,
            kMouse2,
            kMouse3,
            kMouse4,
            kMouse5,
            kMouse6,
            kMouse7,

            kNumDigitalInputs
        };

        enum AnalogInput
        {
            // gamepad
            kAnalogLeftTrigger,
            kAnalogRightTrigger,
            kAnalogLeftStickX,
            kAnalogLeftStickY,
            kAnalogRightStickX,
            kAnalogRightStickY,

            // mouse
            kAnalogMouseX,
            kAnalogMouseY,
            kAnalogMouseScroll,

            kNumAnalogInputs
        };

        static GameInput& GetInstance()
        {
            // Guaranteed to be destroyed.
             // Instantiated on first use.
            static GameInput instance;
            return instance;
        }

        GameInput(GameInput const&) = delete;
        void operator=(GameInput const&) = delete;

        void Initialize(HWND hwnd);
        void Update(const std::shared_ptr<IStepTimer>& stepTimer) override;
        void Shutdown();

        bool IsPressed(DigitalInput di)
        {
            return m_KeyBuffer[di] & 0x80;
        }

        bool IsReleased(DigitalInput di)
        {
            return !(m_KeyBuffer[di] & 0x80);
        }

        float GetAnalogInput(AnalogInput ai)
        {
            return m_analogs[ai];
        }

    private:
        GameInput() {}

        Microsoft::WRL::ComPtr<IDirectInput8A> m_directInput;
        Microsoft::WRL::ComPtr<IDirectInputDevice8A> m_directInputKeyboard;
        Microsoft::WRL::ComPtr<IDirectInputDevice8A> m_directInputMouse;

        DIMOUSESTATE2 m_mouseState;
        unsigned char m_KeyBuffer[256];
        float m_analogs[GameInput::kNumAnalogInputs];

        HWND m_HWND;
    };
}

