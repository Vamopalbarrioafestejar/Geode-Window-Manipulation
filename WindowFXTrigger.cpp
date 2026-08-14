#include "WindowFXTrigger.hpp"
#include "WinWindow.hpp"
#include <Geode/modify/EffectGameObject.hpp>

using namespace geode::prelude;

// Hooks the function GD calls whenever a trigger fires (touched or
// spawn-triggered). EffectGameObject handles most vanilla trigger types
// internally via a switch on m_objectID — we intercept before that switch
// and only pass through to the original for IDs we don't own.
//
// NOTE: field names below (m_moveOffset, m_duration) are the commonly
// reused move-trigger fields, repurposed as generic parameters so the
// trigger works without a custom edit popup yet. Confirm the exact names
// against EffectGameObject in the current bindings before you build —
// they've shifted across GD updates before.
class $modify(WindowFXHook, EffectGameObject) {
    void triggerObject(GJBaseGameLayer* layer, int p1, gd::vector<int> const* p2) {
        if (m_objectID != kWindowFXTriggerID) {
            return EffectGameObject::triggerObject(layer, p1, p2);
        }

        int paramX = static_cast<int>(m_moveOffset.x);
        int paramY = static_cast<int>(m_moveOffset.y);

        // m_duration doubles as a mode switch until there's a real popup:
        //   0 = move window   1 = resize window
        //   2 = fade window   3 = spawn decoy window
        switch (static_cast<int>(m_duration)) {
            case 0: winfx::setWindowPos(paramX, paramY); break;
            case 1: winfx::setWindowSize(paramX, paramY); break;
            case 2:
                winfx::enableTransparency();
                winfx::setOpacity(static_cast<BYTE>(paramX)); // 0-255
                break;
            case 3: winfx::spawnDecoyWindow(L"???", paramX, paramY, 300, 200); break;
        }
    }
};
