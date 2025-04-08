project(hw2w)
cmake_minimum_required (VERSION 3.11)

set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ldl -lpthread")

include_directories(lib/StanfordCPPLib)
file(GLOB stanford_files
        "lib/StanfordCPPLib/*.h"
        "lib/StanfordCPPLib/*.cpp"
        "lib/StanfordCPPLib/stacktrace/*.h"
        "lib/StanfordCPPLib/stacktrace/*.cpp"
        "lib/StanfordCPPLib/private/*.h"
        "lib/StanfordCPPLib/private/*.cpp"
        )
add_library(stanford ${stanford_files})

aux_source_directory(src hw2w_SOURCES)

link_libraries(stanford)
add_executable(hw2w ${hw2w_SOURCES})

target_link_libraries(${PROJECT_NAME}
        PUBLIC ${Boost_STACKTRACE_BASIC_LIBRARY}
        PUBLIC ${Boost_STACKTRACE_BACKTRACE_LIBRARY}
        PUBLIC ${Boost_STACKTRACE_ADDR2LINE_LIBRARY}
        PUBLIC ${Boost_STACKTRACE_NOOP_LIBRARY}
        PUBLIC pthread dl
)
