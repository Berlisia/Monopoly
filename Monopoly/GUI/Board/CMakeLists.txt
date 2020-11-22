set(MODULE_NAME boardView)

set(PUBLIC_HEADERS
    BoardView.hpp
    Field.hpp
)

set(INTERNAL_FILES
    BoardView.cpp
)

add_library(${MODULE_NAME}  ${INTERNAL_FILES} ${PUBLIC_HEADERS})
target_include_directories(${MODULE_NAME} PUBLIC ./)

target_link_libraries(${MODULE_NAME} game_elements Qt5::Widgets)