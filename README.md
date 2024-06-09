# C++ INTERVIEW

## Task

Use `world_bank.json` as data source to print accomplish task below.

Application prints:

* the top 10 regions accorting to ammount of projects done,
* the top 10 regions according to the ammount of investment cost,

Takes as an input the data set provided by the user in the `json` format.

## BUILD

The application is build using `cmake`.

```console
    mkdir build
    cd build
    cmake ..
    make
```

## USE

The application expects as an argument the path to the file.

```console
    ./interview {file-path}
```
