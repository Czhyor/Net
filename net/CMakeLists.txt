set(TARGET_NAME net)

set(HEADERS
    net.h
)

set(SRCS
    net.cpp
)

add_library(${TARGET_NAME} SHARED ${HEADER} ${SRCS})

set_target_properties(${TARGET_NAME} PROPERTIES FOLDER "lib")

target_compile_definitions(${TARGET_NAME} PRIVATE NET_LIBRARY)
target_include_directories(${TARGET_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${TARGET_NAME} PUBLIC
    WS2_32.lib
)