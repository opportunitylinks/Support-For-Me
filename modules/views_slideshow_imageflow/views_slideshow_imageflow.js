// $Id: views_slideshow_imageflow.js,v 1.1.2.2 2009/06/19 21:06:46 aaron Exp $

/**
 *  @file
 *  This will initiate any ImageFlow browsers we have set up.
 */
Drupal.behaviors.viewsSlideshowImageFlow = function (context) {
  $('.views-slideshow-imageflow-images:not(.viewsSlideshowImageFlow-processed)', context).addClass('viewsSlideshowImageFlow-processed').each(function () {
    var imageflow = new ImageFlow();
    var id = $(this).attr('id');
    var flow = Drupal.settings.imageFlow[id];
    if (!flow['slider']) {
      flow['slider'] = false;
    }
    if (!flow['captions']) {
      flow['captions'] = false;
    }
    imageflow.init({
      ImageFlowID: id,
      reflections: false,
      imagesHeight: flow['imagesHeight'],
      aspectRatio: flow['aspectRatio'],
      imageCursor: flow['imageCursor'],
      startID: flow['startID'],
      slider: flow['slider'],
      sliderCursor: flow['sliderCursor'],
      captions: flow['captions'],
      imageFocusM : flow['imageFocusM'],
      scrollbarP : flow['scrollbarP'],
      imageFocusMax : flow['imageFocusMax']
    });
  });
};
