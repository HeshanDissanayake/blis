#!/bin/bash
set -e

BUILD_SCRIPT=./build.sh

MC_VALUES=(16 32 64 96 128 256)

for MC in "${MC_VALUES[@]}"; do
  NC=$MC
  for KC in $(seq 64 64 640); do
    echo "========================================"
    echo "Running build: MC=${MC}, NC=${NC}, KC=${KC}"
    echo "========================================"

    ${BUILD_SCRIPT} -m ${MC} -n ${NC} -k ${KC}
  done
done
