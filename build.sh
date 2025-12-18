#!/bin/bash
set -e

usage() {
  echo "Usage: $0 -m <MC> -n <NC> -k <KC>"
  echo "All parameters are mandatory."
  exit 1
}

# -----------------------------
# Parse command-line arguments
# -----------------------------
while getopts "m:n:k:h" opt; do
  case ${opt} in
    m ) MC=${OPTARG} ;;
    n ) NC=${OPTARG} ;;
    k ) KC=${OPTARG} ;;
    h ) usage ;;
    \? ) usage ;;
  esac
done

# -----------------------------
# Enforce mandatory arguments
# -----------------------------
if [[ -z "${MC}" || -z "${NC}" || -z "${KC}" ]]; then
  echo "Error: MC, NC, and KC must all be specified."
  usage
fi

echo "Building BLIS with:"
echo "  MC = $MC"
echo "  NC = $NC"
echo "  KC = $KC"
echo

# -----------------------------
# Common build function
# -----------------------------
build_blis () {
  local MR=$1
  local NR=$2

  echo "===> Building MR=${MR}, NR=${NR}"

  python3 make_patch.py patch_templete \
    --out config.patch \
    --MR $MR --NR $NR \
    --MC $MC --KC $KC --NC $NC

  sed -i -f config.patch config/rv64i/bli_cntx_init_rv64i.c
  sed -i -f config.patch kernels/rvi/bli_kernels_rvi.h

  source pre-config.sh

  make clean

  ./configure \
    --prefix="/opt/dev/blis/MC_${MC}_KC_${KC}_NC_${NC}/blis_${MR}x${NR}" \
    rv64i

  make -j32
  sudo make install
}

# -----------------------------
# Build variants
# -----------------------------
build_blis 4  4
build_blis 8  8
build_blis 16 16
