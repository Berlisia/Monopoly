set(MODULE_NAME common)

set(PUBLIC_HEADERS
    FsmVariant.h
    Guest.h
)

set(INTERNAL_FILES
)

add_library(${MODULE_NAME}  ${INTERNAL_FILES} ${PUBLIC_HEADERS})
target_include_directories(${MODULE_NAME} PUBLIC ./)
