SET(LIB_NAME OsgVnc)
SET(PLUGIN_HEADERS
    OsgVnc.h
    VncSceneObject.h
)

ADD_LIBRARY(${LIB_NAME}
    "SHARED"
    ${PLUGIN_HEADERS}
    OsgVnc.cpp
    VncSceneObject.cpp
)

INCLUDE_DIRECTORIES(${OSG_INCLUDE_DIR})
TARGET_LINK_LIBRARIES(${LIB_NAME} ${OSG_LIBRARIES})

INSTALL(TARGETS ${LIB_NAME} DESTINATION lib/plugins)

