#!/usr/bin/env bash


################################################################################
#
# This script will sync Danel profile with the platform profile.
#
#
################################################################################

WORKING_DIR="/Applications/MAMP/htdocs/productivity/productivity"
WORKING_DIR_app="/Applications/MAMP/htdocs/productivity/www/app/dist"
PLATFORM_DIR="/Applications/MAMP/htdocs/productivity_pantheon"
ALIAS="@productivity.dev"


rsync -azvr --delete-after --exclude=".git" --exclude=".idea" profiles/ $PLATFORM_DIR
rsync -azvr --delete-after --exclude=".git" --exclude=".idea" $WORKING_DIR_app app/
rsync -azvr --exclude=".git" --exclude=".gitignore" --delete-after profiles/productivity/composer $PLATFORM_DIR/sites/all

# 
# cd $PLATFORM_DIR
# git pull
# git checkout master
# git add .
# git commit -am"Update site"
# git push
# drush $ALIAS uli
# cd $WORKING_DIR
