<?php

/**
 * Implementation of hook_taxonomy_default_vocabularies().
 */
function evince_dir_feature_taxonomy_default_vocabularies() {
  return array(
    'rectype' => array(
      'name' => 'Record Type',
      'description' => '',
      'help' => '',
      'relations' => '1',
      'hierarchy' => '1',
      'multiple' => '0',
      'required' => '0',
      'tags' => '0',
      'module' => 'features_rectype',
      'weight' => '0',
      'nodes' => array(
        'asc_result' => 'asc_result',
      ),
    ),
  );
}
