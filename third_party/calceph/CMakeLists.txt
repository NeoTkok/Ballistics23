file(GLOB_RECURSE SOURCEScal *.h *.cpp *.hpp *.c *.h.in)

add_library(calceph STATIC ${SOURCEScal})
message(calceph include dir ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(calceph PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})