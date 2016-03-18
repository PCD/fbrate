<?php
/**
 * Implements hook_menu.
 */
function fbrate_menu() {
  $items = array();
  $items['admin/fbrate/import/post'] = array(
    'title' => 'Import Post', 
    'page callback' => 'drupal_get_form', 
    'page arguments' => array('fbrate_import_post_form'), 
    'access callback' => TRUE, 
    'type' => MENU_CALLBACK, 
  );
  return $items;
}
