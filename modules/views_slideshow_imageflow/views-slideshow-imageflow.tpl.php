<?php
// $Id: views-slideshow-imageflow.tpl.php,v 1.1 2009/03/30 21:20:37 aaron Exp $

/**
 *  @file
 *  This will format a view to display several images in a ImageFlow/CoverFlow
 *  style.
 *
 *  VERY IMPORTANT:
 *  The View MUST return a set of fields composed of Images only.
 *  Anything else WILL break the output.
 *
 * - $view: The view object.
 * - $options: Style options. See below.
 * - $rows: The output for the rows.
 * - $title: The title of this group of rows.  May be empty.
 * - $id: The unique counter for this view.
 * - $images: An array of images that have been stripped from $rows.
 */
?>

  <div id="views-slideshow-imageflow-<?php print $id; ?>" class="views-slideshow-imageflow">
    <?php if (!empty($title)) : ?>
      <h3><?php print $title; ?></h3>
    <?php endif; ?>

    <div id="views-slideshow-imageflow-images-<?php print $id; ?>" class="views-slideshow-imageflow-images imageflow">
      <?php foreach ($images as $image): ?>
       <?php print $image ."\n"; ?>
      <?php endforeach; ?>
    </div>

  </div>

