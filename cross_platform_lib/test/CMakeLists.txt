add_subdirectory(src)

include_directories(src)

if(${TARGET_PLATFORM} MATCHES "desktop")
    add_subdirectory(desktop)
elseif(${TARGET_PLATFORM} MATCHES "ios")
    add_subdirectory(ios)
endif()