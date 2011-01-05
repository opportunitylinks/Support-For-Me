<?php
// $Id$

/**
 * @file
 * Adminstration page callbacks for the evince dir module.
 */


function evince_dir_admin_settings() {
  $form['evince_dir_maxrec'] = array(
    '#type' => 'textfield',
    '#title' => t('Max Search Records'),
    '#size' => 4,
    '#default_value' => variable_get('evince_dir_maxrec', '1000'),
    '#description' => t('Enter the maximum number of records to load in a single search (affects tab pages only)'),
  );

  return system_settings_form($form);
}
