set(TARGET_NAME demo)

set(HEADERS
    
)

set(SRCS
    main.cpp
)

message("path:${PATH}")

add_executable(${TARGET_NAME} ${HEADER} ${SRCS})
target_link_libraries(${TARGET_NAME} PUBLIC net)

add_custom_command(TARGET ${TARGET_NAME}
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:net> $<TARGET_FILE_DIR:${TARGET_NAME}>
)