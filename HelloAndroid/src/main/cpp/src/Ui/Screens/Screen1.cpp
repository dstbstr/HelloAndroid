#include "Ui/Screens/Screen1.h"

#include "Ui/Ui.h"
#include "imgui.h"

namespace Ui::Screens::Screen1 {
    bool Initialize() {
        return true;
    }
    void Render() {
        ImGui::Begin("Screen1", nullptr, BaseFlags);
        ImGui::Text("Screen 1");
        ImGui::End();
    }
}