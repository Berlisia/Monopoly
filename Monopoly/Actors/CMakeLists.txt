set(MODULE_NAME actors)

set(PUBLIC_HEADERS
    Bank.h
    Bankier.h
    Contestant.h
    PlayerStatus.h
)

set(INTERNAL_FILES
    Bankier.cpp
    PlayerStatus.cpp
)

add_library(${MODULE_NAME}  ${INTERNAL_FILES} ${PUBLIC_HEADERS})
target_include_directories(${MODULE_NAME} PUBLIC ./)

target_link_libraries(${MODULE_NAME} game_elements)
