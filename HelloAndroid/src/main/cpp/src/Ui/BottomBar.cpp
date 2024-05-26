#include "Ui/BottomBar.h"

#include "Ui/Ui.h"

#include "imgui.h"

namespace Ui::BottomBar {
    bool Initialize() {
        return true;
    }

    void Render() {
        ImGui::Begin("BottomBar", nullptr, BaseFlags);
        ImGui::Text("Bottom Bar");
        ImGui::End();
    }
}