function(build_seminar_examples SEMINAR_DIR)
  message(STATUS "Building examples for seminar ${SEMINAR_DIR}...")

  file(GLOB CPPS "${CMAKE_SOURCE_DIR}/seminars/${SEMINAR_DIR}/*.cpp")

  foreach(CPP IN LISTS CPPS)
    get_filename_component(FILENAME ${CPP} NAME_WE)
    add_executable("seminars-${SEMINAR_DIR}-${FILENAME}" ${CPP})
  endforeach()
endfunction()
