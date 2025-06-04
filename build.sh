#!/bin/bash

OUTPUT="warhammer10k"
SRC_DIRS=(
    "common"
    "controller"
    "model"
    "src"
    "view"
)

# Verificar que g++ esté instalado
command -v g++ >/dev/null 2>&1 || { 
    echo "❌ g++ no está instalado. Por favor instala GCC:"
    echo "   En Ubuntu/Debian: sudo apt install g++"
    echo "   En Fedora: sudo dnf install gcc-c++"
    echo "   En Arch: sudo pacman -S gcc"
    exit 1
}

# Verificar que FLTK esté instalado
command -v fltk-config >/dev/null 2>&1 || { 
    echo "❌ FLTK no está instalado. Ejecutá: sudo apt install libfltk1.3-dev"
    exit 1
}

# Reunir todos los archivos fuente .cpp de las carpetas
SOURCES=()
for dir in "${SRC_DIRS[@]}"; do
    while IFS= read -r -d $'\0' file; do
        SOURCES+=("$file")
    done < <(find "$dir" -name "*.cpp" -print0)
done

if [ ${#SOURCES[@]} -eq 0 ]; then
    echo "❌ No se encontraron archivos .cpp en los directorios fuente"
    exit 1
fi

# Flags
CXX_FLAGS="-std=c++17 -Wall -Wextra"
DEBUG_FLAGS="-g -Og"
INCLUDE_DIRS="-I. -Icommon -Icontroller -Imodel -Isrc -Iview"

# FLTK flags
FLTK_FLAGS=$(fltk-config --cxxflags)
FLTK_LIBS=$(fltk-config --ldflags)
EXTRA_LIBS="-lfltk_images"

echo "🔨 Compilando WARHAMMER10K con backend y frontend (FLTK)..."

# Comando de compilación
g++ "${SOURCES[@]}" $CXX_FLAGS $DEBUG_FLAGS $INCLUDE_DIRS $FLTK_FLAGS $FLTK_LIBS $EXTRA_LIBS -o $OUTPUT

if [ $? -eq 0 ]; then
    echo ""
    echo "✅ Compilado correctamente: ./$OUTPUT"
    
    echo ""
    ./warhammer10k
else
    echo ""
    echo "❌ Error de compilación"
    exit 1
fi
