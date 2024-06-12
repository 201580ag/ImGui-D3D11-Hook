#pragma once
#include "includes.h"

uintptr_t moduleBase = (uintptr_t)GetModuleHandle(""); // 대상 프로세스

constexpr DWORD Offset = 0x1234; // 예시 오프셋