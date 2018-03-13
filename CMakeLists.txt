cmake_minimum_required(VERSION 3.8)
project(KMintFramework)

# Include custom cmake modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")

# Set C++ standard and debugging leak detector flags
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
set(CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_STATIC_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")

# Find SDL
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

# Setup project directory environment vars
set(INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# List source files recursively
file(GLOB_RECURSE APP_HEADERS
        ${INCLUDE_DIRS}/*.h)
file(GLOB_RECURSE APP_SOURCES
        ${SOURCE_DIR}/*.cpp)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${INCLUDE_DIRS})

# Add project executable and link with SDL
add_executable(${PROJECT_NAME} ${APP_HEADERS} ${APP_SOURCES} src/file_reader.cpp src/file_reader.h  include/Movable_objects/Cow/Cow.cpp include/Movable_objects/Cow/Cow.h include/Movable_objects/Bunny/Bunny.cpp include/Movable_objects/Bunny/Bunny.h a_star/a_star.cpp a_star/a_star.h include/bunny.h include/linal/vector.h src/linal/vector.cpp include/Movable_objects/State/state_object.cpp include/Movable_objects/State/state_object.h include/Movable_objects/State/base_state.h include/Movable_objects/State/wandering_state.cpp include/Movable_objects/State/wandering_state.h include/Movable_objects/State/sleep_state.cpp include/Movable_objects/State/sleep_state.h include/Movable_objects/Sheep/Sheep.cpp include/Movable_objects/Sheep/Sheep.h include/Movable_objects/State/retrieve_state.cpp include/Movable_objects/State/retrieve_state.h include/Movable_objects/Jansen/Mrs_Jansen.cpp include/Movable_objects/Jansen/Mrs_Jansen.h include/Movable_objects/Jansen/Miss_Jansen.cpp include/Movable_objects/Jansen/Miss_Jansen.h include/BunnySpawner.h include/Movable_objects/Bandlit/bandlit.h include/city.cpp include/city.h include/block.h include/city_drawable.cpp include/city_drawable.h)
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})

# Copy assets to build directory
file(COPY resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR})