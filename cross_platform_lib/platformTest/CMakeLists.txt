
if(${TARGET_PLATFORM} MATCHES "desktop")
    add_subdirectory(desktop)
elseif(${TARGET_PLATFORM} MATCHES "ios")
    # Directly use generated workspace
    # add_subdirectory(ios)
endif()