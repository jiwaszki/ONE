#!/bin/bash

[[ "${BASH_SOURCE[0]}" != "${0}" ]] && echo "Please don't source ${BASH_SOURCE[0]}, execute it" && return

CURRENT_PATH="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT_PATH="$CURRENT_PATH/../../"

# prepare rootfs
if [ -z "$ROOTFS_DIR" ] || [ ! -d $ROOTFS_DIR ]; then
  echo "It will use default rootfs path"
else
  DOCKER_VOLUMES+=" -v $ROOTFS_DIR:/opt/rootfs"
  DOCKER_ENV_VARS+=" -e ROOTFS_ARM=/opt/rootfs"
fi

# mount volume (or directory) for externals
if [ -n "$EXTERNAL_VOLUME" ]; then
  DOCKER_VOLUMES+=" -v $EXTERNAL_VOLUME:/externals"
  DOCKER_ENV_VARS+=" -e EXTERNAL_VOLUME=/externals"
else
  echo "It will use default external path"
fi

DOCKER_ENV_VARS+=" -e BUILD_TYPE=Debug"
DOCKER_ENV_VARS+=" -e BUILD_JOBS=4"

# docker image name
# - for bionic, use DOCKER_IMAGE_NAME="nnfw/one-devtools:bionic"
# - for focal, use DOCKER_IMAGE_NAME="nnfw/one-devtools:focal"
if [[ -z $DOCKER_IMAGE_NAME ]]; then
  echo "It will use default docker image name"
fi

# Mirror server setting
if [[ -z $EXTERNAL_DOWNLOAD_SERVER ]]; then
  echo "It will not use mirror server"
fi

set -e

pushd $ROOT_PATH > /dev/null

export DOCKER_ENV_VARS
export DOCKER_VOLUMES
CMD="make -f ./infra/nncc/Makefile.arm32 cfg debug"
./nncc docker-run bash -c "$CMD"

popd > /dev/null
