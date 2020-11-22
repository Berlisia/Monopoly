set(MODULE_NAME fixture)

set(PUBLIC_HEADERS
    MonopolyGameFixture.h
)
set(INTERNAL_FILES
    MonopolyGameFixture.cpp
)

add_library(${MODULE_NAME} ${PUBLIC_HEADERS} ${INTERNAL_FILES})
target_include_directories(${MODULE_NAME} PUBLIC ./)
target_link_libraries(${MODULE_NAME} actors game_elements)