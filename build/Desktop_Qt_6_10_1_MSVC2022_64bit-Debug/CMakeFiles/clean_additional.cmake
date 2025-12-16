# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\VisioPlot_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\VisioPlot_autogen.dir\\ParseCache.txt"
  "VisioPlot_autogen"
  )
endif()
