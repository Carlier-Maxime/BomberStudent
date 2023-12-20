cmake_minimum_required(VERSION 3.26)
project(bomberStudent)
set(CMAKE_CXX_STANDARD 17)
include_directories(third_party)
file(GLOB server_src_files "src/bomberStudentServer/*")
file(GLOB client_src_files "src/clientDev/*")
file(GLOB game_src_files "src/game/*")
file(GLOB ipc_src_files "src/ipc/*")
file(GLOB socket_src_files "src/socket/*")
file(GLOB utils_src_files "src/utils/*")
add_executable(bomberStudentServer ${server_src_files}
        ${game_src_files}
        ${ipc_src_files}
        ${socket_src_files}
        ${utils_src_files}
)
add_executable(clientDev ${client_src_files}
        ${game_src_files}
        ${ipc_src_files}
        ${socket_src_files}
        ${utils_src_files}
)
target_link_libraries(bomberStudentServer stdc++fs pthread)
target_link_libraries(clientDev stdc++fs pthread)