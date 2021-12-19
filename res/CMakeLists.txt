cmake_minimum_required(VERSION 3.5.1)

# Set properties for installed program
# TODO:
# Set program name dynamically according to installed program name
set(PROGRAM_NAME "budget")
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
set(DESKTOP_FILE "${PROGRAM_NAME}.desktop")
set(MIME_TYPE_FILE "${PROGRAM_NAME}.xml")
set(PROGRAM_ICON_FILE "${PROGRAM_NAME}.svg")
set(ICON_RESOURCE_I "${MIME_TYPE}-${MIME_SUBTYPE}.svg")

# TODO:
# Make these dynamic so that CPack (possibly) installs these in .../build/_CPackPackages/Linux/*/Budget-x.x.x-Linux/bin (rather than in system?)
# Select Local or Global Installation
#  Local:
#set(SHARE_DIR "$HOME/.local/share")
#set(BIN_DIR "$HOME/.local/bin")
#  Global:
set(SHARE_DIR "/usr/share")
set(BIN_DIR "/usr/local/bin")

# Name paths (could be distro-dependent)
set(DESKTOP_PATH "${SHARE_DIR}/applications")
set(MIME_TYPE_PATH "${SHARE_DIR}/mime/packages")
set(ICON_PATH "${SHARE_DIR}/icons/hicolor/scalable/mimetypes")
set(PROG_ICON_PATH "${SHARE_DIR}/icons/hicolor/scalable/apps")

# Configure resource files
message(STATUS "Configuring Desktop entry")
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/icons/target.desktop.in ${PROJECT_BINARY_DIR}/res/target.desktop)

message(STATUS "Configuring MIME type definition")
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/icons/target.xml.in ${PROJECT_BINARY_DIR}/res/target.xml)


# TODO:
# Create Default applications file if it does not exit
#if [ ! -f $DESKTOP_PATH/defaults.list ]; then
#  $DO echo "[Default Applications]" > $DESKTOP_PATH/defaults.list
#fi

# Install icons
INSTALL(FILES ${CMAKE_CURRENT_SOURCE_DIR}/icons/${PROGRAM_ICON} DESTINATION ${PROG_ICON_PATH} RENAME ${PROGRAM_ICON_FILE})
INSTALL(FILES ${CMAKE_CURRENT_SOURCE_DIR}/icons/${MIME_ICON} DESTINATION ${ICON_PATH} RENAME ${ICON_RESOURCE_I})

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
  execute_process(COMMAND ${UPDATE-ICON-CACHES_EXECUTABLE} ${SHARE_DIR}/icons/\*)
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
#INSTALL(FILES ${CMAKE_CURRENT_SOURCE_DIR}/icons/target.xml DESTINATION ${APP_DESKTOP_DIR})

# Copy the pixmap
#INSTALL(FILES ${CMAKE_CURRENT_SOURCE_DIR}/icons/1059389_wallet_cash_coin_money_pay_icon.svg DESTINATION ${APP_PIXMAPS_DIR})

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
#  execute_process(COMMAND ${XDG-MIME_EXECUTABLE} install --novendor ${CMAKE_CURRENT_SOURCE_DIR}/icons/target.xml)
#  execute_process(COMMAND ${XDG-DESKTOP-MENU_EXECUTABLE} install --novendor ${CMAKE_CURRENT_SOURCE_DIR}/icons/target.desktop)
#  execute_process(COMMAND ${XDG-MIME_EXECUTABLE} default ${CMAKE_CURRENT_SOURCE_DIR}/icons/target.desktop ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/budget)
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
