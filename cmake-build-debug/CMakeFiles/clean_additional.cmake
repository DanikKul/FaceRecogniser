# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/rec_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/rec_autogen.dir/ParseCache.txt"
  "rec_autogen"
  )
endif()
