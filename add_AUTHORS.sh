#!/bin/bash

# Prompt for contributor information
read -p "Enter contributor's name: " contributor_name
read -p "Enter contributor's email : " contributor_email
read -p "Enter contributor's GitHub username : " contributor_username

current_date=$(date +'%Y-%m-%d')

contributor_entry="$contributor_name"

if [ -n "$contributor_email" ]; then
  contributor_entry+=" <$contributor_email>"
fi

if [ -n "$contributor_username" ]; then
  contributor_entry+=" (https://github.com/$contributor_username)"
fi

# Add the contributor entry to the AUTHORS file
echo "$contributor_entry - $current_date" >> AUTHORS

echo "Contributor added to AUTHORS file."

