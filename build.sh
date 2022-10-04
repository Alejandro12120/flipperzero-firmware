#!/bin/bash

if [ "$EUID" -ne 0 ] 
    then echo "Please run as root"
    exit
fi

export DIST_SUFFIX=slow-cfw

./fbt COMPACT=1 DEBUG=0 updater_package -c
./fbt COMPACT=1 DEBUG=0 updater_package
if [[ $? -eq 0 ]]; then 
    cd dist/f7-C
    tar -czvf update.tgz f7-update-slow-cfw
fi