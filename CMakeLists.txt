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
set(CMAKE_CXX_STANDARD 17)

# -----------------------------------------------------------------------------
# Set executable and its sources.
# -----------------------------------------------------------------------------
add_executable(
    ${PROJECT_NAME}
    src/wind_turbine/aerodynamic/aerodynamic.cpp

    src/battery/battery.cpp
    src/battery/battery_char.cpp
    src/battery/battery_converter.cpp
    src/battery/battery_fre.cpp
    src/battery/battery_voc.cpp

    src/wind_turbine/generator/generator.cpp
    src/wind_turbine/generator/generator_eq.cpp
    src/wind_turbine/generator/generator_lsf.cpp
    src/wind_turbine/generator/generator_Te.cpp

    src/city_power_grid.cpp
    src/wind_turbine/wind.cpp
    src/house.cpp
    src/main.cpp
    src/wind_turbine/mechanical/mechanical.cpp
    src/wind_turbine/mechanical/mechanical_delay.cpp
    src/wind_turbine/mechanical/mechanical_lsf.cpp
    src/wind_turbine/mechanical/mechanical_tdf.cpp
    src/photo_voltaic/pv_converter.cpp
    src/photo_voltaic/pv_panel.cpp
    src/wind_turbine/turbine.cpp
    src/wind_inverter.cpp
    src/wind_turbine/wind_turbine.cpp
)

target_link_libraries(
    ${PROJECT_NAME}
    systemc-ams
    systemc
    dl
)