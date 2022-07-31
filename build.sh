#!/bin/bash

appPath="$0"
cd $(dirname "$appPath")

mkdir -p build
pushd build

cmake ../

cmake --build .

popd
