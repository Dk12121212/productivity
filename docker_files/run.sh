#!/usr/bin/env bash

# Configure apache2.
echo -e "\n [RUN] Configure apache2."
cp docker_files/default.apache2.conf /etc/apache2/apache2.conf
service apache2 restart

# Start MySQL.
echo -e "\n [RUN] Start MySQL."
service mysql start

# Before install.
echo "\r\n [RUN] Updating system ...\r\n"
apt-get -qq update
echo -e "\n [RUN] Composer self-update."
composer self-update

# Install NodeJS
echo -e "\n [RUN] Install NodeJS."
curl -sL https://deb.nodesource.com/setup_5.x | bash -
apt-get install -y -qq nodejs


# Install php packages required for running a web server from drush on php 5.3
echo -e "\n [RUN] Install php packages."
apt-get install -y --force-yes -qq php5-cgi -qq php5-mysql
# Fix error sending mails.
echo 'sendmail_path = /bin/true' >> /etc/php.ini

# Install Drush & create alias.
echo -e "\n [RUN] Install Drush."
export PATH="$HOME/.composer/vendor/bin:$PATH"
composer global require drush/drush:7.*
cd /var/www/html/productivity
mkdir ~/.drush/
cp docker_files/aliases.drushrc.php ~/.drush/aliases.drushrc.php
source /root/.bashrc

# Installation profile.
echo -e "\n [RUN] Installation profile."
cp default.config.sh config.sh
./install -dy

#install DOMPDF
echo -e "\n [RUN] Install DOMPDF"
cd /var/www/html/productivity/productivity/libraries/dompdf
composer install --no-interaction --prefer-source

#Run SimpleTest
echo "Run SimpleTest."
export PATH="$HOME/.composer/vendor/bin:$PATH"
drush @productivity en simpletest -y
cd /var/www/html/productivity
php ./www/scripts/run-tests.sh --php $(which php) --concurrency 4 --verbose --color --url http://localhost Productivity 2>&1 | tee /tmp/simpletest-result.txt
egrep -i "([1-9]+ fail)|(Fatal error)|([1-9]+ exception)" /tmp/simpletest-result.txt && exit 1

# Install Firefox (iceweasel)
echo -e "\n [RUN] Installing Firefox."
apt-get -y install -qq iceweasel

# Install Selenium.
echo -e "\n [RUN] Installing Selenium."
# Create folder to place selenium in
echo -e "\n [RUN] Creating folder to place selenium in.\n"
mkdir ~/selenium
cd ~/selenium

# Get Selenium and install headless Java runtime
echo -e "\n [RUN] Installing Selenium and headless Java runtime.\n"
wget http://selenium-release.storage.googleapis.com/2.53/selenium-server-standalone-2.53.0.jar
cd /var/www/html/productivity/productivity
apt-get install -qq openjdk-7-jre-headless -y

# Install headless GUI for browser.'Xvfb is a display server that performs graphical operations in memory'
echo -e "\n [RUN] Installing XVFB (headless GUI for Firefox).\n"
# on mac use instruction here:
# http://stackoverflow.com/questions/18868743/how-to-install-selenium-webdriver-on-mac-os
# and put in behat dir this: https://github.com/mozilla/geckodriver/releases
apt-get install -qq xvfb -y

# Install Behat for backend.
echo -e "\n [RUN] Install Behat for back end."
cd /var/www/html/productivity/productivity/behat
curl -sS https://getcomposer.org/installer | php
php composer.phar update
cp behat.local.docker.yml behat.local.yml
cd ../..

# Start up Selenium server
echo -e "\n [RUN] Starting up Selenium server.\n"
DISPLAY=:1 xvfb-run java -jar ~/selenium/selenium-server-standalone-2.53.0.jar > ~/sel.log 2>&1 &


# Output server logs:
echo -e "\n [RUN] Look at my Selenium log: \n"
cat ~/sel.log

cd /var/www/html/productivity

# Run Behat tests.
echo -e "\n [RUN] Start tests.\n"
cd productivity/behat && ./bin/behat --tags=~@wip
