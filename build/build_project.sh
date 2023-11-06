#!/bin/sh

config={$1:-debug}

bear -- make config=$config
