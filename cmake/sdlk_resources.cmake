function(set_sdlk_resources TARGET)
    set(options)
    set(oneValueArgs DESTINATION)
    set(multiValueArgs FILES DIRECTORIES)

    cmake_parse_arguments(SDLK
        "${options}"
        "${oneValueArgs}"
        "${multiValueArgs}"
        ${ARGN}
    )

    if (NOT SDLK_DESTINATION)
        set(SDLK_DESTINATION "resources")
    endif()

    foreach(file ${SDLK_FILES})
        add_custom_command(TARGET ${TARGET} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${file}
            $<TARGET_FILE_DIR:${TARGET}>/${SDLK_DESTINATION}/user/${file}
        )
    endforeach()

    foreach(dir ${SDLK_DIRECTORIES})
        add_custom_command(TARGET ${TARGET} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${dir}
            $<TARGET_FILE_DIR:${TARGET}>/${SDLK_DESTINATION}/user/${dir}
        )
    endforeach()

    add_custom_command(TARGET ${TARGET} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${SDLK_ENGINE_RESOURCE_DIR}
        $<TARGET_FILE_DIR:${TARGET}>/${SDLK_DESTINATION}/engine
    )
endfunction()