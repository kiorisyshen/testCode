#pragma once
#include "GfxConfiguration.hpp"

namespace newbieGE {
class BaseApplication {
   public:
    BaseApplication(GfxConfiguration &cfg);
    virtual int Initialize();
    virtual void Finalize() = 0;
    // One cycle of the main loop
    virtual void Tick() = 0;

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

    virtual void CreateMainWindow()      = 0;
    virtual void *GetMainWindowHandler() = 0;

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
