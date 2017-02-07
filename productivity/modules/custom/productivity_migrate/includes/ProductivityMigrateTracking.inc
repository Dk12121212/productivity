<?php

class ProductivityMigrateTracking extends Migration {

  /**
   * Class constructor.
   */
  public function __construct($arguments) {
    parent::__construct($arguments);
    $this->description = t('Copy non-regular time tracking to work session nodes.');

    $this->addSimpleMappings(array('title', 'created', 'changed'));
    $this->addFieldMapping('field_project', 'field_project_target_id');
    $this->addFieldMapping('field_time_estimate', 'field_time_estimate_value');
    $this->addFieldMapping('field_issue_id', 'field_issue_id_value');
    $this->addFieldMapping('field_github_project_id', 'field_github_project_id_value');

    $this->addFieldMapping('field_session_date', 'date');
    $this->addFieldMapping('field_session_date:to', 'enddate');
    $this->addFieldMapping('field_session_date:timezone')
      ->defaultValue('Asia/Jerusalem');


    // Create a map object for tracking the relationships between source rows.
    $key = array(
      'nid' => array(
        'type' => 'varchar',
        'length' => 255,
        'not null' => TRUE,
      ),
    );

    $this->map = new MigrateSQLMap($this->machineName, $key, MigrateDestinationNode::getKeySchema());

    // Fetch all time tracking nodes with type different than 'regular'.
    $query = db_select('node', 'n');
    $query->leftJoin('field_data_field_day_type', 'dt', "dt.entity_type = 'node' AND dt.entity_id = n.nid");
    $query->leftJoin('field_data_field_time_estimate', 'es', "es.entity_type = 'node' AND es.entity_id = n.nid");
    $query->leftJoin('field_data_field_work_date', 'wd', "wd.entity_type = 'node' AND wd.entity_id = n.nid");
    $query->leftJoin('field_data_field_employee', 'e', "e.entity_type = 'node' AND e.entity_id = n.nid");
    $query->leftJoin('field_data_field_project', 'p', "p.entity_type = 'node' AND p.entity_id = n.nid");
    $query->leftJoin('field_data_field_issue_id', 'i', "i.entity_type = 'node' AND i.entity_id = n.nid");
    $query->leftJoin('field_data_field_github_project_id', 'gh', "gh.entity_type = 'node' AND gh.entity_id = n.nid");

    // Left join since some node will not have a project ID.

    $query
      ->fields('n',  array('nid', 'created','changed', 'title'))
      ->fields('dt', array('field_day_type_value'))
      ->fields('es', array('field_time_estimate_value'))
      ->fields('wd', array('field_work_date_value'))
      ->fields('e',  array('field_employee_target_id'))
      ->fields('p',  array('field_project_target_id'))
      ->fields('i', array('field_issue_id_value'))
      ->fields('gh', array('field_github_project_id_value'))
      ->condition('dt.field_day_type_value', 'regular')
      ->condition('n.type', 'time_tracking')
      ->condition('n.status', 1)
      ->orderBy('n.created');

    $this->source = new MigrateSourceSQL($query);
    $this->destination = new MigrateDestinationNode('tracking');
  }

  public function prepare($row, $entity) {
  }

  /**
   * Convert string to taxonomy.
   */
  public function prepareRow($row) {


  }

//  /**
//   * Filter the destiny field ID.
//   *
//   * @param array $dest_field
//   *   The destiny field settings.
//   *
//   * @return array
//   *   The filtered array.
//   */
//  protected function filterDestid2FromEntityReference($dest_field) {
//    $filtered_ids = array();
//
//    if (!empty($dest_field['destid1'])) {
//      $filtered_ids = array('destid1' => $dest_field['destid1']);
//      if (!empty($dest_field['destid2'])) {
//        $filtered_ids['destid2'] = $dest_field['destid2'];
//      }
//    }
//    elseif (is_array($dest_field)) {
//      foreach ($dest_field as $key => $dest) {
//        $filtered_ids[$key] = array('destid1' => $dest['destid1']);
//        if (!empty($dest['destid2'])) {
//          $filtered_ids[$key]['destid2'] = $dest['destid2'];
//        }
//      }
//    }
//
//    return $filtered_ids;
//  }
}
