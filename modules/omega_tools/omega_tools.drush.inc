<?php
// $Id: omega_tools.drush.inc,v 1.1.4.2 2010/06/14 23:32:28 himerus Exp $

/**
 * @file Drush sql commands
 */

/**
 * Implementation of hook_drush_help().
 */
function omega_tools_drush_help($section) {
  switch ($section) {
    case 'drush:omega-subtheme':
      return dt('Creates a valid subtheme in sites/all/themes based on a single argument, the name of the subtheme');
  }
}

/**
 * Implementation of hook_drush_command().
 */
function omega_tools_drush_command() {
  $items['omega-subtheme'] = array(
    'description' => 'Creates an Omega subtheme.',
    'callback' => 'drush_omega_subtheme',
    'examples' => array(
      'drush omega-subtheme subtheme_name' => 'Create an Omega subtheme to the default sites/all/themes folder named subtheme_name.',
      'drush omega-subtheme subtheme_name --destination=example.com' => 'Create an Omega subtheme to sites/example.com/themes folder named subtheme_name.',
    ),
    'arguments' => array(
      'name' => 'The name of the subtheme to create.',
    ),
    'options' => array(
      '--destination' => 'The site specific folder name in /sites where the information should be saved. /sites/all by default.',
    ),
  );
  return $items;
}


function drush_omega_subtheme() {
  $args = func_get_args();
  if (isset($args[0])) {
    $name = $args[0];
    $exec = drush_omega_tools_subtheme($name);
    // Avoid the php memory of the $output array in drush_shell_exec().
    if ($exec) {
      $return = drush_op('system', $exec);
      return $return; 
    }
    
  }
  else {
    return drush_set_error(dt('You must delcare the name of the new subtheme'));
  }
}

function drush_omega_tools_subtheme($name) {
  $name_long = $name;
  // replace non-alphanumeric characters with an underscore
  $name = strtolower(preg_replace('/\W/', '_', $name));
  //clean up leading/trailing and double underscores
  $name = str_replace('__', '_', $name);
  $name = trim($name, '_');
  $drupal_root = drush_get_context('DRUSH_DRUPAL_ROOT') .'/';
  $omega_path = $drupal_root . drupal_get_path('theme', omega);
  
  if ($path = drush_get_option('destination')) {
    $site_dir = $drupal_root .'sites/'. $path;
    $theme_dir = $site_dir .'/themes';
  }
  
  else {
    $site_dir = $drupal_root .'sites/all';
    $theme_dir = $site_dir .'/themes';
  }
  //drush_print(dt('Creating subtheme location in: '. $site_dir));
  if (!is_dir($omega_path)) {
    drush_set_error(dt('Omega base theme not found. You must download the Omega theme to create a subtheme of Omega.'));
    return FALSE;
  }
  if (!is_dir($site_dir)) {
    drush_set_error(dt('The site directory: '. $site_dir .' does not exist. Please specify another, remove --destination to use /sites/all/themes'));
    return FALSE;
  }
  if (!is_dir($theme_dir)) {
    if(!drush_op('mkdir', $theme_dir)) {
      drush_set_error(dt('The theme directory: '. $theme_dir .' does not exist. An attempt to automagically create this folder failed. '));
      return FALSE;
    }
    else {
      drush_log(dt('The theme directory: '. $theme_dir .' does not exist. It was created for you. I hope you don\'t mind!!'), 'ok');
    }
  }
  if (is_dir($site_dir .'/'. $name)) {
    drush_set_error(dt('The destination theme directory: '. $site_dir .' already exists. Please specify another theme name.'));
    return FALSE;
  }
  
  // copy the starterkit directory to the new location
  $exec = 'cp -R '. $omega_path .'/starterkit '. $theme_dir .'/'. $name;
  // replace instances of omega_starterkit in all php files
  $exec .= '; sed -i.bak s/omega_starterkit/'. $name .'/ '. $theme_dir .'/'. $name .'/template.php';
  $exec .= '; sed -i.bak s/omega_starterkit/'. $name .'/ '. $theme_dir .'/'. $name .'/theme-settings.php';
  // move the .info file
  $exec .= '; mv '. $theme_dir .'/'. $name .'/omega_starterkit.info '. $theme_dir .'/'. $name .'/' . $name .'.info';
  // change the name of the theme in the .info file
  $exec .= '; sed -i.bak s/"Omega Starter Kit"/"'. $name_long .'"/ '. $theme_dir .'/'. $name .'/*.info';
  drush_log(dt('Omega Subtheme: '. $name_long .' ('. $name .') created and configured for usage.'), 'ok');
  return $exec;
}

