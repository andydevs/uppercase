#!/bin/bash
for file in $(ls uppercase); do
    sed -i -e 's:#include "[a-z]*\/\([a-z_]*\.h\)":#include "\1":' uppercase/$file
done