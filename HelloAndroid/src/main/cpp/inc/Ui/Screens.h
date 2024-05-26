#pragma once

namespace Ui {
    enum struct Screen { Splash, Screen1, Screen2 };

    namespace Screens {
        bool InitializeScreens();
        void RenderActiveScreen();
        void SetActiveScreen(Screen screen);
        Screen GetActiveScreen();
    } // namespace Screens
} // namespace Ui