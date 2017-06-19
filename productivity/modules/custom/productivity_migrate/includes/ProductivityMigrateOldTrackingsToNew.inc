<?php

class ProductivityMigrateOldTrackingsToNew extends Migration {

  /**
   * Class constructor.
   */
  public function __construct($arguments) {
    parent::__construct($arguments);
    $this->description = t('Copy multifiled field_track_log to node track_log_item.');

    $this->addFieldMapping('field_track_date', 'field_track_log_field_date_value');
    $this->addFieldMapping('field_track_date:timezone')
      ->defaultValue('Asia/Jerusalem');

    $this->addFieldMapping('field_employee', 'field_track_log_field_employee_target_id');
    $this->addFieldMapping('field_github_username', 'field_track_log_field_github_username_value');
    $this->addFieldMapping('field_issue_id', 'field_track_log_field_issue_id_value');
    $this->addFieldMapping('title', 'field_track_log_field_issue_label_value');
    $this->addFieldMapping('field_issue_type', 'field_track_log_field_issue_type_value');
    $this->addFieldMapping('field_time_spent', 'field_track_log_field_time_spent_value');
    $this->addFieldMapping('field_issue_status', 'field_track_log_field_issue_status_target_id');
    $this->addFieldMapping('field_push_date', 'field_track_log_field_last_push_value');
    $this->addFieldMapping('field_push_date:timezone')
        ->defaultValue('Asia/Jerusalem');

    // Create a map object for tracking the relationships between source rows.
    $key = array(
      'field_track_log_id' => array(
        'type' => 'varchar',
        'length' => 255,
        'not null' => TRUE,
      ),
    );

    $this->map = new MigrateSQLMap($this->machineName, $key, MigrateDestinationNode::getKeySchema());

    // Fetch all time tracking nodes with type different than 'regular'.
    $query = db_select('field_data_field_track_log', 't');
    $query
      ->fields('t');
//      ->condition('field_track_log_id', 69901);

    $this->source = new MigrateSourceSQL($query);
    $this->destination = new MigrateDestinationNode('track_log_item');
  }

  public function complete($entity, stdClass $row) {
    // Connect to tracking node.
    $track_nid = $row->entity_id;
    $wrapper = entity_metadata_wrapper('node',$track_nid);
    $wrapper->field_track_log_items[] = $entity;
    $wrapper->save();
  }

}
