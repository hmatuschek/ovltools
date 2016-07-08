SET(OVL_HALSERVICE_SOURCES qhal.cc
    halchat.cc halchatserviceplugin.cc)
SET(OVL_HALSERVICE_MOC_HEADERS
    halchat.hh halchatserviceplugin.hh)
SET(OVL_HALSERVICE_HEADERS ${OVL_HALSERVICE_MOC_HEADERS}
    qhal.hh)

SET(OVL_HALSERVICE_META halchatservice.json)

qt5_wrap_cpp(OVL_HALSERVICE_MOC_SOURCES ${OVL_HALSERVICE_MOC_HEADERS})

add_library(ovlhalchat SHARED ${OVL_HALSERVICE_SOURCES} ${OVL_HALSERVICE_MOC_SOURCES} ${OVL_HALSERVICE_RCC_SOURCES})
set_target_properties(ovlhalchat PROPERTIES OUTPUTNAME "ovl-halchatservice")
set_target_properties(ovlhalchat PROPERTIES MACOSX_RPATH "${OVL_PLUGIN_DIR}")
set_target_properties(ovlhalchat PROPERTIES INSTALL_NAME_DIR ${OVL_PLUGIN_DIR})
target_link_libraries(ovlhalchat ${LIBS})

add_custom_target(ovlhalchatmeta SOURCES ${OVL_HALSERVICE_META})

install(TARGETS ovlhalchat DESTINATION ${OVL_PLUGIN_DIR})
install(FILES ${OVL_HALSERVICE_META} DESTINATION ${OVL_PLUGIN_DIR})
