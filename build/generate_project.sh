#!/bin/sh

config=${1:-debug}

premake5 gmake
bear --append -- make config=$config
