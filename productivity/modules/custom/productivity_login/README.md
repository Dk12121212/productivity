# Productivity Login

Logging in to Productivity is supported via two methods:
 * authenticating against Drupal database
 * authenticating via GitHub, using OAuth web workflow

To use OAuth, do the following:
 * register your app at Github: https://github.com/settings/applications/new
 * provide secrets via already existing settings.php variables: `github_public`
   and `github_secret`
