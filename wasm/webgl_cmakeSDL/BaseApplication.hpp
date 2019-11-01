#pragma once
#include "GfxConfiguration.hpp"

namespace newbieGE {
class BaseApplication {
   public:
    BaseApplication(GfxConfiguration &cfg);
    virtual int Initialize();
    virtual void Finalize();
    // One cycle of the main loop
    virtual void Tick();

    void SetCommandLineParameters(int argc, char **argv);
    int GetCommandLineArgumentsCount() const;
    const char *GetCommandLineArgument(int index) const;

    bool IsQuit() const;
    void RequestQuit() {
        m_bQuit = true;
    }

    inline const GfxConfiguration &GetConfiguration() const {
        return m_Config;
    };

    virtual void CreateMainWindow() {
    }
    virtual void *GetMainWindowHandler() {
        return nullptr;
    }

   protected:
    // Flag if need quit the main loop of the application
    static bool m_bQuit;
    GfxConfiguration m_Config;
    int m_nArgC;
    char **m_ppArgV;

   private:
    // hide the default construct to enforce a configuration
    BaseApplication(){};
};
}  // namespace newbieGE
