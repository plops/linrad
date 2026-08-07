#!/usr/bin/env bash
set -e

echo "=== Linrad Continuous Integration & Verification Suite ==="
echo ""

echo "[1/4] Running ./configure..."
./configure

echo "[2/4] Building xlinrad64 and running Makefile test suite..."
make test

echo "[3/4] Configuring CMake build directory..."
mkdir -p build
cd build
cmake ..

echo "[4/4] Building clinrad and running CTest suite..."
make test_runner clinrad
ctest --output-on-failure

echo ""
echo "=== ALL BUILD AND TEST VERIFICATION STAGES PASSED ==="
