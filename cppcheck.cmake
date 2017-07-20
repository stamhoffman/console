find_program(
  CPPCHECK_EXE
  NAMES "cppcheck"
  DOC "Path to cppcheck executable"
  )
if(NOT CPPCHECK_EXE)
  message(STATUS "cppcheck not found.")
else()
  message(STATUS "cppcheck found: ${CPPCHECK_EXE}")
  set(DO_CPPCHECK_FORMAT ${CPPCHECK_EXE} ${CPPCHEK_ARGS})
endif()

if(CPPCHECK_EXE)
  add_custom_target(
    check
    COMMAND ${DO_CPPCHECK_FORMAT} ${FILES_TO_CHECK}
  )
endif()
