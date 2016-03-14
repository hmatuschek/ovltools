SET(OVL_DAEMON_SOURCES main.cc echostream.cc qhal.cc sockswhitelist.cc
    application.cc halchat.cc settings.cc httpstatus.cc)
SET(OVL_DAEMON_MOC_HEADERS
    application.hh halchat.hh settings.hh)
SET(OVL_DAEMON_HEADERS ${OVL_DAEMON_MOC_HEADERS}
    echostream.hh qhal.hh sockswhitelist.hh httpstatus.hh)

qt5_wrap_cpp(OVL_DAEMON_MOC_SOURCES ${OVL_DAEMON_MOC_HEADERS})

add_executable(ovldaemon ${OVL_DAEMON_SOURCES} ${OVL_DAEMON_MOC_SOURCES} ${OVL_DAEMON_RCC_SOURCES})
target_link_libraries(ovldaemon ${LIBS})

INSTALL(TARGETS ovldaemon DESTINATION bin)

# Install service script
IF(CMAKE_SYSTEM_NAME MATCHES "Linux")
INSTALL(
  FILES "${CMAKE_SOURCE_DIR}/shared/ovldaemon.conf"
  DESTINATION "/etc/init")
ENDIF(CMAKE_SYSTEM_NAME MATCHES "Linux")


SET(OVL_GENID_SOURCES genid.cc)
add_executable(ovlgenid ${OVL_GENID_SOURCES})
target_link_libraries(ovlgenid ${LIBS})
INSTALL(TARGETS ovlgenid DESTINATION bin)
