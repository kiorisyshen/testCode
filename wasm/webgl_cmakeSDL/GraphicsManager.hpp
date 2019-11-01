#pragma once
#include <unordered_map>
#include <vector>

namespace newbieGE {
enum DefaultShaderIndex {
    BasicShader = 0
};

class GraphicsManager {
   public:
    ~GraphicsManager() = default;

    int Initialize();
    void Finalize();

    void Tick();

    void ResizeCanvas(int32_t width, int32_t height);

    void RenderBuffers();

   protected:
    bool InitializeShaders();

    void BeginScene();
    void EndScene();

   protected:
    bool m_bFinishInit = false;
    uint32_t m_CurrentShader;
    std::unordered_map<int32_t, uint32_t> m_ShaderList;
    std::vector<uint32_t> m_Buffers;
    std::vector<uint32_t> m_VAO;
};

extern GraphicsManager *g_pGraphicsManager;
}  // namespace newbieGE
