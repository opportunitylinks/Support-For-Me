<?php

/**
 * Implementation of hook_node_info().
 */
function evince_dir_feature_node_info() {
  $items = array(
    'asc_search' => array(
      'name' => t('ASC Search'),
      'module' => 'features',
      'description' => t('Info related to a faceted search, keyed to a specific result set.  Title of node is result set id. Body is serialised array of search info.'),
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
function evince_dir_feature_views_api() {
  return array(
    'api' => '2',
  );
}
