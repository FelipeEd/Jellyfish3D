#!/bin/bash
set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR"

print_help() {
    echo "Usage: ./build.sh [option]"
    echo ""
    echo "Options:"
    echo "  debug       Build in debug mode (default)"
    echo "  release     Build optimized release"
    echo "  lib-only    Build library only"
    echo "  clean       Remove build directories"
    echo "  deep-clean  Remove all build artifacts and dependencies"
    echo "  help        Show this message"
}

build_project() {
    cmake --preset "$1"
    cmake --build "build/$1" -j$(nproc)
}

preset="${1:-debug}"

case "$preset" in
    debug|release|lib-only)
        build_project "$preset"
        ;;
    clean)
        rm -rf build/
        ;;
    deep-clean)
        echo "Deep cleaning all CMake artifacts..."
        rm -rf build/ _deps/
        find . -type f -name "CMakeCache.txt" -delete
        find . -type f -name "cmake_install.cmake" -delete
        find . -type f -name "compile_commands.json" -delete
        find . -type f -name "Makefile" -delete
        find . -type d -name "CMakeFiles" -exec rm -rf {} + 2>/dev/null || true
        echo "Clean complete!"
        ;;
    help|--help|-h)
        print_help
        ;;
    *)
        echo "Unknown option: $preset"
        print_help
        exit 1
        ;;
esac
