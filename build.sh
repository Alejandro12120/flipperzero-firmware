#!/bin/bash

if [ "$EUID" -ne 0 ] 
    then echo "Please run as root"
    exit
fi

export CUSTOM_FLIPPER_NAME=Bicho
export DIST_SUFFIX=slow-cfw-${CUSTOM_FLIPPER_NAME,,}
BUILD=f7-update-${DIST_SUFFIX}

#./fbt COMPACT=1 DEBUG=0 updater_package -c
./fbt COMPACT=1 DEBUG=0 updater_package
if [[ $? -eq 0 ]]; then 
    cd dist/f7-C
    tar -czvf update.tgz ${BUILD}
fi