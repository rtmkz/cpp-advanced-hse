function(build_seminar_examples SEMINAR_DIR)
  message(STATUS "Building examples for seminar ${SEMINAR_DIR}...")

  file(GLOB CPPS "${CMAKE_SOURCE_DIR}/seminars/2022/${SEMINAR_DIR}/*.cpp")

  foreach(CPP IN LISTS CPPS)
    get_filename_component(FILENAME ${CPP} NAME_WE)
    set(TARGET_NAME "seminars-${SEMINAR_DIR}-${FILENAME}")
    message(STATUS "\tAdding target ${TARGET_NAME}")
    add_executable(${TARGET_NAME} ${CPP})
  endforeach()
endfunction()
