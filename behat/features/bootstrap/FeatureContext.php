<?php

use Drupal\DrupalExtension\Context\DrupalContext;
use Behat\Behat\Context\SnippetAcceptingContext;
use Behat\Gherkin\Node\PyStringNode;
use Behat\Gherkin\Node\TableNode;
use Behat\Behat\Tester\Exception\PendingException;

class FeatureContext extends DrupalContext implements SnippetAcceptingContext {

  /**
   *  The total hours of a project.
   */
  protected $totalHours;

  /**
   *  The name of the project being tested.
   */
  protected $projectName;


  /**
   * @When /^I login with user "([^"]*)"$/
   */
  public function iLoginWithUser($name) {
    // @todo: Move password to YAML.
    $password = '1234';
    $password = $name == 'admin' ? 'admin' : '1234';
    $this->loginUser($name, $password);
  }

  /**
   * Login a user to the site.
   *
   * @param $name
   *   The user name.
   * @param $password
   *   The use password.
   * @param bool $check_success
   *   Determines if we should check for the login to be successful.
   *
   * @throws \Exception
   */
  protected function loginUser($name, $password, $check_success = TRUE) {
    $this->getSession()->visit($this->locatePath('user'));
    $element = $this->getSession()->getPage();
    $element->fillField('Username', $name);
    $element->fillField('Password', $password);
    $submit = $element->findButton('Log in');

    if (empty($submit)) {
      throw new \Exception(sprintf("No submit button at %s", $this->getSession()->getCurrentUrl()));
    }
    // Log in.
    $submit->click();

  }

  /**
   * @When /^I login with bad credentials$/
   */
  public function iLoginWithBadCredentials() {
    return $this->loginUser('wrong-foo', 'wrong-bar', FALSE);
  }

  /**
   * @When /^I open the calendar$/
   */
  public function iOpenTheCalendar() {
    $element = $this->getSession()->getPage();
    $element->pressButton('Show Calendar');
    $this->iShouldWaitForTheTextTo('Log work', 'appear');
  }

  /**
   * @Then /^I should wait for the text "([^"]*)" to "([^"]*)"$/
   */
  public function iShouldWaitForTheTextTo($text, $appear) {
    $this->waitForXpathNode(".//*[contains(normalize-space(string(text())), \"$text\")]", $appear == 'appear');
  }

  /**
   * @Then /^I wait for css element "([^"]*)" to "([^"]*)"$/
   */
  public function iWaitForCssElement($element, $appear) {
    $xpath = $this->getSession()->getSelectorsHandler()->selectorToXpath('css', $element);
    $this->waitForXpathNode($xpath, $appear == 'appear');
  }
  /**
   * @AfterStep
   *
   * Take a screen shot after failed steps for Selenium drivers (e.g.
   * PhantomJs).
   */
  public function takeScreenshotAfterFailedStep($event) {
    if ($event->getTestResult()->isPassed()) {
      // Not a failed step.
      return;
    }

    if ($this->getSession()->getDriver() instanceof \Behat\Mink\Driver\Selenium2Driver) {
      $file_name = sys_get_temp_dir() . DIRECTORY_SEPARATOR . 'behat-failed-step.png';
      $screenshot = $this->getSession()->getDriver()->getScreenshot();
      file_put_contents($file_name, $screenshot);
      print "Screenshot for failed step created in $file_name";
    }
  }
  /**
   * @BeforeScenario
   *
   * Delete the RESTful tokens before every scenario, so user starts as
   * anonymous.
   */
  public function deleteRestfulTokens($event) {
    if (!module_exists('restful_token_auth')) {
      // Module is disabled.
      return;
    }
    if (!$entities = entity_load('restful_token_auth')) {
      // No tokens found.
      return;
    }
    foreach ($entities as $entity) {
      $entity->delete();
    }
  }


  /**
   * @BeforeScenario
   *
   * Resize the view port.
   */
  public function resizeWindow() {
    if ($this->getSession()->getDriver() instanceof \Behat\Mink\Driver\Selenium2Driver) {
      $this->getSession()->resizeWindow(1440, 900, 'current');
    }
  }

