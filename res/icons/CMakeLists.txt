cmake_minimum_required(VERSION 3.7.1)

# Set properties for installed program
set(PROGRAM_DISPLAY_NAME "Budgeting")
set(PROGRAM_COMMENT "A Short Description of the Budget Program")
set(PROGRAM_ICON "1059389_wallet_cash_coin_money_pay_icon.svg")

# Set properties for associated MIME types
set(MIME_TYPE "application")
set(MIME_SUBTYPE "csv-data-table")
set(MIME_COMMENT "Data Table for budget program")
set(MIME_EXTENSION ".tab")
set(MIME_ICON "Gthumb.svg")

# Set installed file names
get_target_property(PROGRAM_NAME ${PROJECT_NAME} OUTPUT_NAME)
set(DESKTOP_FILE "${PROGRAM_NAME}.desktop")
set(MIME_TYPE_FILE "${PROGRAM_NAME}.xml")
set(PROGRAM_ICON_FILE "${PROGRAM_NAME}.svg")
set(ICON_RESOURCE_I "${MIME_TYPE}-${MIME_SUBTYPE}.svg")

# Add option for local installation
option(LocalInstall "Install locally without root privledges" OFF)

# Set share directory to be a child of install location for any user-input install location
set(SHARE_DIR "${CMAKE_INSTALL_PREFIX}/share")

# TODO:
# Keep CPack from installing the icon resources to the system when creating install targets for package
# Only set the installation location if not given with the --prefix command (CMake 3.15)
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  if(LocalInstall)
    message(STATUS "Configured for Local installation")
    # Change default install location to a local directory not requiring root privledges
    # IF(WINDOWS)
      # set(CMAKE_INSTALL_PREFIX "C:/Users/$ENV{USER}/AppData/Local/Programs/${PROJECT_NAME}" CACHE PATH "..." FORCE)
    # ELSE()
      set(CMAKE_INSTALL_PREFIX "$ENV{HOME}/.local" CACHE PATH "..." FORCE)
    # ENDIF()
    # Update share directory
    set(SHARE_DIR "${CMAKE_INSTALL_PREFIX}/share")
  else()
    # Update default location of global share directory
    # IF(NOT WINDOWS)
      set(SHARE_DIR "${CMAKE_INSTALL_PREFIX}/../share")
    # ENDIF()
  endif()
endif()
message(STATUS "Configured for installation at ${CMAKE_INSTALL_PREFIX}")

# Name paths (could be distro-dependent)
set(DESKTOP_PATH "${SHARE_DIR}/applications")
set(MIME_TYPE_PATH "${SHARE_DIR}/mime/packages")
set(ICON_PATH "${SHARE_DIR}/icons/hicolor/scalable/mimetypes")
set(PROG_ICON_PATH "${SHARE_DIR}/icons/hicolor/scalable/apps")

# Configure resource files
message(STATUS "Configuring Desktop entry")
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/target.desktop.in ${PROJECT_BINARY_DIR}/res/target.desktop)

message(STATUS "Configuring MIME type definition")
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/target.xml.in ${PROJECT_BINARY_DIR}/res/target.xml)


# TODO:
# Create Default applications file if it does not exit
#if [ ! -f $DESKTOP_PATH/defaults.list ]; then
#  $DO echo "[Default Applications]" > $DESKTOP_PATH/defaults.list
#fi

# Install icons
INSTALL(FILES ${CMAKE_CURRENT_SOURCE_DIR}/${PROGRAM_ICON} DESTINATION ${PROG_ICON_PATH} RENAME ${PROGRAM_ICON_FILE})
INSTALL(FILES ${CMAKE_CURRENT_SOURCE_DIR}/${MIME_ICON} DESTINATION ${ICON_PATH} RENAME ${ICON_RESOURCE_I})

# Generate Desktop Entry File
INSTALL(FILES ${PROJECT_BINARY_DIR}/res/target.desktop DESTINATION ${DESKTOP_PATH} RENAME ${DESKTOP_FILE})

