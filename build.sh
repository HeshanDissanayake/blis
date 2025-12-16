#!/bin/bash
MR=16
NR=16
MC=32
KC=32
NC=32


python3 make_patch.py patch_templete --out config.patch --MR $MR --NR $NR --MC $MC --KC $KC --NC $NC

sed -i -f config.patch config/rv64i/bli_cntx_init_rv64i.c
sed -i -f config.patch kernels/rvi/bli_kernels_rvi.h

source pre-config.sh

make clean

./configure --prefix="/opt/dev/blis/MC_${MC}_KC_${KC}_NC_${NC}/blis_${MR}x${NR}" rv64i
make -j32
sudo make install
