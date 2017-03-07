Feature: Login test
  Test login and default actions.

  @api
  Scenario: Check login form when not logged in.
    Given I visit the "/" page
    Then  I see the text "Username"
    Then  I see the text "Login with GitHub"


  @api
  Scenario: Attempt login.
    Given I login with user "admin"
    When  I visit the "/" page
    Then  I should see the text "Dashboard"
