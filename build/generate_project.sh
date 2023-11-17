#!/bin/sh

config=${1:-debug}

premake5 gmake
premake5 export-compile-commands
