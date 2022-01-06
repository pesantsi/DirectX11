#include <pch.h>

#include <GameInput.h>

namespace CoreProject
{
    void GameInput::Initialize(HWND hwnd)
    {
        m_HWND = hwnd;
        ThrowIfFailed(DirectInput8Create(GetModuleHandle(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_directInput, nullptr));

        ThrowIfFailed(m_directInput->CreateDevice(GUID_SysKeyboard, &m_directInputKeyboard, nullptr));
        ThrowIfFailed(m_directInputKeyboard->SetDataFormat(&c_dfDIKeyboard));
        //ThrowIfFailed(m_directInputKeyboard->SetCooperativeLevel(m_HWND, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
        ThrowIfFailed(m_directInputKeyboard->SetCooperativeLevel(nullptr, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND)); //Ubisoft

        ThrowIfFailed(m_directInput->CreateDevice(GUID_SysMouse, &m_directInputMouse, nullptr));
        ThrowIfFailed(m_directInputMouse->SetDataFormat(&c_dfDIMouse));
        //ThrowIfFailed(m_directInputMouse->SetCooperativeLevel(m_HWND, DISCL_EXCLUSIVE | DISCL_NOWINKEY | DISCL_FOREGROUND));
        ThrowIfFailed(m_directInputMouse->SetCooperativeLevel(nullptr, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND)); //Ubisoft
    }

    void GameInput::Update(const std::shared_ptr<CoreProject::StepTimer>&)
    {
        HWND foreground = GetForegroundWindow();
        bool visible = IsWindowVisible(foreground) != 0;
        if (m_HWND == foreground && visible)
        {
            m_directInputKeyboard->Acquire();
            m_directInputKeyboard->GetDeviceState(sizeof(m_KeyBuffer), &m_KeyBuffer);

            m_directInputMouse->Acquire();
            m_directInputMouse->GetDeviceState(sizeof(DIMOUSESTATE), &m_mouseState);

            m_analogs[kAnalogMouseX] = (float)m_mouseState.lX * -0.001f;
            m_analogs[kAnalogMouseY] = (float)m_mouseState.lY * 0.001f;

            if (m_mouseState.lZ > 0)
                m_analogs[kAnalogMouseScroll] = 1.0f;
            else if (m_mouseState.lZ < 0)
                m_analogs[kAnalogMouseScroll] = -1.0f;

            /*if (keyboardState[DIK_ESCAPE] & 0x80)
                PostMessage(m_HWND, WM_DESTROY, 0, 0);

            float speed = 15.0f * time;

            if (keyboardState[DIK_A] & 0x80)
            {
                moveLeftRight -= speed;
            }
            if (keyboardState[DIK_D] & 0x80)
            {
                moveLeftRight += speed;
            }
            if (keyboardState[DIK_W] & 0x80)
            {
                moveBackForward += speed;
            }
            if (keyboardState[DIK_S] & 0x80)
            {
                moveBackForward -= speed;
            }
            if ((mouseCurrState.lX != mouseLastState.lX) || (mouseCurrState.lY != mouseLastState.lY))
            {
                camYaw += mouseLastState.lX * 0.001f;

                camPitch += mouseCurrState.lY * 0.001f;

                mouseLastState = mouseCurrState;
            }*/
        }
        else
        {
            memset(&m_mouseState, 0, sizeof(DIMOUSESTATE2));
            memset(m_KeyBuffer, 0, sizeof(m_KeyBuffer));
        }
    }

    void GameInput::Shutdown()
    {
        m_directInputKeyboard->Unacquire();
        m_directInputKeyboard.Reset();
        m_directInputMouse->Unacquire();
        m_directInputMouse.Reset();
        m_directInput.Reset();
    }
}
