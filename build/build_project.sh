#!/bin/sh

config=${1:-debug}

echo "Building for: " $config    
make clean
bear -- make config=$config
