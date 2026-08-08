#!/usr/bin/env bash
set -e

echo "=== Linrad Continuous Integration & Verification Suite (CMake) ==="
echo ""

echo "[1/3] Configuring CMake build..."
cmake -B build -S . -DCMAKE_BUILD_TYPE=Release

echo "[2/3] Building all targets with CMake..."
cmake --build build --config Release

echo "[3/3] Running CTest test suite..."
ctest --test-dir build --output-on-failure

echo ""
echo "=== ALL BUILD AND TEST VERIFICATION STAGES PASSED ==="
