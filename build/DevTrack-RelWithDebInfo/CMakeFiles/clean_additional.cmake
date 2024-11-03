# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "RelWithDebInfo")
  file(REMOVE_RECURSE
  "CMakeFiles\\DevTrack_Mini_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\DevTrack_Mini_autogen.dir\\ParseCache.txt"
  "DevTrack_Mini_autogen"
  )
endif()
