#pragma once

// Input abstraction - hiding GLFW from the user
namespace Jellyfish
{
    enum class Key
    {
        // Movement keys
        W, A, S, D,
        Up, Down, Left, Right,
        Space, LeftShift, LeftControl,
        
        // Number keys
        Key0, Key1, Key2, Key3, Key4,
        Key5, Key6, Key7, Key8, Key9,
        
        // Function keys
        F1, F2, F3, F4, F5, F6,
        F7, F8, F9, F10, F11, F12,
        
        // Other common keys
        Escape, Enter, Tab, Backspace,
        Delete, Home, End, PageUp, PageDown,
        
        // Letters
        Q, E, R, T, Y, U, I, O, P,
        F, G, H, J, K, L,
        Z, X, C, V, B, N, M,
        
        Unknown
    };

    enum class MouseButton
    {
        Left,
        Right,
        Middle,
        Unknown
    };

    enum class InputAction
    {
        Press,
        Release,
        Repeat
    };
}
