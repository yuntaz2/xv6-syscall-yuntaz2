#! /bin/bash

# Check for argument
if [ $# -eq 0 ]; then
  echo "No arguments supplied. Usage hint: './git-setup.sh <util/syscall/pgtbl/...>'."
  exit 1
fi

# This is a small script for getting setup with git configuration
echo "Setting up repository for branch: $1"

# First, check we have main branch checked out.
echo "Checkout main branch."
git checkout main

# Rebase main with remote lab being run
echo "Rebase lab $1."
git rebase origin/$1

# Pull changes from main
echo "Pull differences from main branch."
git config pull.rebase true
git pull
git config pull.rebase false

# Force push changes to github
echo "Push merged repository."
git push --force

# Script complete!
echo "Repository setup complete!"

