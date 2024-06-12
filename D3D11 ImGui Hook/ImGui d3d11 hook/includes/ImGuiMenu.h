#pragma once
#include "includes/includes.h"

void ImGuiMenu() {
    // ImGui 프레임 설정
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    // ImGui 윈도우 렌더링
    ImGui::Begin(u8"ImGui Window");
    ImGui::Text(u8"abc");
    ImGui::End();

    ImGui::Render();
}