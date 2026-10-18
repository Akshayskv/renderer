#!/bin/bash

SCRIPT_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &> /dev/null && pwd)
cd $SCRIPT_DIR
BUILD_DIR="../build"

if [ ! -d "$BUILD_DIR" ]; then
	echo -e "Build directory not found\nRunning cmake..."
	cmake -S .. -B ../build -G Ninja
fi

echo "Compiling..."
ninja -C "../build/"

exec $BUILD_DIR/renderer
