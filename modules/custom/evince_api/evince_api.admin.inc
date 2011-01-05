<?php
// $Id$

/**
 * @file
 * Adminstration page callbacks for the evince api module.
 */

/**
 * Form builder.  Module settings.
 *
 * @ingroup forms
 * @see system_settings_form()
 */
function evince_api_admin_settings() {
  $form['evince_api_url'] = array(
    '#type' => 'textfield',
    '#title' => t('URL'),
    '#default_value' => variable_get('evince_api_url', ''),
    '#description' => t('Enter the base URL of the evince API web service e.g. http://api.evince-online.com.'),
  );
  $form['evince_api_snac'] = array(
    '#type' => 'textfield',
    '#title' => t('SNAC'),
    '#default_value' => variable_get('evince_api_snac', ''),
    '#description' => t('Enter the SNAC for this website e.g. 8PC.'),
    '#size' => 6,
  );
  $form['evince_api_api_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Key'),
    '#default_value' => variable_get('evince_api_api_key', ''),
    '#description' => t('Enter the evince API key.'),
  );
  $form['evince_api_marker'] = array(
    '#type' => 'textfield',
    '#title' => t('Marker'),
    '#default_value' => variable_get('evince_api_marker', ''),
    '#description' => t('Enter the evince API marker.  Only records with this marker will be displayed.'),
  );
  $form['evince_api_node_type'] = array(
    '#type' => 'textfield',
    '#title' => t('Search result node type '),
    '#default_value' => variable_get('evince_api_node_type', ''),
    '#description' => t('Enter the machine name of the node type to store search results.'),
    '#size' => 20,
  );
  $form['evince_api_search_node_type'] = array(
    '#type' => 'textfield',
    '#title' => t('Search context node type '),
    '#default_value' => variable_get('evince_api_search_node_type', ''),
    '#description' => t('Enter the machine name of the node type to store search context.'),
    '#size' => 20,
  );
  return system_settings_form($form);
}
