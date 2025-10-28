cmake_minimum_required(VERSION 3.16)
project(PlatformerSFML)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 69ea0cd863aed1d4092b970b676924a716ff718b
)
FetchContent_MakeAvailable(SFML)

# Add all sources (paths are relative to this CMakeLists.txt in src/)
set(SOURCE_FILES
    main.cpp
    Game.cpp
    GameObject.cpp
    Vector2.cpp
    UImanager.cpp
    PlayingState.cpp
    DayEndState.cpp
    MenuState.cpp
)

set(HEADER_FILES
    Game.h
    GameObject.h
    Vector2.h
    UImanager.h
    PlayingState.h
    DayEndState.h
    MenuState.h
)

add_executable(PlatformerSFML ${SOURCE_FILES} ${HEADER_FILES} "MenuState.cpp" "MenuState.h")

target_link_libraries(PlatformerSFML PRIVATE sfml-graphics sfml-window sfml-system sfml-network sfml-audio)
target_compile_features(PlatformerSFML PRIVATE cxx_std_20)

# Robust Data copying:
# Try a few likely source locations (src/Data, ../Data, root/Data, root/src/Data)
set(POSSIBLE_DATA_DIRS
    "${CMAKE_CURRENT_SOURCE_DIR}/Data"
    "${CMAKE_CURRENT_SOURCE_DIR}/../Data"
    "${CMAKE_SOURCE_DIR}/Data"
    "${CMAKE_SOURCE_DIR}/src/Data"
)

set(DATA_SOURCE "")
foreach(dir IN LISTS POSSIBLE_DATA_DIRS)
    if(EXISTS "${dir}")
        set(DATA_SOURCE "${dir}")
        break()
    endif()
endforeach()

if(DATA_SOURCE)
    message(STATUS "Data folder found at: ${DATA_SOURCE}")
    # Ensure a copy exists in the top-level build directory (${CMAKE_BINARY_DIR}/Data)
    file(COPY "${DATA_SOURCE}" DESTINATION "${CMAKE_BINARY_DIR}/Data")

    # Ensure Data is copied prior to building the target (keeps files up to date while developing)
    add_custom_command(TARGET PlatformerSFML
        PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${DATA_SOURCE}" "${CMAKE_BINARY_DIR}/Data"
    )

    # Also ensure runtime path for the exe's working-dir layout:
    # Executable -> ${CMAKE_BINARY_DIR}/bin ; code uses ../Data -> ${CMAKE_BINARY_DIR}/Data
    # Add a post-build copy to guarantee Data is present relative to the built exe.
    add_custom_command(TARGET PlatformerSFML
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${DATA_SOURCE}" "${CMAKE_BINARY_DIR}/Data"
    )
else()
    message(WARNING "Data directory not found in any of: ${POSSIBLE_DATA_DIRS}. Asset loading will fail until Data is present.")
endif()

if(WIN32)
    # Copy OpenAL from the SFML tree so sound works when building SFML via FetchContent
    if(DEFINED SFML_SOURCE_DIR)
        add_custom_command(
            TARGET PlatformerSFML
            COMMENT "Copy OpenAL DLL to build directory so app can have sound"
            PRE_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
                "${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll"
                "$<TARGET_FILE_DIR:PlatformerSFML>"
            VERBATIM
        )
    endif()
endif()