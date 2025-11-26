#!/bin/bash

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR"

for preset in release debug lib-only; do
    if [ -d "build/$preset/bin" ]; then
        BUILD_DIR="build/$preset/bin"
        break
    fi
done

if [ -z "$BUILD_DIR" ]; then
    echo "Build not found. Run: ./build.sh"
    exit 1
fi

echo "================================"
echo "   Jellyfish3D - Exemplos"
echo "================================"
echo ""
echo "Escolha um exemplo para executar:"
echo ""
echo "  1 - Sandbox"
echo "  2 - Boids"
echo ""
read -p "Digite sua escolha (1 ou 2): " choice

case $choice in
    1)
        echo ""
        echo "Executando Sandbox..."
        ./$BUILD_DIR/Sandbox
        ;;
    2)
        echo ""
        echo "Executando Boids..."
        ./$BUILD_DIR/Boids
        ;;
    *)
        echo ""
        echo "Opção inválida!"
        exit 1
        ;;
esac
