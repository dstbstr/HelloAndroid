#include "Ui/Screens.h"
#include "Ui/Screens/Screen1.h"
#include "Ui/Screens/Screen2.h"
#include "Ui/Screens/Splash.h"

namespace {
    auto activeScreen = Ui::Screen::Splash;
}

namespace Ui::Screens {

    bool InitializeScreens() {
        return 
            Screen1::Initialize() &&
            Screen2::Initialize();
    }

    void RenderActiveScreen() {
        switch (activeScreen) {
            case Screen::Splash:
                Splash::Render();
                break;
            case Screen::Screen1:
                Screen1::Render();
                break;
            case Screen::Screen2:
                Screen2::Render();
                break;
        }
    }

    void SetActiveScreen(Screen screen) {
        activeScreen = screen;
    }

    Screen GetActiveScreen() {
        return activeScreen;
    }
}