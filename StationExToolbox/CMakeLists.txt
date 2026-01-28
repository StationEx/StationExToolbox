add_library(StationExToolboxLib STATIC
    WorldXmlDocument.cpp
    StructureSaveData.cpp
    ThingSaveData.cpp
    EntitySaveData.cpp
    WorldXmlReader.cpp
    HumanSaveData.cpp
    DynamicThingSaveData.cpp
)

target_include_directories(StationExToolboxLib PUBLIC
        ${RAPIDXML_INCLUDE_DIR}
        ${ARGS_INCLUDE_DIR}
)

if (MSVC)
    target_compile_options(StationExToolboxLib PRIVATE /W4)
else()
    target_compile_options(StationExToolboxLib PRIVATE -Wall -Wextra -Wpedantic)
endif()

if (EMSCRIPTEN)
  add_executable(StationExToolbox StationExToolboxWASM.cpp)
  set_target_properties(StationExToolbox PROPERTIES
      OUTPUT_NAME "StationExToolbox"
      SUFFIX ".js"
  )
  target_link_options(StationExToolbox PUBLIC
      "-sMODULARIZE=1"
      "-sEXPORT_ES6=1"
      "-sALLOW_MEMORY_GROWTH=1"
      "-sENVIRONMENT=web,worker,node"
      "--bind"
  )
else(EMSCRIPTEN)
  add_executable(StationExToolbox StationExToolbox.cpp)
endif(EMSCRIPTEN)

target_link_libraries(StationExToolbox PRIVATE StationExToolboxLib)

