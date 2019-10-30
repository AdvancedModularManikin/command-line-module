#############################
# CMake - Command Line Module - root/src
#############################

set(
   COMMAND_LINE_MODULE_SOURCES
   CommandLineModuleMain.cpp
)

add_executable(CommandLineModule ${COMMAND_LINE_MODULE_SOURCES})

target_link_libraries(CommandLineModule PUBLIC amm_std)

target_link_libraries(
   CommandLineModule
   PUBLIC amm_std
   PUBLIC fastcdr
   PUBLIC fastrtps
)
