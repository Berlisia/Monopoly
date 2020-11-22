set(MODULE_NAME game_elements)

set(PUBLIC_HEADERS
    Board.h
    CyclicIterator.h
    Die.h
    Square/BlackHole.h
    Square/Deposite.h
    Square/District.h
    Square/Estate.h
    Square/GoToPrison.h
    Square/Penalty.h
    Square/Prison.h
    Square/Property.h
    Square/PublicFacilities.h
    Square/RandomSquare.h
    Square/RailwayStation.h
    Square/RentPayMode.h
    Square/Reward.h
    Square/Square.h
    Square/Start.h
)

set(INTERNAL_FILES
    Board.cpp
    Square/BlackHole.cpp
    Square/Deposite.cpp
    Square/District.cpp
    Square/Estate.cpp
    Square/GoToPrison.cpp
    Square/Penalty.cpp
    Square/Prison.cpp
    Square/Property.cpp
    Square/PublicFacilities.cpp
    Square/RandomSquare.cpp
    Square/RailwayStation.cpp
    Square/Reward.cpp
    Square/Start.cpp
)

add_library(${MODULE_NAME}  ${INTERNAL_FILES} ${PUBLIC_HEADERS})
target_include_directories(${MODULE_NAME} PUBLIC ./ PUBLIC Square)

target_link_libraries(${MODULE_NAME} common)