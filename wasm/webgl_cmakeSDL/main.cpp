#include <unistd.h>
#include <chrono>
#include <functional>

#include <emscripten.h>

std::function<void()> loop;
void main_loop() {
    loop();
}

#include "SdlApplication.hpp"

#include "GraphicsManager.hpp"

using namespace newbieGE;
using namespace std;

int main(int argc, char **argv) {
    int ret;

    GfxConfiguration config(8, 8, 8, 8, 24, 8, 0, 960, 540, "NewbieGameEngine Editor");
    BaseApplication *g_pApp = static_cast<BaseApplication *>(new SdlApplication(config));

    GraphicsManager *g_pGraphicsManager = static_cast<GraphicsManager *>(new GraphicsManager);

    g_pApp->SetCommandLineParameters(argc, argv);

    if ((ret = g_pApp->Initialize()) != 0) {
        cerr << "Failed. err = " << ret;
        return ret;
    }

    if ((ret = g_pGraphicsManager->Initialize()) != 0) {
        cerr << "Failed. err = " << ret;
        return ret;
    }

    g_pApp->CreateMainWindow();

    loop = [&] {
        g_pApp->Tick();
        g_pGraphicsManager->Tick();
    };

    emscripten_set_main_loop(main_loop, 0, true);

    g_pGraphicsManager->Finalize();
    g_pApp->Finalize();

    return ret;
}