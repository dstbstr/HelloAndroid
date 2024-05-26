#include "Ui/Screens/Screen2.h"

#include "Ui/Ui.h"
#include "imgui.h"

namespace Ui::Screens::Screen2 {
    bool Initialize() {
        return true;
    }
    void Render() { 
        ImGui::Begin("Screen2", nullptr, BaseFlags);
        ImGui::Text("Screen 2");
        ImGui::End();
    }
}