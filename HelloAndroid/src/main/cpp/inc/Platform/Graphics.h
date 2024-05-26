#pragma once

#include "Platform/Platform.h"
#include "Ui/Ui.h"

#include <utility>

struct Image;
namespace Graphics {
    bool Initialize(Platform& platform);
    void Shutdown();

    void Render();

    void SetFont(const char* fontName, float fontSize);
    bool LoadImage(const char* file, Image& outImage);

    std::pair<int, int> GetScreenSize();
};