# !bin/sh

config=${1:-debug}

# Build the project, bear file should in the directory ../
cd ../
bear -- make config=$config -j4 -C build/gmake2