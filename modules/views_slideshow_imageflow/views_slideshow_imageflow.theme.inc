<?php
// $Id: views_slideshow_imageflow.theme.inc,v 1.1.2.3 2009/06/19 21:06:46 aaron Exp $

/**
 *  @file
 *  Theme & preprocess functions for the Views Slideshow: Imageflow module.
 */

/**
 *  We'll grab only the first image from each row.
 */
function template_preprocess_views_slideshow_imageflow(&$vars) {
  // Initialize our $images array.
  $vars['images'] = array();

  // Strip all images from the $rows created by the original view query.
  foreach($vars['rows'] as $item) {
    preg_match('@(<\s*img\s+[^>]*>)@i', $item, $matches);
    if ($image = $matches[1]) {
      // We need to add a URL to 'longdesc', as required by the plugin.
      // If our image is in an anchor tag, use its URL.
      preg_match('@<\s*a\s+href\s*=\s*"\s*([^"]+)\s*"[^>]*>[^<]*'. preg_quote($image) .'[^<]*<\s*/a\s*>@i', $item, $urls);
      if (!($url = $urls[1])) {
        // Otherwise link to the original image.
        preg_match('@src\s*=\s*"([^"]+)"@i', $image, $urls);
        if (!($url = $urls[1])) {
          // If we get this far, there are probably more serious problems.
          // But for now, we'll go to the front page instead.
          $url = url('<front>');
        }
      }

      // Add the URL to the image's longdesc tag.
      $image = preg_replace('@img\s+@i', 'img longdesc="'. $url .'" ', $image);

      // Add the image to our image array to display.
      $vars['images'][] = $image;
    }
  }

  // Find the path to our plugin.
  $path = variable_get('views_slideshow_imageflow_plugin', 'sites/all/plugins/imageflow');

  // Add the required JS and CSS.
  drupal_add_js($path .'/imageflow.packed.js');
  drupal_add_css($path .'/imageflow.css');
  drupal_add_js(drupal_get_path('module', 'views_slideshow_imageflow') .'/views_slideshow_imageflow.js');

  $view = $vars['view'];
  $rows = $vars['rows'];
  $options = $vars['options'];
  switch ($options['imageflow']['start']) {
    case 'start':
      $start = 1;
      break;
    case 'end':
      $start = sizeof($rows);
      break;
    case 'middle':
      $start = ceil(sizeof($rows) / 2);
      break;
    case 'random':
      $start = rand(1, sizeof($rows));
      break;
  }

  // Deal with views created before various options were available:
  // @TODO: Do this in an update function instead?
  $options['imageflow']['captions'] = isset($options['imageflow']['captions']) ? $options['imageflow']['captions'] : TRUE;
  $options['imageflow']['imageFocusM'] = isset($options['imageflow']['imageFocusM']) ? $options['imageflow']['imageFocusM'] : 1.0;
  $options['imageflow']['scrollbarP'] = isset($options['imageflow']['scrollbarP']) ? $options['imageflow']['scrollbarP'] : 0.6;
  $options['imageflow']['imageFocusMax'] = isset($options['imageflow']['imageFocusMax']) ? $options['imageflow']['imageFocusMax'] : 4;

  $settings = array(
    'aspectRatio' => $options['imageflow']['aspect_ratio'],
    'imagesHeight' => $options['imageflow']['images_height'],
    'imageCursor' => $options['imageflow']['image_cursor'],
    'sliderCursor' => $options['imageflow']['slider_cursor'],
    'startID' => $start,
    'slider' => $options['imageflow']['slider'],
    'captions' => $options['imageflow']['captions'],
    'imageFocusM' => $options['imageflow']['imageFocusM'],
    'scrollbarP' => $options['imageflow']['scrollbarP'],
    'imageFocusMax' => $options['imageflow']['imageFocusMax'],
  );
  drupal_add_js(array('imageFlow' => array('views-slideshow-imageflow-images-'. $vars['id'] => $settings)), 'setting');
}
