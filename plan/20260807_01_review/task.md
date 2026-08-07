# Linrad Codebase Review & Quality Assurance Tasks

This file outlines the sequential task list for inspecting, refactoring, testing, and documenting the Linrad software suite. Each step is independent, serial, and includes explicit verification instructions.

---

## Task 1: Catalog External Dependencies and DeepWiki Mapping
- [x] **Goal**: Identify all external hardware drivers, math libraries, and system dependencies used by Linrad.
- [x] **Action**: Create `plan/20260807_01_review/deps.md` mapping each library to its description and GitHub organization target.
- [x] **Verification**: Verify markdown table layout in [`deps.md`](file:///workspace/src/linrad/plan/20260807_01_review/deps.md).

---

## Task 2: Resolve Header Shadowing in POSIX Builds
- [x] **Goal**: Fix compilation errors caused by local [`semaphore.h`](file:///workspace/src/linrad/semaphore.h) shadowing the glibc `<semaphore.h>` header when built with CMake `-I.`.
- [x] **Action**: Update [`semaphore.h`](file:///workspace/src/linrad/semaphore.h) to check for POSIX/GCC platforms and delegate to `#include_next <semaphore.h>`.
- [x] **Verification**: Run `cd build && cmake .. && make clinrad` and confirm zero header compilation errors.

---

## Task 3: Establish Unit Test Suite and Test Runner
- [x] **Goal**: Add automated unit tests covering core mathematical, version parsing, and palette routines.
- [x] **Action**: Create test modules in `tests/`:
  - [`tests/test_vernr.c`](file:///workspace/src/linrad/tests/test_vernr.c): Linrad version string validation.
  - [`tests/test_palette.c`](file:///workspace/src/linrad/tests/test_palette.c): Color palette allocation verification.
  - [`tests/test_llsq.c`](file:///workspace/src/linrad/tests/test_llsq.c): Parabolic fit and least squares computation verification.
  - [`tests/test_runner.c`](file:///workspace/src/linrad/tests/test_runner.c): Master test suite executor.
- [x] **Verification**: Execute `make test` and confirm all 4 unit test assertions pass.

---

## Task 4: Integrate CTest Harness into CMake Build System
- [x] **Goal**: Wire the unit test suite into `CMakeLists.txt` so that `ctest` runs automatically during CI.
- [x] **Action**: Add `enable_testing()` and `add_test(NAME LinradUnitTests COMMAND test_runner)` in [`CMakeLists.txt`](file:///workspace/src/linrad/CMakeLists.txt).
- [x] **Verification**: Run `cd build && ctest --output-on-failure` and verify 100% pass rate.

---

## Task 5: Implement Automated Master Verification Script
- [x] **Goal**: Provide a single command script ([`run_tests.sh`](file:///workspace/src/linrad/run_tests.sh)) that validates both Autoconf and CMake build paths.
- [x] **Action**: Write [`run_tests.sh`](file:///workspace/src/linrad/run_tests.sh) with `./configure`, `make test`, `cmake`, and `ctest`. Make executable (`chmod +x run_tests.sh`).
- [x] **Verification**: Execute `./run_tests.sh` and verify output displays `=== ALL BUILD AND TEST VERIFICATION STAGES PASSED ===`.

---

## Task 6: Document Implementation & Walkthrough Report
- [x] **Goal**: Create comprehensive Walkthrough report summarizing codebase architectural findings, test results, Docker dependencies, and future recommendations.
- [x] **Action**: Write [`plan/20260807_01_review/walkthrough.md`](file:///workspace/src/linrad/plan/20260807_01_review/walkthrough.md).
- [x] **Verification**: Confirm file presence and completeness in `plan/20260807_01_review/`.
