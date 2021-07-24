#!/bin/bash
find uppercase -type f -exec sed -i '' -e 's:#include "[a-z]*\/\([a-z_]*\.h\)":#include "\1":' {} \;