# Generate MIME XML File
INSTALL(FILES ${PROJECT_BINARY_DIR}/res/target.xml DESTINATION ${MIME_TYPE_PATH} RENAME ${MIME_TYPE_FILE})

# TODO:
# Append default application for extensions
#echo "$UI_FILE_I_MIME_TYPE/$UI_FILE_I_MIME_SUBTYPE=$DESKTOP_FILE" | \
#$DO tee -a $DESKTOP_PATH/defaults.list > /dev/null
#echo "$UI_FILE_II_MIME_TYPE/$UI_FILE_II_MIME_SUBTYPE=$DESKTOP_FILE" | \
#$DO tee -a $DESKTOP_PATH/defaults.list > /dev/null

# TODO:
# For uninstall target, remove default application for exension
#$DO sed -i "\|^$UI_FILE_I_MIME_TYPE/$UI_FILE_I_MIME_SUBTYPE=$DESKTOP_FILE|d" $DESKTOP_PATH/defaults.list
#$DO sed -i "\|^$UI_FILE_II_MIME_TYPE/$UI_FILE_II_MIME_SUBTYPE=$DESKTOP_FILE|d" $DESKTOP_PATH/defaults.list

# Update Resources
find_program(UPDATE-MIME-DATABASE_EXECUTABLE update-mime-database)
INSTALL(CODE "
  message(STATUS \"Updating MIME database cache\")
  execute_process(COMMAND ${UPDATE-MIME-DATABASE_EXECUTABLE} ${SHARE_DIR}/mime)
")

find_program(UPDATE-ICON-CACHES_EXECUTABLE update-icon-caches)
INSTALL(CODE "
  message(STATUS \"Updating icon cache\")
  execute_process(COMMAND ${UPDATE-ICON-CACHES_EXECUTABLE} \"${SHARE_DIR}/icons/\*\")
")

find_program(UPDATE-DESKTOP-DATABASE_EXECUTABLE update-desktop-database)
INSTALL(CODE "
  message(STATUS \"Updating desktop database cache\")
  execute_process(COMMAND ${UPDATE-DESKTOP-DATABASE_EXECUTABLE} ${SHARE_DIR}/applications)
")





#set(APP_DESKTOP_DIR "/usr/share/applications")
#set(APP_PIXMAPS_DIR "/usr/share/icons/hicolor/scalable/mimetypes")

## Try to set up the menu system
#find_program(XDG-MIME_EXECUTABLE xdg-mime)
#find_program(XDG-DESKTOP-MENU_EXECUTABLE xdg-desktop-menu)

#INSTALL(CODE "
#  message(STATUS \"Update 1\")
#  execute_process(COMMAND ${XDG-MIME_EXECUTABLE} install --novendor ${MIME_TYPE_PATH}/budget.xml)
#  message(STATUS \"Update 2\")
#  execute_process(COMMAND ${XDG-DESKTOP-MENU_EXECUTABLE} install --novendor ${DESKTOP_PATH}/budget.desktop)
#  message(STATUS \"Update 3\")
##  execute_process(COMMAND ${XDG-MIME_EXECUTABLE} default ${DESKTOP_PATH}/budget.desktop budget)
#  "
#)

# TODO:
# Add uninstall instruction to uninstall desktop and mime and remove from default



# Look at contents of these files particularly
#   /usr/share/applications/defaults.list
#   ~/.config/mimeapps.list
# And ensure these are not there anymore
#   /usr/share/mime/packages/budget.xml
#   /usr/share/applications/budget.desktop

# Before uninstalling, run these commands
# # # xdg-mime uninstall /usr/share/mime/packages/budget.xml
# # # xdg-desktop-menu uninstall /usr/share/applications/budget.desktop

# After uninstalling, run these commands
#  sudo update-mime-database /usr/share/mime
#  sudo update-icon-caches /usr/share/icons/*
#  sudo update-desktop-database /usr/share/applications
# and logout-login to see mime-type changes (mimetype .../res/data/*)















#set(APP_DESKTOP_DIR "/usr/share/applications/")
#set(APP_PIXMAPS_DIR "/usr/share/icons/hicolor/scalable/mimetypes")

#INSTALL(FILES ${CMAKE_CURRENT_SOURCE_DIR}/target.desktop DESTINATION ${APP_DESKTOP_DIR})
#INSTALL(FILES ${CMAKE_CURRENT_SOURCE_DIR}/target.xml DESTINATION ${APP_DESKTOP_DIR})

# Copy the pixmap
#INSTALL(FILES ${CMAKE_CURRENT_SOURCE_DIR}/1059389_wallet_cash_coin_money_pay_icon.svg DESTINATION ${APP_PIXMAPS_DIR})

# Try to set up the menu system
##find_program(XDG-MIME_EXECUTABLE xdg-mime)
#find_program(XDG-DESKTOP-MENU_EXECUTABLE xdg-desktop-menu)

#INSTALL(CODE "
#  execute_process(COMMAND ${XDG-MIME_EXECUTABLE} install --novendor ${APP_DESKTOP_DIR}/target.xml)
#  execute_process(COMMAND ${XDG-DESKTOP-MENU_EXECUTABLE} install --novendor ${APP_DESKTOP_DIR}/target.desktop)
#  execute_process(COMMAND ${XDG-MIME_EXECUTABLE} default ${APP_DESKTOP_DIR}/target.desktop ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/budget)
#  "
#)

#INSTALL(CODE "
#  execute_process(COMMAND ${XDG-MIME_EXECUTABLE} install --novendor ${CMAKE_CURRENT_SOURCE_DIR}/target.xml)
#  execute_process(COMMAND ${XDG-DESKTOP-MENU_EXECUTABLE} install --novendor ${CMAKE_CURRENT_SOURCE_DIR}/target.desktop)
#  execute_process(COMMAND ${XDG-MIME_EXECUTABLE} default ${CMAKE_CURRENT_SOURCE_DIR}/target.desktop ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/budget)
#  "
#)

## Add the ws2_32 library if being compiled on Windows
#ifeq ($(OS),Windows_NT)
#   $(info INFO: Compiling for Windows. The ws2_32 library will be linked.)
#   LDLIBS += -lws2_32
#   WINDRES = windres
#else
#   $(info INFO: Compiling for Linux. ws2_32 library is not being linked.)
#   WINDRES = :
#endif

#ifeq ($(OS),Windows_NT)
#ICNS_SRC := $(shell find $(SRC_DIRS) -name "*.rc")
#ICNS := $(ICNS_SRC:%.rc=$(BUILD_DIR)/%.res)
#else
#ICNS := icon
#endif


# Build the target application
#$(OUT_DIR)/$(TARGET_EXEC): $(OBJS) $(ICNS)
#	$(MKDIR_P) $(dir $@)
#	$(ECHO) "\033[32mLinking objects into executable \033[1m$@\033[0m"
#ifeq ($(OS),Windows_NT)
#	$(CC) $(OBJS) $(ICNS) -o $@ $(LDFLAGS) $(LDLIBS)
#else
#	$(CC) $(OBJS) -o $@ $(LDFLAGS) $(LDLIBS)
#endif


#ifeq ($(OS),Windows_NT)
## Windows Resources
#$(BUILD_DIR)/%.res: %.rc
#	$(MKDIR_P) $(dir $@)
#	$(ECHO) "\033[33mCompiling \033[1m$<\033[0m"
#	$(WINDRES) -i $< --input-format=rc -o $@ --output-format=coff
#
#else
## Linux Resources
#.PHONY: icon
#icon:
#	$(ECHO) "\033[33mCompiling \033[1m$<\033[0m"
#	cp res/target.desktop ~/.local/share/applications/
#
#endif
