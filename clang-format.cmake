find_program(
  CLANG_FORMAT_EXE
  NAMES "clang-format"
  DOC "Path to clang-format executable"
  )
if(NOT CLANG_FORMAT_EXE)
  message(STATUS "clang-format not found.")
else()
  message(STATUS "clang-format found: ${CLANG_FORMAT_EXE}")
  set(DO_CLANG_FORMAT ${CLANG_FORMAT_EXE} ${CLANG_FORMAT_ARGS})
endif()

if(CLANG_FORMAT_EXE)
  add_custom_target(
    format
    COMMAND ${DO_CLANG_FORMAT} ${FILES_TO_FORMAT}
  )
endif()
