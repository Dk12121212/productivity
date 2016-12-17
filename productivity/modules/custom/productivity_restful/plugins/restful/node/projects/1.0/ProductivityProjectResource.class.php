<?php

/**
 * @file
 * Contains ProductivityProjectResource.
 */

class ProductivityProjectResource extends \ProductivityEntityBaseNode {

  protected $range = 100;
  /**
   * Overrides \RestfulEntityBaseNode::publicFieldsInfo().
   */
  public function publicFieldsInfo() {
    $public_fields = parent::publicFieldsInfo();

    $public_fields['id'] = array(
      'property' => 'nid',
    );

    $public_fields['rate_types'] = array(
      'property' => 'field_table_rate',
      'process_callbacks' => array(
        array($this, 'getRateTypes'),
      ),
    );

    return $public_fields;
  }

  /**
   * Overrides RestfulEntityBase::getEntityFieldQuery.
   *
   * When there's a year and a month defined in the request, Filter projects which their end date is bigger,
   * Which will return all projects that are still active in this time.
   */
  public function getEntityFieldQuery() {
    $query = parent::getEntityFieldQuery();
    $request = $this->getRequest();

    if (!empty($request['year']) && !empty($request['month'])) {
      list($start_time, $end_time) = $this->getTimeSpan('+1 month');
      $query
        ->fieldCondition('field_date', 'value', $end_time, '<=')
        ->fieldCondition('field_date', 'value2', $start_time, '>=')
        ->addTag('empty_end_date');
    }

    return $query;
  }

  /**
   * Fetches the allowed rate types for-each project.
   *
   * In order to get custom rate types for each project and to get rid of the
   * necessity to list the issues type manually in the frontend application,
   * this provides a list of types allowed for issues to be logged by the
   * employees.
   * i.e. 'dev' => 'Development'
   *
   * @param array $values
   *   The rate table values.
   *
   * @return array
   *   An array containing the allowed issue types for each project or null if
   *   empty.
   */
  protected function getRateTypes(array $values) {
    // Get the allowed values for the issues types.
    $issues_type_info = field_info_field('field_issue_type');
    $allowed_values = $issues_type_info['settings']['allowed_values'];

    // Go throw the rates table and get the allowed types.
    $rate_types = array();
    if (!empty($values)) {
      foreach ($values as $value) {
        // Sub field of a multi-field, we can't use wrapper.
        $type = $value->field_issue_type[LANGUAGE_NONE][0]['value'];
        $rate_types[$type] = $allowed_values[$type];
      }
    }

    return $rate_types;
  }
}
