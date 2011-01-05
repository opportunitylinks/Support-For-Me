<?php
// $Id: views_slideshow_imageflow.admin.inc,v 1.1 2009/03/30 21:20:37 aaron Exp $

/**
 * @file
 * Admin functions for the Views Slideshow: ImageFlow module.
 */

/**
 * Configure Views Slideshow: Imageflow; menu callback for admin/build/views/views_slideshow_imageflow.
 */
function views_slideshow_imageflow_settings() {
  $form = array();

  $path = variable_get('views_slideshow_imageflow_plugin', 'sites/all/plugins/imageflow');
  $message = t('To use !imageflow, you must first !download the plugin package, extract it, and place the entire contents into the folder on your server specified here.', array('!imageflow' => l(t('ImageFlow'), 'http://finnrudolph.de/ImageFlow'), '!download' => l(t('download'), 'http://finnrudolph.de/ImageFlow/Download')));
  if (!file_exists($path .'/imageflow.packed.js')) {
    drupal_set_message($message, 'error');
  }

  $form['views_slideshow_imageflow_plugin'] = array(
    '#type' => 'textfield',
    '#title' => t('Path to the ImageFlow plugin'),
    '#description' => $message,
    '#default_value' => $path,
  );

  return system_settings_form($form);
}
