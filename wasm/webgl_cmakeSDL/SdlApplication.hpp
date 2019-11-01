#pragma once

#include <SDL2/SDL.h>
#include "BaseApplication.hpp"

namespace newbieGE {
class SdlApplication : public BaseApplication {
   public:
    using BaseApplication::BaseApplication;

    int Initialize() override;
    void Finalize() final;
    // One cycle of the main loop
    void Tick() final;

    void *GetMainWindowHandler() override {
        return m_pWindow;
    };
    void CreateMainWindow() override;

   protected:
    void logSDLError(std::ostream &os, const std::string &msg);
    void onResize(int width, int height);

   protected:
    SDL_Window *m_pWindow;

    bool m_bInDrag = false;
    SDL_GLContext m_hContext;
};
}  // namespace newbieGE
