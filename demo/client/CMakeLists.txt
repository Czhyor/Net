set(TARGET_NAME client)

set(HEADERS
    
)

set(SRCS
    main.cpp
)

message("path:${PATH}")

add_executable(${TARGET_NAME} ${HEADER} ${SRCS})

set_target_properties(${TARGET_NAME} PROPERTIES FOLDER "demo")

target_link_libraries(${TARGET_NAME} PUBLIC net)

install(FILES $<TARGET_FILE:net> DESTINATION $<TARGET_FILE_DIR:${TARGET_NAME}>)