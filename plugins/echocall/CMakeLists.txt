SET(OVL_ECHOSERVICE_SOURCES 
    echocallserviceplugin.cc)
SET(OVL_ECHOSERVICE_MOC_HEADERS
    echocallserviceplugin.hh)
SET(OVL_ECHOSERVICE_HEADERS ${OVL_ECHOSERVICE_MOC_HEADERS}
    )

SET(OVL_ECHOSERVICE_META echocallservice.json)

qt5_wrap_cpp(OVL_ECHOSERVICE_MOC_SOURCES ${OVL_ECHOSERVICE_MOC_HEADERS})

add_library(ovlechocall SHARED ${OVL_ECHOSERVICE_SOURCES} ${OVL_ECHOSERVICE_MOC_SOURCES} ${OVL_ECHOSERVICE_RCC_SOURCES})
set_target_properties(ovlechocall PROPERTIES OUTPUTNAME "ovl-echocallservice")
set_target_properties(ovlechocall PROPERTIES MACOSX_RPATH "${OVL_PLUGIN_DIR}")
set_target_properties(ovlechocall PROPERTIES INSTALL_NAME_DIR ${OVL_PLUGIN_DIR})
target_link_libraries(ovlechocall ${LIBS})

add_custom_target(ovlechocallmeta SOURCES ${OVL_ECHOSERVICE_META})

install(TARGETS ovlechocall DESTINATION ${OVL_PLUGIN_DIR})
install(FILES ${OVL_ECHOSERVICE_META} DESTINATION ${OVL_PLUGIN_DIR})
