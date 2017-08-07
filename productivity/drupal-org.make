core = 7.x
api = 2

; Modules
projects[admin_menu][subdir] = "contrib"
projects[admin_menu][version] = "3.0-rc5"

projects[admin_views][subdir] = "contrib"
projects[admin_views][version] = "1.5"

projects[charts][subdir] = "contrib"
projects[charts][version] = "2.x-dev"

projects[ckeditor][subdir] = "contrib"
projects[ckeditor][version] = "1.17"

projects[content_access][subdir] = "contrib"
projects[content_access][version] = "1.2-beta2"

projects[composer_manager][subdir] = "contrib"
projects[composer_manager][version] = "1.8"

projects[ctools][subdir] = "contrib"
projects[ctools][version] = "1.12"

projects[currency][subdir] = "contrib"
projects[currency][version] = "2.6"

projects[country_field][subdir] = "contrib"
projects[country_field][version] = "1.0"

projects[date][subdir] = "contrib"
projects[date][version] = "2.9"

projects[diff][subdir] = "contrib"
projects[diff][version] = "3.2"

projects[entity][subdir] = "contrib"
projects[entity][version] = "1.6"
projects[entity][patch][] = "https://www.drupal.org/files/issues/2086225-entity-access-check-node-create-3.patch"

projects[entityreference][subdir] = "contrib"
projects[entityreference][version] = "1.1"
projects[entityreference][patch][] = "https://www.drupal.org/files/issues/migrate_multiple_entity_reference-2394725-4.patch"

projects[entityreference_autofill][subdir] = "contrib"
projects[entityreference_autofill][version] = "1.2"

projects[entityreference_filter][subdir] = "contrib"
projects[entityreference_filter][version] = "1.5"

projects[entitiesdiagram][type] = "module"
projects[entitiesdiagram][subdir] = "contrib"
projects[entitiesdiagram][download][type] = "git"
projects[entitiesdiagram][download][branch] = "master"
projects[entitiesdiagram][download][url] = "https://github.com/Gizra/entitiesdiagram.git"

projects[gravatar][subdir] = "contrib"
projects[gravatar][version] = "1.1"

projects[flag][subdir] = "contrib"
projects[flag][version] = "3.7"

projects[field_group][subdir] = "contrib"
projects[field_group][version] = "1.5"

projects[field_referenced_delete][subdir] = "contrib"
projects[field_referenced_delete][version] = "1.0"

projects[features][subdir] = "contrib"
projects[features][version] = "2.9"

projects[file_entity][subdir] = "contrib"
projects[file_entity][version] = "2.0-beta3"

projects[github_api][subdir] = "contrib"
projects[github_api][version] = "1.0-beta2"

projects[interval][subdir] = "contrib"
projects[interval][version] = "1.0"

projects[inline_entity_form][subdir] = "contrib"
projects[inline_entity_form][version] = "1.8"

projects[jquery_update][subdir] = "contrib"
projects[jquery_update][version] = "2.7"

projects[libraries][subdir] = "contrib"
projects[libraries][version] = "2.2"

projects[logs_rollbar][type] = "module"
projects[logs_rollbar][subdir] = "contrib"
projects[logs_rollbar][download][type] = "git"
projects[logs_rollbar][download][branch] = "master"
projects[logs_rollbar][download][url] = "https://github.com/Gizra/logs_rollbar.git"

projects[mailsystem][subdir] = "contrib"
projects[mailsystem][version] = "3.x-dev"

projects[message][subdir] = "contrib"
projects[message][version] = "1.11"

projects[message_ui][subdir] = "contrib"
projects[message_ui][version] = "1.4"

projects[message_notify][subdir] = "contrib"
projects[message_notify][version] = "2.5"

projects[message_subscribe][subdir] = "contrib"
projects[message_subscribe][version] = "1.0-rc2"

projects[mimemail][subdir] = "contrib"
projects[mimemail][version] = "1.0-beta4"

projects[module_filter][subdir] = "contrib"
projects[module_filter][version] = "2.0"

projects[money][subdir] = "contrib"
projects[money][version] = "1.x-dev"

projects[multifield][subdir] = "contrib"
projects[multifield][version] = "1.0-alpha4"
projects[multifield][patch][] = "https://www.drupal.org/files/issues/multifield-features-integration-fix-api-2102265-32.patch"
projects[multifield][patch][] = "https://www.drupal.org/files/issues/2041531-23-entity-api-support.patch"
; Fix feature integration.

projects[panels][version] = "3.8"
projects[panels][subdir] = "contrib"

projects[profile2][subdir] = "contrib"
projects[profile2][version] = "1.3"

projects[pathauto][subdir] = "contrib"
projects[pathauto][version] = "1.3"

projects[openid_connect][subdir] = "contrib"
projects[openid_connect][version] = "1.0-beta8"
projects[openid_connect][patch][] = "https://www.drupal.org/files/issues/add_pre_login_hook-2559543-5.patch"

projects[openid_connect_github][subdir] = "contrib"
projects[openid_connect_github][download][type] = "git"
projects[openid_connect_github][download][revision] = 56760f0519882348f48903194699b17ec83def25
projects[openid_connect_github][download][branch] = "7.x-1.x"

projects[restful][subdir] = "contrib"
projects[restful][download][type] = "git"
projects[restful][download][url] = "https://github.com/RESTful-Drupal/restful.git"
projects[restful][download][branch] = "7.x-1.x"

projects[smtp][subdir] = "contrib"
projects[smtp][version] = "1.3"

projects[strongarm][subdir] = "contrib"
projects[strongarm][version] = "2.0"

projects[token][subdir] = "contrib"
projects[token][version] = "1.6"

projects[views][subdir] = "contrib"
projects[views][version] = "3.13"

projects[views_data_export][subdir] = "contrib"
projects[views_data_export][version] = "3.1"

projects[views_bulk_operations][subdir] = "contrib"
projects[views_bulk_operations][version] = "3.3"

projects[views_calc][subdir] = "contrib"
projects[views_calc][version] = "1.1"

; Development
projects[devel][subdir] = "development"
projects[devel][version] = "1.5"

projects[coder][subdir] = "development"
projects[coder][version] = "2.3"

projects[migrate][subdir] = "development"
projects[migrate][version] = "2.8"

projects[migrate_extras][subdir] = "development"
projects[migrate_extras][version] = "2.5"

; Themes
projects[bootstrap][subdir] = "contrib"
projects[bootstrap][version] = "3.5"
projects[bootstrap][type] = "theme"
