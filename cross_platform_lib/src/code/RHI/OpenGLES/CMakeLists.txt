# Currently only android and web use OpenGLES
if(${TARGET_PLATFORM} MATCHES "android")
    add_library(OpenGLESRHI STATIC
        OpenGLESRenderer.hpp
        OpenGLESRenderer.cpp
    )
else()
    add_library(OpenGLESRHI OBJECT
        OpenGLESRenderer.hpp
        OpenGLESRenderer.cpp
    )
endif()
