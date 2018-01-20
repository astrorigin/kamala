cmake_minimum_required( VERSION 2.6 )

project( kamala )

find_package( KDE4 REQUIRED )
find_package( Qt4 REQUIRED )
find_package( LibKDEGames REQUIRED )
find_package( Sqlite REQUIRED )

set( ZODIACORE_DIR ./core )
set( SWISSEPH_DIR ./swisseph )
set( KAMALA_DEFINITIONS -DKAMALA )

include( KDE4Defaults )

include_directories(
    ${KDE4_INCLUDES}
    ${KDEGAMES_INCLUDE_DIRS}
    ${SQLITE_INCLUDE_DIR}
    ${ZODIACORE_DIR}
    ${SWISSEPH_DIR} )

set( QT_USE_QTCORE 1 )
set( QT_USE_QTGUI 1 )
set( QT_USE_QTXML 1 )
include( ${QT_USE_FILE} )

add_definitions(
    ${QT_DEFINITIONS}
    ${KDE4_DEFINITIONS}
    ${SQLITE_DEFINITIONS}
    ${KAMALA_DEFINITIONS} )

set( SWISSEPH_SRCS
    ${SWISSEPH_DIR}/swecl.c
    ${SWISSEPH_DIR}/swedate.c
    ${SWISSEPH_DIR}/swehel.c
    ${SWISSEPH_DIR}/swehouse.c
    ${SWISSEPH_DIR}/swejpl.c
    ${SWISSEPH_DIR}/swemmoon.c
    ${SWISSEPH_DIR}/swemplan.c
    #${SWISSEPH_DIR}/swemptab.c
    ${SWISSEPH_DIR}/swepcalc.c
    ${SWISSEPH_DIR}/swepdate.c
    ${SWISSEPH_DIR}/sweph.c
    ${SWISSEPH_DIR}/swephlib.c )

set( ZODIACORE_SRCS
    ${ZODIACORE_DIR}/core.c )

set( KAMALA_SRCS
    actions.cpp
    application.cpp
    dialogs/horoscopedialog.cpp
    dialogs/preferencesdialog.cpp
    items/aspectgraphicsitem.cpp
    items/bunch.cpp
    items/chartgraphicsitem.cpp
    items/cuspgraphicsitem.cpp
    items/planetgraphicsitem.cpp
    items/svgcollection.cpp
    items/zodiacframegraphicsitem.cpp
    items/zodiacgraphicsitem.cpp
    kgeonames/kgeoname.cpp
    kgeonames/kgeonamesbutton.cpp
    kgeonames/kgeonamesdialog.cpp
    kgeonames/kgeonamesquery.cpp
    kgeonames/kgeonameswidget.cpp
    main.cpp
    mainwindow.cpp
    models/chartmodel.cpp
    models/horoscopemodel.cpp
    models/horoscopeproxymodel.cpp
    scenes/chartgraphicsscene.cpp
    translation.cpp
    views/chartview.cpp
    views/chartgraphicsview.cpp
    views/horoscopeview.cpp
    widgets/centralwidget.cpp
    widgets/chartdockwidget.cpp
    widgets/chartwidget.cpp
    widgets/geocoordwidget.cpp
    widgets/orbwidget.cpp
    widgets/searchdockwidget.cpp
    widgets/searchwidget.cpp
    widgets/subwindow.cpp )


add_subdirectory( img )

kde4_add_executable( kamala
    ${SWISSEPH_SRCS}
    ${ZODIACORE_SRCS}
    ${KAMALA_SRCS} )

target_link_libraries( kamala
    ${KDE4_KDECORE_LIBS}
    ${KDE4_KDEUI_LIBS}
    ${KDE4_KIO_LIBS}
    #${KDE4_KROSSCORE_LIBS}
    #${KDE4_KROSSUI_LIBS}
    ${KDEGAMES_LIBRARY}
    ${QT_LIBRARIES}
    ${SQLITE_LIBRARIES}
    m )

install( TARGETS kamala DESTINATION ${BIN_INSTALL_DIR} )

install( FILES kamala.desktop DESTINATION ${XDG_APPS_INSTALL_DIR} )

file( GLOB KAMALA_SQL ${ZODIACORE_DIR}/*.sql )
install( FILES ${KAMALA_SQL} DESTINATION ${DATA_INSTALL_DIR}/kamala )

install( FILES kamalaui.rc DESTINATION ${DATA_INSTALL_DIR}/kamala )

