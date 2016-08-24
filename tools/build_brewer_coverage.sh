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
    rm -rf ./build/*
    mkdir -p build
    cd build
    cmake ../ -DCMAKE_BUILD_TYPE=Coverage
    make -j test_brewer
    ./test/test_brewer
    lcov --capture --directory ./ --output-file coverage.info
    lcov --extract coverage.info "*src/*" -o extracted_coverage.info
    mkdir coverage_reports
    genhtml extracted_coverage.info --output-directory ./coverage_reports
else
    echo "ERROR: Not in brewer repository!"
    echo "       Exiting..."
    exit
fi
