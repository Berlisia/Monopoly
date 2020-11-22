set(MODULE_NAME mocks)

set(PUBLIC_HEADERS
    DiceMock.h
    DistrictMock.h
    GuestMock.h
    PlayerMock.h
)

add_library(${MODULE_NAME} ${PUBLIC_HEADERS})
target_include_directories(${MODULE_NAME} PUBLIC ./)
target_link_libraries(${MODULE_NAME} actors game_elements gmock gtest gtest_main)