  /**
   * Helper function; Execute a function until it return TRUE or timeouts.
   *
   * @param $fn
   *   A callable to invoke.
   * @param int $timeout
   *   The timeout period. Defaults to 90 seconds.
   *
   * @throws Exception
   */
  private function waitFor($fn, $timeout = 90000) {
    $start = microtime(true);
    $end = $start + $timeout / 1000.0;
    while (microtime(true) < $end) {
      if ($fn($this)) {
        return;
      }
    }
    throw new \Exception('waitFor timed out.');
  }
  /**
   * Wait for an element by its XPath to appear or disappear.
   *
   * @param string $xpath
   *   The XPath string.
   * @param bool $appear
   *   Determine if element should appear. Defaults to TRUE.
   *
   * @throws Exception
   */
  private function waitForXpathNode($xpath, $appear = TRUE) {
    $this->waitFor(function($context) use ($xpath, $appear) {
        try {
          $nodes = $context->getSession()->getDriver()->find($xpath);
          if (count($nodes) > 0) {
            $visible = $nodes[0]->isVisible();
            return $appear ? $visible : !$visible;
          }
          return !$appear;
        }
        catch (WebDriver\Exception $e) {
          if ($e->getCode() == WebDriver\Exception::NO_SUCH_ELEMENT) {
            return !$appear;
          }
          throw $e;
        }
      });
  }

  /**
   * @Given /^I wait$/
   */
  public function iWait() {
    sleep(10);
  }

  public function getTotalHours($projectName) {
    $this->getSession()->visit($this->locatePath('content/' . $projectName));
    $page = $this->getSession()->getPage();

    if (!$element = $page->find('xpath', '//div[@class="field-item even"]')) {
      throw new \Exception('The element was not found in the page.');
    }

    $totalHoursText = $element->getText();

    // Removing whitespace in case $totalHoursText >= 1 000
    $totalHours = intval(str_replace(' ', '', $totalHoursText));

    return $totalHours;
  }

  /**
   * @Given /^I get the total hours from "([^"]*)" project$/
   */
  public function iGetTheTotalHours($projectName) {
    $this->projectName = $projectName;
    $totalHours = $this->getTotalHours($projectName);

    $this->totalHours = $totalHours;
  }

  /**
   * @Given /^I validate that total hours have "([^"]*)" by "([^"]*)"$/
   */
  public function iValidateTheTotalHours($type, $hours) {
    $newTotalHours = $this->getTotalHours($this->projectName);
    $expectedSum;
    switch ($type) {
      case "incremented":
        $expectedSum = $this->totalHours + $hours;
        break;

      case "decremented":
        $expectedSum = $this->totalHours - $hours;
        print("\nOriginal Hours: " . $this->totalHours);
        print("\nDecremented Hours: " . $hours);
        print("\nExpected Sum: " . $expectedSum);
        break;

      default:
        throw new Exception('Wrong arithmetic type provided.');
    }

    print("\nTotal Hours: ". $newTotalHours . " Expected Sum: " . $expectedSum );
    if ($newTotalHours != $expectedSum ) {
      throw new Exception("The total hours didn't match the expected number.");
    }
   }

  /**
   * @Then /^I add a new time tracking entry with "([^"]*)" hours$/
   */
  public function iAddANewTimeTrackingEntry($hours) {
    $this->getSession()->visit($this->locatePath('node/add/time-tracking'));
    $element = $this->getSession()->getPage();

    $element->fillField('Title', 'Developing the thing');
    $element->fillField('Description', 'Yay');
    $element->selectFieldOption('Project', 'nike Site');
    $element->fillField('Time Spent', $hours);
    $element->selectFieldOption('Issue type', 'Development');
    $element->find('css', '#edit-submit')->click();
  }


  function getLatestTrackingEntry() {
    $query = new EntityFieldQuery();
    $result = $query
      ->entityCondition('entity_type', 'node')
      ->propertyCondition('type', 'time_tracking')
      ->propertyOrderBy('created', 'DESC')
      ->range(0, 1)
      ->execute();

    if (empty($result['node'])) {
      return;
    }
    return key($result['node']);
  }

  /**
   * @Then /^I add "([^"]*)" hours to the latest tracking entry$/
   */
  public function iAddHoursToLatestTrackingEntry($hours) {
    $entryID = $this->getLatestTrackingEntry();
    $this->getSession()->visit($this->locatePath('node/' . $entryID .'/edit'));
    $element = $this->getSession()->getPage();

    $timeSpentElm = $element->find('css', '#edit-field-issues-logs-und-0-field-time-spent-und-0-value');
    $timeSpent = $timeSpentElm->getValue();

    if ( isset($timeSpent) ) {
      $hours += $timeSpent;
    }

    $element->fillField('Time Spent', $hours);
    $element->find('css', '#edit-submit')->click();
  }

  /**
   * @Then /^I delete the latest tracking entry$/
   */
  public function iDeleteLatestTrackingEntry() {
    $entryID = $this->getLatestTrackingEntry();
    $this->getSession()->visit($this->locatePath('node/' . $entryID .'/delete'));
    $element = $this->getSession()->getPage();
    $element->find('css', '#edit-submit')->click();
  }

}

