if(${TARGET_PLATFORM} MATCHES "desktop")
    add_subdirectory(Metal)
elseif(${TARGET_PLATFORM} MATCHES "ios")
    add_subdirectory(Metal)
endif()

