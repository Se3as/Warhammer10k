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

# Encontrar todos los archivos .cpp en los directorios fuente
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

# Flags de compilación
CXX_FLAGS="-std=c++11 -Wall -Wextra"
DEBUG_FLAGS="-g"  # Opciones de depuración
INCLUDE_DIRS="-I. -Icommon -Icontroller -Imodel -Isrc -Iview"  # Todos los directorios de includes

echo "🔨 Compilando WARHAMMER10K..."
#echo "📝 Archivos fuente encontrados:"
#printf '• %s\n' "${SOURCES[@]}"

echo ""
echo "🚀 Corriendo..."

# Comando de compilación
g++ "${SOURCES[@]}" $CXX_FLAGS $DEBUG_FLAGS $INCLUDE_DIRS -o $OUTPUT

if [ $? -eq 0 ]; then
    echo ""
    echo "✅ Compilado correctamente: ./$OUTPUT"
    
    # Ejecutar el programa automáticamente
    echo ""
    ./$OUTPUT
else
    echo ""
    echo "❌ Error de compilación"
    exit 1
fi