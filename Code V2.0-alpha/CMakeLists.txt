cmake_minimum_required(VERSION 3.22)
project(client)

set(CMAKE_C_STANDARD 11)

include_directories(code)

add_executable(client
        code/client.c
        code/receiver.c
        code/receiver.h
        code/sender.c
        code/sender.h
	code/encryption.c
        code/encryption.h)

target_link_libraries(client crypto)

project(server)

set(CMAKE_C_STANDARD 11)

include_directories(code)

add_executable(server
        code/server.c
        code/receiver.c
        code/receiver.h
        code/sender.c
        code/sender.h
	code/encryption.c
        code/encryption.h)

target_link_libraries(server crypto)
