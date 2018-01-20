kde4_install_icons( ${DATA_INSTALL_DIR}/kamala/icons )

file( GLOB KAMALA_DEFAULT_SVG default/*.svg )

install( FILES ${KAMALA_DEFAULT_SVG}
    DESTINATION ${DATA_INSTALL_DIR}/kamala/themes/default )

