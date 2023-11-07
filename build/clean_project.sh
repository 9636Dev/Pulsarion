#!/bin/sh
rm -rf bin
rm -rf bin-int
rm compile_commands.json
find . -name "Makefile" -type f -delete
find . -name "*.make" -type f -delete
# XCode
find . -name "*.xcodeproj" -type d -exec rm -rf {} +
find . -name "*.xcworkspace" -type d -exec rm -rf {} +
find . -name "*.xcuserstate" -type f -delete
