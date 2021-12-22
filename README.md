# DoubleBooks

A C++ based double-entry bookkeeping and accounting system to record transactions and manage account allocations.

## Building and Installing the Program

Do the following

```bash
mkdir -p build
cd build/
cmake ..
cmake --build .
cmake --install .
```

## Using the Program

Run the program generated in the repository's `bin` directory. Pass the data file to parse as the only argument to the function. From the `build/` directory, run

```bash
../bin/budget ../data/TransactionsList.csv
```