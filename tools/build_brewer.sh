#!/bin/bash

GIT_REPO_FULL_PATH=`git rev-parse --show-toplevel 2> /dev/null`

if [ $? -ne 0 ]
then
    echo "ERROR: Not a git repository!"
    echo "       You must run this script from the brewer repository"
    echo "       Exiting..."
    exit 1
fi

GIT_REPO_BASE_DIR_NAME=`basename $GIT_REPO_FULL_PATH 2> /dev/null`

if [ "$GIT_REPO_BASE_DIR_NAME" == "brewer" ]
then
    cd $GIT_REPO_FULL_PATH
    rm -rf ./build
    mkdir build
    cd build
    cmake ../
    make
    ctest
else
    echo "ERROR: Not in brewer repository!"
    echo "       Exiting..."
    exit
fi
