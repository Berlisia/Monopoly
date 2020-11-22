
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(Qt5_DIR "/usr/lib/x86_64-linux-gnu/cmake/Qt5/")

find_package(Qt5 COMPONENTS Widgets REQUIRED)

# The Qt5Widgets_INCLUDES also includes the include directories for
# dependencies QtCore and QtGui
include_directories(${Qt5Widgets_INCLUDES})

# We need add -DQT_WIDGETS_LIB when using QtWidgets in Qt 5.
add_definitions(${Qt5Widgets_DEFINITIONS})

# set up a mapping so that the Release configuration for the Qt imported target is
# used in the COVERAGE CMake configuration.
set_target_properties(Qt5::Core PROPERTIES MAP_IMPORTED_CONFIG_COVERAGE "RELEASE")

add_executable(Monopoly
    GUI/Resources/resources.qrc
    MonopolyGame.cpp
    main.cpp
)

add_subdirectory(GUI)
add_subdirectory(Common)
add_subdirectory(GameElements)
add_subdirectory(Actors)
add_subdirectory(BuildingProperty)
add_subdirectory(Player)

target_link_libraries(Monopoly
    player
    building_property
    actors
    game_elements
    common
    gui::main_window
    Qt5::Widgets
)

set(MODULE_NAME monopolylib)
set(PUBLIC_HEADERS
    MonopolyGame.h
)

set(INTERNAL_FILES
    MonopolyGame.cpp
)

add_library(${MODULE_NAME}  ${INTERNAL_FILES} ${PUBLIC_HEADERS})
target_link_libraries(${MODULE_NAME}
    player
    building_property
    actors
    game_elements
    common
    gui::main_window
    Qt5::Widgets
)

