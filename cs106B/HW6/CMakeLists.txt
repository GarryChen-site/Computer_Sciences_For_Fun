project(hw6p)
cmake_minimum_required (VERSION 3.11)

set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ldl -lpthread")

include_directories(lib/StanfordCPPLib)
file(GLOB stanford_files
        "lib/StanfordCPPLib/stacktrace/*.h"
        "lib/StanfordCPPLib/stacktrace/*.cpp"
        "lib/StanfordCPPLib/private/*.h"
        "lib/StanfordCPPLib/private/*.cpp"
        "lib/StanfordCPPLib/*.h"
        "lib/StanfordCPPLib/*.cpp"
        )
add_library(stanford ${stanford_files})

aux_source_directory(src hw6p_SOURCES)

link_libraries(stanford)
add_executable(hw6p ${hw6p_SOURCES})

add_custom_command(TARGET hw6p POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/res
        $<TARGET_FILE_DIR:hw6p>
)


target_link_libraries(${PROJECT_NAME}
        PUBLIC ${Boost_STACKTRACE_BASIC_LIBRARY}
        PUBLIC ${Boost_STACKTRACE_BACKTRACE_LIBRARY}
        PUBLIC ${Boost_STACKTRACE_ADDR2LINE_LIBRARY}
        PUBLIC ${Boost_STACKTRACE_NOOP_LIBRARY}
        PUBLIC pthread dl
)
