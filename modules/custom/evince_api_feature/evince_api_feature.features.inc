<?php

/**
 * Implementation of hook_node_info().
 */
function evince_api_feature_node_info() {
  $items = array(
    'asc_result' => array(
      'name' => t('ASC Result'),
      'module' => 'features',
      'description' => t('A single evince API search result, usually one of a set identified by the same result set ID.  Exists only until the next search is performed or when garbage collection is run.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '1',
      'body_label' => t('Body'),
      'min_word_count' => '0',
      'help' => '',
    ),
  );
  return $items;
}

/**
 * Implementation of hook_views_api().
 */
function evince_api_feature_views_api() {
  return array(
    'api' => '2',
  );
}
