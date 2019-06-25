# -----------------------------------------------------------------------------
# Set the minimum CMake version.
# -----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.10)

# -----------------------------------------------------------------------------
# Set project name and language.
# -----------------------------------------------------------------------------
project(WindTurbine CXX)

# -----------------------------------------------------------------------------
# Link directories (where libraries resides).
# -----------------------------------------------------------------------------
link_directories(
    /usr/local/lib
)

# -----------------------------------------------------------------------------
# Include directories.
# -----------------------------------------------------------------------------
include_directories(
    include
)

# -----------------------------------------------------------------------------
# Set the C++ flags.
# -----------------------------------------------------------------------------
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
#SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
#SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wfloat-equal")
#SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic")
#SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic-errors")
#SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g3")
#SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O4")
#SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-narrowing")
#SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-function")
#SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-variable")
#SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")
#SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")
set(CMAKE_CXX_STANDARD 14)

# -----------------------------------------------------------------------------
# Set executable and its sources.
# -----------------------------------------------------------------------------
add_executable(
    ${PROJECT_NAME}
    src/aerodynamic.cpp
    src/battery.cpp
    src/battery_char.cpp
    src/battery_converter.cpp
    src/battery_fre.cpp
    src/battery_voc.cpp
    src/cti_bus.cpp
    src/environment.cpp
    src/generator.cpp
    src/generator_eq.cpp
    src/generator_lsf.cpp
    src/generator_Te.cpp
    src/house1.cpp
    src/house2.cpp
    src/house5.cpp
    src/main.cpp
    src/mechanical.cpp
    src/mechanical_delay.cpp
    src/mechanical_lsf.cpp
    src/mechanical_tdf.cpp
    src/pv_converter.cpp
    src/pv_panel.cpp
    src/turbine.cpp
    src/wind_inverter.cpp
    src/wind_turbine.cpp
)

target_link_libraries(
    ${PROJECT_NAME}
    systemc-ams
    systemc
    dl
)