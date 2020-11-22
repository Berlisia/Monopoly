

add_executable(MonopolyTests
    BuildingPropertyFsmTestSuite.cpp
    GoToPrisonTestSuite.cpp
    PlayerTestSuite.cpp
    PropertyModuleTestSuite.cpp
    PublicFaciliiesTestSuite.cpp
    RailwayStationTestSuite.cpp
)

add_subdirectory(Mocks)
add_subdirectory(Fixture)

target_link_libraries(MonopolyTests
    fixture
    mocks
    monopolylib
    player
    building_property
    actors
    game_elements
    common
    gmock
    gtest
    gtest_main
)

add_test( runUnitTests MonopolyTests )
