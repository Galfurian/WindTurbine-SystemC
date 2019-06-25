cmake_minimum_required(VERSION 3.10)
project(WindTurbine)

set(CMAKE_CXX_STANDARD 14)

include_directories(
    src
)

link_directories(
    /usr/local/lib
)

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