#pragma once
#include <cstdint>
#include <vector>
#include <Windows.h>
#include <d3d11.h>
#include <dxgi.h>
#include "../HookLib/Kiero/kiero.h"
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_win32.h"
#include "../imgui/imgui_impl_dx11.h"
#include "font.h"
#include "ImGuiSetting.h"
#include "ImGuiMenu.h"

typedef HRESULT(__stdcall* Present) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);
typedef uintptr_t PTR;