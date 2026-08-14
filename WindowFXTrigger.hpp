#pragma once
#include <Geode/Geode.hpp>

// Object ID for the custom trigger, as it'll appear in the level editor.
// Vanilla GD trigger IDs run up through the 3000s as of 2.2; mods claim
// IDs well outside that range to avoid stepping on official objects.
// If you're planning to publish this, check the Geode Discord's shared
// custom-ID list first so you don't collide with another mod's trigger.
constexpr int kWindowFXTriggerID = 9911;
