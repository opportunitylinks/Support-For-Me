<?php

/**
 * Implementation of hook_menu_default_menu_links().
 */
function evince_dir_feature_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: primary-links:evince/dir
  $menu_links['primary-links:evince/dir'] = array(
    'menu_name' => 'primary-links',
    'link_path' => 'evince/dir',
    'router_path' => 'evince/dir',
    'link_title' => 'Search',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-48',
  );
  // Exported menu link: primary-links:evince/dir/atoz
  $menu_links['primary-links:evince/dir/atoz'] = array(
    'menu_name' => 'primary-links',
    'link_path' => 'evince/dir/atoz',
    'router_path' => 'evince/dir',
    'link_title' => 'A to Z',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-49',
  );
  // Exported menu link: primary-links:evince/dir/category/7
  $menu_links['primary-links:evince/dir/category/7'] = array(
    'menu_name' => 'primary-links',
    'link_path' => 'evince/dir/category/7',
    'router_path' => 'evince/dir',
    'link_title' => 'Zones',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-50',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('A to Z');
  t('Search');
  t('Zones');


  return $menu_links;
}
