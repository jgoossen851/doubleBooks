# DoubleBooks

A C++ based double-entry bookkeeping and accounting system to record transactions and manage account allocations.

## Dependencies



## Building and Installing the Program

Do the following

```bash
mkdir -p build
cd build/
cmake ..
cmake --build .
make docs
make test || ctest -V
sudo make install
sudo make uninstall
sudo make package
sudo make package_source
```

To install the program without root privileges, run `cmake` as

```bash
cmake -DLocalInstall=YES ..
```

After install, run `sudo touch /usr/share/icons/hicolor/` for to update icons for global install and `mkdir -p ~/.icons && touch ~/.icons` for local install. See [Buglist](./meta/buglist.md).

After generating `package` or `package_source`, run `make uninstall` again to remove installed resources. See [Buglist](./meta/buglist.md).

## Using the Program

Run the program generated in the repository's `bin` directory. Pass the data file to parse as the only argument to the function. From the `build/` directory, run

```bash
../bin/doublebooks ../res/data/TransactionsList.2dblist
```

