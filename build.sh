# Vytvoří složku build, pokud neexistuje (-p)
mkdir -p build
cd build
cmake ..
make
echo "Hotovo. Program najdete ve složce build/catventure"