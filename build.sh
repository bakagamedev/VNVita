#!/bin/bash
echo $PATH
cmake .
make
zip -r vnvita.vpk assets
zip -r vnvita.vpk sce_sys
rm vnvita.elf