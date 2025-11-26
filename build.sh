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
    echo "  help        Show this message"
}

build_project() {
    cmake -S . -B "build/$1" --preset "$1"
    cmake --build "build/$1" -j$(nproc)
}

case "${1:-debug}" in
    debug|release|lib-only)
        build_project "$1"
        ;;
    clean)
        rm -rf build/
        ;;
    help|--help|-h)
        print_help
        ;;
    *)
        echo "Unknown option: $1"
        print_help
        exit 1
        ;;
esac
