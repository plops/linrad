# Linrad Software Review & Implementation Plan

**Client**: Wol Pumba (<wolpumba@gmail.com>)  
**Codebase**: `/workspace/src/linrad`  
**Repository**: [fventuri/linrad](file:///workspace/src/linrad)

---

## 1. Executive Summary & Architectural Review

Linrad is a high-performance Software Defined Radio (SDR) receiving application developed by Leif Åsbrink (SM5BSZ) and maintained by Franco Venturi. It features advanced Digital Signal Processing (DSP) pipelines (FFT, noise blanking, coherent detection, automatic frequency control) implemented in C and optimized x86/x64 NASM assembly.

### Current Architectural State
- **Build System**: Dual build system consisting of legacy autoconf (`./configure` generating `Makefile`) and CMake (`CMakeLists.txt`).
- **Hardware Integration**: Dynamic runtime library loading (`dlopen`/`LoadLibrary`) for numerous SDR hardware backends (Airspy, AirspyHF, bladeRF, RTL-SDR, SDRplay v2/v3, Perseus, Mirics, FDM-S1, Soft66, etc.).
- **Display & UI Layer**: Direct low-level graphics rendering via X11 (`xmain.c`), SVGAlib, or Win32 API.
- **Threading & Synchronization**: POSIX threads (`pthreads`) on Linux/macOS and Win32 threads on Windows.

### Key Quality & Maintainability Observations
1. **Include-Shadowing / Header Isolation**: Header files like `semaphore.h` in the source root shadowed system POSIX headers when included with `-I.`, causing build breaks under modern GCC/CMake without explicit `#include_next` guards.
2. **Automated Testing Coverage**: Historically lacked automated unit/integration tests. The introduction of `tests/test_runner.c` and `run_tests.sh` establishes an initial automated test suite.
3. **Build Tool Standardization**: Dual build paths (`Makefile` vs `CMakeLists.txt`) require synchronization when source files or flags are added.

---

## 2. Requirement Analysis & Proposed Feature Enhancements

### User Requirements Checklist
- [x] Conduct code & architecture review of Linrad in `/workspace/src/linrad`.
- [x] Catalog external dependencies and GitHub organizations in [`deps.md`](file:///workspace/src/linrad/plan/20260807_01_review/deps.md).
- [x] Define Ubuntu Docker container software recommendations for building and testing.
- [x] Provide an Implementation Plan formatted for autonomous AI agents.
- [x] Establish unit & integration test suite (`tests/`) and runner script ([`run_tests.sh`](file:///workspace/src/linrad/run_tests.sh)).
- [x] Create step-by-step task breakdown in [`task.md`](file:///workspace/src/linrad/plan/20260807_01_review/task.md).
- [x] Generate comprehensive post-implementation walkthrough in [`walkthrough.md`](file:///workspace/src/linrad/plan/20260807_01_review/walkthrough.md).

### Recommended Feature Enhancements
1. **Headless Web / Network Stream Mode**: Linrad already contains lightweight web server components ([`html_server.c`](file:///workspace/src/linrad/html_server.c), [`httpd.c`](file:///workspace/src/linrad/httpd.c)). Extending this to support WebSockets or SSE for streaming spectrum/waterfall data will enable headless server deployments.
2. **Modern C11 Standard & Compiler Warning Cleanliness**: Enable `-Wall -Wextra` clean build across both GCC and Clang, replacing legacy C89 constructs with C11 atomics and standard threads where applicable.
3. **CI/CD Container Standardization**: Create an official Dockerfile packaging pre-requisites (`nasm`, `cmake`, `libx11-dev`, `libasound2-dev`, `libusb-1.0-0-dev`, `portaudio19-dev`, `libairspy-dev`, `librtlsdr-dev`, `libbladerf-dev`).

---

## 3. AI Agent Context Files & Source Map

An autonomous AI agent working on this codebase should review the following essential files:

| File | Description & Purpose |
|---|---|
| [`CMakeLists.txt`](file:///workspace/src/linrad/CMakeLists.txt) | Primary CMake configuration for building `clinrad` and running `CTest`. |
| [`Makefile.in`](file:///workspace/src/linrad/Makefile.in) | Template for autoconf `./configure` generating main `Makefile`. |
| [`run_tests.sh`](file:///workspace/src/linrad/run_tests.sh) | Continuous Integration script running `./configure`, `make test`, `cmake`, and `ctest`. |
| [`globdef.h`](file:///workspace/src/linrad/globdef.h) | Central global header containing core constants, type definitions, and OS switches. |
| [`uidef.h`](file:///workspace/src/linrad/uidef.h) | UI, thread index definitions, and user parameters. |
| [`sdrdef.h`](file:///workspace/src/linrad/sdrdef.h) | Hardware sampling rates, USB modes, and device structures. |
| [`semaphore.h`](file:///workspace/src/linrad/semaphore.h) | Win32/POSIX thread semaphore abstraction with `#include_next` guard for Linux system header. |
| [`llsq.c`](file:///workspace/src/linrad/llsq.c) & [`llsqvar.c`](file:///workspace/src/linrad/llsqvar.c) | Linear least squares fitting and DSP windowing algorithms (tested by `test_llsq.c`). |
| [`palette.c`](file:///workspace/src/linrad/palette.c) | Waterfall and spectrum color palette generator (tested by `test_palette.c`). |
| [`vernr.h`](file:///workspace/src/linrad/vernr.h) | Version string declaration (tested by `test_vernr.c`). |
| [`tests/test_runner.c`](file:///workspace/src/linrad/tests/test_runner.c) | Automated test suite entry point executing unit tests. |
| [`plan/20260807_01_review/deps.md`](file:///workspace/src/linrad/plan/20260807_01_review/deps.md) | Catalog of external dependencies and GitHub repositories for DeepWiki lookups. |

---

## 4. Conventional Commit Policy

All commits in this repository MUST strictly follow the Conventional Commits 1.0.0 specification with rich, informative commit messages.

### Format
```text
<type>(<scope>): <short summary in imperative mood>

<detailed explanation of why the change was made, what architectural problem
was solved, design decisions, and how verification was performed>

Fixes / Refs: #<issue-number>
```

### Allowed Commit Types
- `feat`: A new feature added to Linrad (e.g., new SDR hardware support or web API).
- `fix`: A bug fix (e.g., header shadowing in `semaphore.h`).
- `refactor`: Code change that neither fixes a bug nor adds a feature.
- `test`: Adding missing unit tests or refactoring test suites.
- `build`: Changes affecting the build system (`CMakeLists.txt`, `Makefile.in`, `configure`).
- `ci`: Changes to CI scripts (`run_tests.sh`, GitHub Actions workflows).
- `docs`: Documentation updates (`README.md`, `deps.md`, `walkthrough.md`).

---

## 5. Testing & Verification Methodology

Every modification MUST be validated by running the master verification script:

```bash
./run_tests.sh
```

### Verification Pipeline Stages
1. **Autoconf Build**: `./configure && make test` (verifies `xlinrad64` build and standalone C test runner).
2. **CMake Build**: `mkdir -p build && cd build && cmake .. && make clinrad test_runner` (verifies `clinrad` build and CTest harness).
3. **CTest Harness**: `ctest --output-on-failure` (verifies all registered unit test suites).
