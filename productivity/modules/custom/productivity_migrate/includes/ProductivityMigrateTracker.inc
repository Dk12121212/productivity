<?php
/**
 * @file
 * Migrate class to create Productivity content.
 */

/**
 * Class ProductivityDemoCreateProductivityContent
 */
class ProductivityMigrateTracker extends ProductivityMigrate {
  public $entityType = 'node';
  public $bundle = 'tracking';

  /**
   * CSV Column mapping.
   *
   * @var array
   */
  public $csvColumns = array(
    array('id', 'ID'),
    array('field_date', 'field_date'),
    array('field_employee', 'field_employee'),
    array('field_project', 'field_project'),
    array('field_time_spent', 'field_time_spent'),
    array('title', 'title'),
  );

  /**
   * Configure the object during creation.
   */
  public function __construct($arguments) {
    parent::__construct($arguments);

    $this->dependencies = array(
      'ProductivityMigrateUser',
      'ProductivityMigrateProject',
    );

    $this
      ->addFieldMapping('field_project', 'field_project')
      ->sourceMigration('ProductivityMigrateProject');

  }

  function prepare($entity, $row) {
    // Save time tracking, in multifield format.
    $entity->field_track_log[LANGUAGE_NONE][0]['field_time_spent'][LANGUAGE_NONE][0]['value'] = $row->field_track_hours;
    $entity->field_track_log[LANGUAGE_NONE][0]['field_issue_type'][LANGUAGE_NONE][0]['value'] = 'dev';
    $entity->field_track_log[LANGUAGE_NONE][0]['field_issue_label'][LANGUAGE_NONE][0]['value'] = $row->title;
    $entity->field_track_log[LANGUAGE_NONE][0]['field_date'][LANGUAGE_NONE][0]['value'] = $row->field_date;

    $user = user_load_by_name($row->field_employee);

    $entity->field_track_log[LANGUAGE_NONE][0]['field_date'][LANGUAGE_NONE][0]['target_id'] = $user->uid;
  }
}
