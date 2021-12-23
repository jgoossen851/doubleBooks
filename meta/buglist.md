# Outstanding Bugs #

* [ ] When building the `package` and `package_source` targets, the MIMEs, icons, and desktop entries are still being installed in the user's system. These should only be installed and the commands `update-mime-database`, `update-icon-caches`, and `update-desktop-database` only run, if the user is actually installing the program to use.

* [ ] The `install` target does not always update the MIME-type icons in Nautilus. Apparently, according to [this StackExchange answer](https://unix.stackexchange.com/a/465085), Gtk+ needs to have the icon path modification time (`mtime`) changed to update the icons, which can be done for global installs via

  ```bash
  sudo touch /usr/share/icons/hicolor/
  ```

  and for local installs via

  ```bash
  mkdir -p ~/.icons && touch ~/.icons
  ```

* [ ] Certain files are missing from the source code package after making the target `package_source`. These files include

  * `/res/icons/target.desktop.in`
  * `/meta/ProgramStructure.odp`

* [ ] The `uninstall` target is incomplete. The three commands from the install target should be rerun to update the MIME and Desktop databases and update the icon caches.

* [ ] The command that removes the Install Manifest should be removed from the `uninstall` target. It was added because the Install Manifest required elevated privileges to remove when created with `sudo`, but it does not cause issues for local installations.

* [ ] The files `account.*` should actually be `accountList.*` located in the AccountList library. These files deal with reading avaliable accounts from a CSV and setting up a vector of available accounts. In the Datafields library, there should be `account.*` files that read info from a transactions file (this is why the `setFromStr()` function is needed) and save an iterator to the appropriate account in the AccountList.

# Needed Features

* [ ] Create a Windows installer
* [ ] Allow CSV data table to be delimited by commas (or other punctuation of user's choice). Pass as optional parameter to the function.

