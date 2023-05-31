add_executable(line_chart_example line_chart_example.cc)

target_include_directories(
  line_chart_example PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>)
