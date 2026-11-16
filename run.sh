#!/bin/bash
set -euo pipefail

./build.sh "$@"
./build/projet1_nsi
