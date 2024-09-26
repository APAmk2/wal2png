cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("wal2png")
add_executable (wal2png "src/main.cpp" "src/ByteReader.cpp" "src/lodepng.cpp" "src/pcx.cpp" "src/wal.cpp" "external/info.rc")
add_custom_command(TARGET wal2png POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_CURRENT_SOURCE_DIR}/external/colormap.pcx" $<TARGET_FILE_DIR:wal2png>)
set_target_properties(wal2png PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/binaries/debug"
                      RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/binaries/release"
)


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET wal2png PROPERTY CXX_STANDARD 20)
endif()