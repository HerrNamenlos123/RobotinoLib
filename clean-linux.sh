#!/bin/bash
set -e		# exit on error
SCRIPT_DIR="$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"

echo "Cleaning project..."

rm -rf "$SCRIPT_DIR/bin"
rm -rf "$SCRIPT_DIR/build"

echo "Done"
