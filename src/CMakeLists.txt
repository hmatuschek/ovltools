SET(OVL_DAEMON_SOURCES main.cc
    daemon.cc settings.cc)
SET(OVL_DAEMON_MOC_HEADERS
    daemon.hh settings.hh)
SET(OVL_DAEMON_HEADERS ${OVL_DAEMON_MOC_HEADERS}
    )

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
