set(MODULE_NAME building_property)

set(PUBLIC_HEADERS
    BuildingMachine.h
    BuildingObserver.h
    BuildingProperty.h
    BuildingPropertyFsm.h
    EventVariant.h
    HouseDevelop.h
    MortgageBuildingState.h
    StateVariant.h
    SubjectBuildingProperty.h
)

set(INTERNAL_FILES
    BuildingProperty.cpp
    BuildingPropertyFsm.cpp
    SubjectBuildingProperty.cpp
)

add_library(${MODULE_NAME}  ${INTERNAL_FILES} ${PUBLIC_HEADERS})
target_include_directories(${MODULE_NAME} PUBLIC ./)

target_link_libraries(${MODULE_NAME} game_elements common)
