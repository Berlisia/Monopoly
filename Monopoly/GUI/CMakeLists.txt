set(MODULE_NAME main_window)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(PUBLIC_HEADERS
    MainWindow.h
)

set(INTERNAL_FILES
    MainWindow.cpp
    MainWindow.ui
)

add_subdirectory(Board)

add_library(${MODULE_NAME}  ${INTERNAL_FILES} ${PUBLIC_HEADERS})
add_library(gui::${MODULE_NAME} ALIAS ${MODULE_NAME})
target_link_libraries(${MODULE_NAME} boardView Qt5::Widgets)

