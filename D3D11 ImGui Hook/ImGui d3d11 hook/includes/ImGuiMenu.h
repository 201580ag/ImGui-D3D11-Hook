#pragma once
#include "includes/includes.h"

void ImGuiMenu() {
    // ImGui ������ ����
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    // ImGui ������ ������
    ImGui::Begin(u8"ImGui Window");
    ImGui::Text(u8"abc");
    ImGui::End();

    ImGui::Render();
}