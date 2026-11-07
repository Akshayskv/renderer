#!/bin/bash

SCRIPT_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &> /dev/null && pwd)

cd $SCRIPT_DIR

cmake -S .. -B ../build -G Ninja
