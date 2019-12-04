find_library(MTK_LIBRARY MetalKit required)
find_library(METAL_LIBRARY Metal required)

add_library(MetalRHI
    MetalRenderer.h
    MetalRenderer.mm
)

set_property(TARGET MetalRHI APPEND_STRING PROPERTY COMPILE_FLAGS "-fobjc-arc")

target_link_libraries(MetalRHI ${MTK_LIBRARY} ${METAL_LIBRARY})

