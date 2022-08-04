add_executable(Plotter plotter.cc)

target_include_directories(Plotter PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>)