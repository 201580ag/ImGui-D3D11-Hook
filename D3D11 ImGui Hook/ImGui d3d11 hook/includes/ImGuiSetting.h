#pragma once
#include "includes/includes.h"

HWND window = NULL; // 윈도우 핸들 저장 변수 선언 및 초기화
ID3D11Device* pDevice = NULL; // Direct3D 11 장치 포인터 변수 선언
ID3D11DeviceContext* pContext = NULL; // Direct3D 11 장치 컨텍스트 포인터 변수 선언

void InitImGui()
{
    ImGui::CreateContext(); // ImGui 컨텍스트 생성
    ImGuiIO& io = ImGui::GetIO(); // ImGui 입출력 객체 가져오기
    io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange; // 마우스 커서 변경 비활성화 플래그 설정
    ImGui_ImplWin32_Init(window); // ImGui Win32 초기화
    ImGui_ImplDX11_Init(pDevice, pContext); // ImGui DirectX 11 초기화

    // 폰트 설정을 위한 구성 구조체 생성
    ImFontConfig fontConfig;
    fontConfig.FontDataOwnedByAtlas = false; // ImGui가 폰트 데이터를 소유하지 않도록 설정

    // 메모리에 있는 TTF 폰트 데이터를 ImGui 폰트에 추가
    // rawData: 폰트 데이터 배열의 포인터
    // sizeof(rawData): 폰트 데이터 배열의 크기
    // 18.5f: 폰트 크기
    // &fontConfig: 폰트 설정 구조체 포인터
    // io.Fonts->GetGlyphRangesKorean(): 한글 범위를 지정하는 함수 호출
    io.Fonts->AddFontFromMemoryTTF(rawData, sizeof(rawData), 18.5f, &fontConfig, io.Fonts->GetGlyphRangesKorean());

    ImGuiStyle& style = ImGui::GetStyle(); // ImGui 스타일 객체 가져오기
    // 아래에 디자인 관련 코드를 넣어 주세요.

}