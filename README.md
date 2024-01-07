 # ImGui-d3d11-hook

**`ImGui Hook`을 학습할 수 있는 곳입니다.**  
[학습 영상](https://www.youtube.com/watch?v=4659KaH4ON8)  
[레포지토리 링크](https://github.com/rdbo/ImGui-DirectX-11-Kiero-Hook)  

**디자인,폰트 관련 레포지토리:**  
[디자인](https://github.com/GraphicsProgramming/dear-imgui-styles)  
[폰트 적용 관련 도움](https://dlemrcnd.tistory.com/650)  
[현재 적용된 폰트(나눔 폰트)](https://hangeul.naver.com/font)  
> 지금 `font.h` 안에 있는 폰트는 `NanumGothic.ttf` 입니다.

**폰트 적용 방법** 
```
1. `HxD` 를설치한다.
2. 원하는 폰트를 다운 받는다.(.ttf)
3. HxD 에 폰트(.ttf) 파일을 넣는다.
4. 그리고 저장 또는 클립보드 복사를 C 형식으로 한다.
5. 복사나 저장한 C로 변환된 폰트를 `font.h` 안에 넣는다.
```

**한글 출력 방법** 
```
`u8`을 붙혀준다.
예) ImGui::Begin(u8"테스트");
    ImGui::Button(u8"테스트 버튼");
    ImGui::Text(u8"테스트 텍스트");
> u8은 C++11 이상에서 도입된 UTF-8 인코딩의 문자열 리터럴 표기법    
```

**디자이너 레포지토리 및 웹 버전:**  
[디자이너 레포지토리 링크](https://github.com/Raais/ImStudio)  
[웹 버전 링크](https://raais.github.io/ImStudio)  

# 예제 목록
**현재 시간, 날짜 출력 예제** 
```cpp
    ImGui::NewFrame();
    // 현재시간, 날짜 ImGui 창
    ImGui::SetNextWindowSize(ImVec2(200, 50));  // 창 크기 고정
    ImGui::Begin(u8"현재 시간", NULL, 135);

    // 실시간으로 시간을 업데이트
    std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    struct tm localTime;
    localtime_s(&localTime, &now);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &localTime);
    std::string timeString(buffer);

    // 실시간으로 업데이트된 시간을 검은색으로 표시
    ImGui::TextColored(ImVec4(0, 0, 0, 1), u8"현재 시간: %s", timeString.c_str());

    ImGui::End();
```

**현재 FPS를 출력하는 예제** 
```cpp
// 어플리케이션의 FPS를 측정하기 위한 변수들
std::chrono::time_point<std::chrono::high_resolution_clock> lastFrameTime;
int frameCount = 0;
float fps = 0.0f;

// 렌더 타겟 설정 및 ImGui 렌더링
pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);

// 어플리케이션의 FPS 측정 및 표시
auto currentFrameTime = std::chrono::high_resolution_clock::now();
std::chrono::duration<float> deltaTime = currentFrameTime - lastFrameTime;
frameCount++;
if (deltaTime.count() >= 1.0f) {
fps = static_cast<float>(frameCount) / deltaTime.count();
frameCount = 0;
lastFrameTime = currentFrameTime;
}

// FPS를 ImGui 창에 표시
ImGui::SetNextWindowPos(ImVec2(0, 30));  // 창 위치를 좌측 상단으로 설정
ImGui::Begin(u8"어플리케이션 FPS", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | NULL | 129);
ImGui::TextColored(ImVec4(0, 0, 0, 1), u8"FPS: %.5f", fps);
ImGui::End();
```

**화면 정중앙에 빨간점을 표시하는 예제** 
```cpp
    ImGui::NewFrame();

    // 화면 정중앙에 빨간 원을 그리기
    ImVec2 center = ImVec2(ImGui::GetIO().DisplaySize.x * 0.5f, ImGui::GetIO().DisplaySize.y * 0.5f);
    float radius = 5.0f;
    ImU32 redColor = IM_COL32(255, 0, 0, 255);
    ImGui::GetBackgroundDrawList()->AddCircleFilled(center, radius, redColor);

    // ImGui 렌더링
    ImGui::Render();
```
