#include "WinWindow.hpp"

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <cocos2d.h>

HWND winfx::getGameWindow() {
    // CCEGLView wraps the GLFWwindow* Geode's cocos2d fork runs on.
    // Method name to confirm against docs.geode-sdk.org/classes if this
    // doesn't match your SDK version.
    auto* glView = cocos2d::CCEGLView::sharedOpenGLView();
    GLFWwindow* window = glView->getWindow();
    return glfwGetWin32Window(window);
}

void winfx::setWindowPos(int x, int y) {
    SetWindowPos(getGameWindow(), nullptr, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}

void winfx::setWindowSize(int width, int height) {
    SetWindowPos(getGameWindow(), nullptr, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER);
}

void winfx::enableTransparency() {
    HWND hwnd = getGameWindow();
    LONG_PTR exStyle = GetWindowLongPtr(hwnd, GWL_EXSTYLE);
    SetWindowLongPtr(hwnd, GWL_EXSTYLE, exStyle | WS_EX_LAYERED);
}

void winfx::setOpacity(BYTE alpha) {
    SetLayeredWindowAttributes(getGameWindow(), 0, alpha, LWA_ALPHA);
}

HWND winfx::spawnDecoyWindow(const wchar_t* title, int x, int y, int width, int height) {
    static bool classRegistered = false;
    HINSTANCE inst = GetModuleHandleW(nullptr);

    if (!classRegistered) {
        WNDCLASSW wc = {};
        wc.lpfnWndProc = DefWindowProcW;
        wc.hInstance = inst;
        wc.lpszClassName = L"WindowFXDecoy";
        wc.hCursor = LoadCursorW(nullptr, IDC_ARROW);
        RegisterClassW(&wc);
        classRegistered = true;
    }

    return CreateWindowExW(
        WS_EX_TOPMOST,
        L"WindowFXDecoy",
        title,
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        x, y, width, height,
        nullptr, nullptr, inst, nullptr
    );
}
