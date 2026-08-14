#pragma once
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>

namespace winfx {
    // Resolves the game's own HWND via GLFW. Cheap enough to call each time;
    // cache it yourself if you're calling these every frame.
    HWND getGameWindow();

    void setWindowPos(int x, int y);
    void setWindowSize(int width, int height);

    void enableTransparency();       // flips on WS_EX_LAYERED, one-time setup
    void setOpacity(BYTE alpha);     // 0 = invisible, 255 = opaque

    // Spawns a bare decoy window — not the game's render target, just a
    // prop. Fill it in (child controls, a bitmap, whatever) if you want it
    // to look like something instead of a blank rectangle.
    HWND spawnDecoyWindow(const wchar_t* title, int x, int y, int width, int height);
}
