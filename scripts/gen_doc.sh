#!/bin/bash

cd "$(dirname "$0")"

cd ..

echo "Generating documentation..."
doxygen

echo "Copying HTML files to EngineDocs submodule..."

cp -r docs/html/* EngineDocs

cd EngineDocs

echo "Adding changes to the git submodule..."
git add -A
git commit -m "Update HTML documentation"

echo "Pushing changes to the submodule repository..."
git push origin main

cd ..

echo "Committing the submodule changes in the main project..."
git add EngineDocs
git commit -m "Update EngineDocs submodule with new documentation"
git push origin main

echo "Documentation update complete."
