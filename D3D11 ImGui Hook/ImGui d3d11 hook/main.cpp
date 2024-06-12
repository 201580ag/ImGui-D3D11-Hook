#include "includes/includes.h"

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam); // ImGui 핸들러 함수 선언

Present oPresent; // Present 함수 포인터 선언
WNDPROC oWndProc; // 기존 윈도우 프로시저 함수 포인터 선언
ID3D11RenderTargetView* mainRenderTargetView; // Direct3D 11 렌더 타겟 뷰 포인터 변수 선언

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam)) // ImGui 핸들러에 메시지 전달 및 처리 여부 확인
        return true;

    return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam); // 기존 윈도우 프로시저 함수 호출
}

bool init = false; // 초기화 상태 플래그

// Direct3D 11의 Present 함수 후킹된 버전
HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
    // 초기화되지 않은 경우 초기화 수행
    if (!init)
    {
        // 장치 및 컨텍스트 가져오기
        if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice)))
        {
            pDevice->GetImmediateContext(&pContext);

            // 스왑 체인 설정 가져오기
            DXGI_SWAP_CHAIN_DESC sd;
            pSwapChain->GetDesc(&sd);
            window = sd.OutputWindow;

            // 백 버퍼 생성 및 렌더 타겟 뷰 생성
            ID3D11Texture2D* pBackBuffer;
            pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
            pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
            pBackBuffer->Release();

            // 기존 윈도우 프로시저 함수 후킹
            oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);

            // ImGui 초기화
            InitImGui();

            // 초기화 완료 플래그 설정
            init = true;
        }
        else
        {
            // 초기화에 실패하면 기존 Present 함수 호출
            return oPresent(pSwapChain, SyncInterval, Flags);
        }
    }

    ImGuiMenu();

    // 렌더 타겟 설정 및 ImGui 렌더링
    pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
    // 기존 Present 함수 호출
    return oPresent(pSwapChain, SyncInterval, Flags);
}

DWORD WINAPI MainThread(LPVOID lpReserved)
{
    bool init_hook = false; // 후킹 초기화 상태 플래그

    do
    {
        // kiero 초기화 및 D3D11 후킹 시도
        if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success)
        {
            kiero::bind(8, (void**)&oPresent, hkPresent); // Present 함수 후킹
            init_hook = true; // 후킹 초기화 완료 플래그 설정
        }
    } while (!init_hook);

    return TRUE; // 스레드 종료
}

BOOL WINAPI DllMain(HMODULE hMod, DWORD dwReason, LPVOID lpReserved)
{
    switch (dwReason)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hMod); // 스레드 라이브러리 호출 비활성화
        CreateThread(nullptr, 0, MainThread, hMod, 0, nullptr); // 주 스레드 생성
        break;
    case DLL_PROCESS_DETACH:
        kiero::shutdown(); // kiero 라이브러리 종료
        break;
    }

    return TRUE;
}
