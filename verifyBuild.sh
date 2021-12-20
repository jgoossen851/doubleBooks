
sudo rm -rf build/    || { echo -e "\e[31mFailed to remove build dir\e[0m"; exit; }
mkdir build/          || { echo -e "\e[31mFailed to make build dir\e[0m"; exit; }
pushd build/          || { echo -e "\e[31mFailed to enter build dir\e[0m"; exit; }

cmake ..              || { echo -e "\e[31mFailed to generate Makefile\e[0m"; popd; exit; }
cmake --build .       || { echo -e "\e[31mFailed to build project\e[0m"; popd; exit; }
make docs             || { echo -e "\e[31mFailed to build documentation\e[0m"; popd; exit; }
make test             || { echo -e "\e[31mFailed to run tests\e[0m"; popd; exit; }
sudo make install     || { echo -e "\e[31mFailed to install executable\e[0m"; popd; exit; }
sudo make uninstall   || { echo -e "\e[31mFailed to uninstall executable\e[0m"; popd; exit; }
sudo make package     || { echo -e "\e[31mFailed to package binary\e[0m"; popd; exit; }
sudo make package_source   || { echo -e "\e[31mFailed to package source\e[0m"; popd; exit; }

popd
