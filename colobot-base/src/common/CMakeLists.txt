target_sources(Colobot-Base PRIVATE
    config_file.cpp
    config_file.h
    error.h
    event.cpp
    event.h
    font_loader.cpp
    font_loader.h
    global.h
    image.cpp
    image.h
    ioutils.h
    key.cpp
    key.h
    language.cpp
    language.h
    logger.cpp
    logger.h
    profiler.cpp
    profiler.h
    regex_utils.cpp
    regex_utils.h
    restext.cpp
    restext.h
    settings.cpp
    settings.h
    singleton.h
    timeutils.h

    resources/inputstream.cpp
    resources/inputstream.h
    resources/inputstreambuffer.cpp
    resources/inputstreambuffer.h
    resources/outputstream.cpp
    resources/outputstream.h
    resources/outputstreambuffer.cpp
    resources/outputstreambuffer.h
    resources/physfs_utils.cpp
    resources/physfs_utils.h
    resources/resourcemanager.cpp
    resources/resourcemanager.h
    resources/sdl_file_wrapper.cpp
    resources/sdl_file_wrapper.h
    resources/sdl_memory_wrapper.cpp
    resources/sdl_memory_wrapper.h
    resources/sndfile_wrapper.cpp
    resources/sndfile_wrapper.h

    thread/worker_thread.h

    ${PLATFORM_SYSTEM_SOURCES}
)

# Configure files
macro(SetFlag var name)
    if(${var})
        set(${name} "true")
    else()
        set(${name} "false")
    endif()
endmacro()

SetFlag(COLOBOT_OFFICIAL_BUILD CONFIG_OFFICIAL_BUILD)
SetFlag(COLOBOT_DEVELOPMENT_MODE CONFIG_DEVELOPMENT_BUILD)
SetFlag(PORTABLE_SAVES CONFIG_PORTABLE_SAVES)
SetFlag(USE_RELATIVE_PATHS CONFIG_RELATIVE_PATHS)

configure_file(config.h.cmake "${CMAKE_CURRENT_BINARY_DIR}/config.h")
configure_file(version.h.cmake "${CMAKE_CURRENT_BINARY_DIR}/version.h")

target_sources(Colobot-Base PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR}/config.h
    ${CMAKE_CURRENT_BINARY_DIR}/version.h
)
