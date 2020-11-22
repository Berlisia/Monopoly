set(MODULE_NAME player)

set(PUBLIC_HEADERS
    EventPlayer.h
    Player.h
    PlayerPropertis.h
    StatePlayer.h
    PlayerFsm.h
)

set(INTERNAL_FILES
    Player.cpp
    PlayerFsm.cpp
    PlayerPropertis.cpp
)

add_library(${MODULE_NAME}  ${INTERNAL_FILES} ${PUBLIC_HEADERS})
target_include_directories(${MODULE_NAME} PUBLIC ./)

target_link_libraries(${MODULE_NAME} actors building_property game_elements common)