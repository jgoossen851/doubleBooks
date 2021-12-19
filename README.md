# Project Name (not yet determined)

A C++ program to record transactions, help with budgeting etc.

## Dependencies



## Building and Installing the Program

Do the following

```bash
mkdir -p build
cd build/
cmake ..
cmake --build .
make docs
make test
sudo make install
```

## Using the Program

Run the program generated in the repository's `bin` directory. Pass the data file to parse as the only argument to the function. From the `build/` directory, run

```bash
../bin/budget ../data/TransactionsList.csv
```