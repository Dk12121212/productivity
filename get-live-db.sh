drush @productivity.live sql-dump > now.sql --strict=0
cd www
drush sql-drop -y
drush sql-cli < ../now.sql
drush dis logs_http -y
drush vset composer_manager_file_dir /private/tmp
drush vset composer_manager_vendor_dir profiles/productivity/composer/vendor/
drush vset error_level 2
drush cc all
echo done
