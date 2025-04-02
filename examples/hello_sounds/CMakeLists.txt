add_executable(svkg_example_hello_sounds main.c)
target_link_libraries(svkg_example_hello_sounds PRIVATE svkg)

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/assets")
    file(GLOB_RECURSE ASSETS "${CMAKE_CURRENT_SOURCE_DIR}/assets/*")
    add_custom_command(TARGET svkg_example_hello_sounds POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory
        $<TARGET_FILE_DIR:svkg_example_hello_sounds>/assets
    )
    foreach(asset ${ASSETS})
        add_custom_command(TARGET svkg_example_hello_sounds POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${asset}
            $<TARGET_FILE_DIR:svkg_example_hello_sounds>/assets
        )
    endforeach()
endif()
