#include "includes.h"

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam); // ImGui �ڵ鷯 �Լ� ����

Present oPresent; // Present �Լ� ������ ����
HWND window = NULL; // ������ �ڵ� ���� ���� ���� �� �ʱ�ȭ
WNDPROC oWndProc; // ���� ������ ���ν��� �Լ� ������ ����
ID3D11Device* pDevice = NULL; // Direct3D 11 ��ġ ������ ���� ����
ID3D11DeviceContext* pContext = NULL; // Direct3D 11 ��ġ ���ؽ�Ʈ ������ ���� ����
ID3D11RenderTargetView* mainRenderTargetView; // Direct3D 11 ���� Ÿ�� �� ������ ���� ����

void InitImGui()
{
    ImGui::CreateContext(); // ImGui ���ؽ�Ʈ ����
    ImGuiIO& io = ImGui::GetIO(); // ImGui ����� ��ü ��������
    io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange; // ���콺 Ŀ�� ���� ��Ȱ��ȭ �÷��� ����
    ImGui_ImplWin32_Init(window); // ImGui Win32 �ʱ�ȭ
    ImGui_ImplDX11_Init(pDevice, pContext); // ImGui DirectX 11 �ʱ�ȭ
}

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam)) // ImGui �ڵ鷯�� �޽��� ���� �� ó�� ���� Ȯ��
        return true;

    return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam); // ���� ������ ���ν��� �Լ� ȣ��
}

bool init = false; // �ʱ�ȭ ���� �÷���

// Direct3D 11�� Present �Լ� ��ŷ�� ����
HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
    // �ʱ�ȭ���� ���� ��� �ʱ�ȭ ����
    if (!init)
    {
        // ��ġ �� ���ؽ�Ʈ ��������
        if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice)))
        {
            pDevice->GetImmediateContext(&pContext);

            // ���� ü�� ���� ��������
            DXGI_SWAP_CHAIN_DESC sd;
            pSwapChain->GetDesc(&sd);
            window = sd.OutputWindow;

            // �� ���� ���� �� ���� Ÿ�� �� ����
            ID3D11Texture2D* pBackBuffer;
            pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
            pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
            pBackBuffer->Release();

            // ���� ������ ���ν��� �Լ� ��ŷ
            oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);

            // ImGui �ʱ�ȭ
            InitImGui();

            // �ʱ�ȭ �Ϸ� �÷��� ����
            init = true;
        }
        else
        {
            // �ʱ�ȭ�� �����ϸ� ���� Present �Լ� ȣ��
            return oPresent(pSwapChain, SyncInterval, Flags);
        }
    }

    // ImGui ������ ����
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    // ImGui ������ ������
    ImGui::Begin("ImGui Window");
    ImGui::End();

    ImGui::Render();

    // ���� Ÿ�� ���� �� ImGui ������
    pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    // ���� Present �Լ� ȣ��
    return oPresent(pSwapChain, SyncInterval, Flags);
}

DWORD WINAPI MainThread(LPVOID lpReserved)
{
    bool init_hook = false; // ��ŷ �ʱ�ȭ ���� �÷���

    do
    {
        // kiero �ʱ�ȭ �� D3D11 ��ŷ �õ�
        if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success)
        {
            kiero::bind(8, (void**)&oPresent, hkPresent); // Present �Լ� ��ŷ
            init_hook = true; // ��ŷ �ʱ�ȭ �Ϸ� �÷��� ����
        }
    } while (!init_hook);

    return TRUE; // ������ ����
}

BOOL WINAPI DllMain(HMODULE hMod, DWORD dwReason, LPVOID lpReserved)
{
    switch (dwReason)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hMod); // ������ ���̺귯�� ȣ�� ��Ȱ��ȭ
        CreateThread(nullptr, 0, MainThread, hMod, 0, nullptr); // �� ������ ����
        break;
    case DLL_PROCESS_DETACH:
        kiero::shutdown(); // kiero ���̺귯�� ����
        break;
    }

    return TRUE;
}
