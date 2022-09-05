#!/bin/bash

if [ "$EUID" -ne 0 ] 
    then echo "Please run as root"
    exit
fi

./fbt COMPACT=1 DEBUG=0 updater_package -c
./fbt COMPACT=1 DEBUG=0 updater_package
tar -czvf f7-update-local.tgz dist/f7-C/f7-update-local/