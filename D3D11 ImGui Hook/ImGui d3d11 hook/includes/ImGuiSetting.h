#pragma once
#include "includes/includes.h"

HWND window = NULL; // ������ �ڵ� ���� ���� ���� �� �ʱ�ȭ
ID3D11Device* pDevice = NULL; // Direct3D 11 ��ġ ������ ���� ����
ID3D11DeviceContext* pContext = NULL; // Direct3D 11 ��ġ ���ؽ�Ʈ ������ ���� ����

void InitImGui()
{
    ImGui::CreateContext(); // ImGui ���ؽ�Ʈ ����
    ImGuiIO& io = ImGui::GetIO(); // ImGui ����� ��ü ��������
    io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange; // ���콺 Ŀ�� ���� ��Ȱ��ȭ �÷��� ����
    ImGui_ImplWin32_Init(window); // ImGui Win32 �ʱ�ȭ
    ImGui_ImplDX11_Init(pDevice, pContext); // ImGui DirectX 11 �ʱ�ȭ

    // ��Ʈ ������ ���� ���� ����ü ����
    ImFontConfig fontConfig;
    fontConfig.FontDataOwnedByAtlas = false; // ImGui�� ��Ʈ �����͸� �������� �ʵ��� ����

    // �޸𸮿� �ִ� TTF ��Ʈ �����͸� ImGui ��Ʈ�� �߰�
    // rawData: ��Ʈ ������ �迭�� ������
    // sizeof(rawData): ��Ʈ ������ �迭�� ũ��
    // 18.5f: ��Ʈ ũ��
    // &fontConfig: ��Ʈ ���� ����ü ������
    // io.Fonts->GetGlyphRangesKorean(): �ѱ� ������ �����ϴ� �Լ� ȣ��
    io.Fonts->AddFontFromMemoryTTF(rawData, sizeof(rawData), 18.5f, &fontConfig, io.Fonts->GetGlyphRangesKorean());

    ImGuiStyle& style = ImGui::GetStyle(); // ImGui ��Ÿ�� ��ü ��������
    // �Ʒ��� ������ ���� �ڵ带 �־� �ּ���.

}