# Linky Benchmark

Benchmarking tool for the Linky project

## Usage

Configure what you want to do in `config.env`. Then run :

    sudo ./bin/linky_benchmark

> [!WARNING]
> You have to run with `sudo` as RAPL and other probes require sudo rights. 

## Installation

Make sure that `turbostat` is installed and in your Path. Then, simply run :

    make

## TODO

- [ ] add cpu affinity ro run in only one core
- [ ] format output to enable post processing