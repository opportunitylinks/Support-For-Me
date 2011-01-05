/*
 * jQuery panelgallery plugin
 * @author admin@catchmyfame.com - http://www.catchmyfame.com
 * @version 1.1
 * @date August 13, 2009
 * @category jQuery plugin
 * @copyright (c) 2009 admin@catchmyfame.com (www.catchmyfame.com)
 * @license CC Attribution-No Derivative Works 3.0 - http://creativecommons.org/licenses/by-nd/3.0/
 */

(function($){
	$.fn.extend({
		panelGallery: function(options)
		{
			var defaults = 
			{
				sections : 3,
				imageTransitionDelay : 3000,
				sectionTransitionDelay : 700,
				startDelay : 2000,
				repeat : true,
				direction : "lr"
			};
		var options = $.extend(defaults, options);
	
    		return this.each(function() {
				var o=options;
				var obj = $(this);

				// Preload images
				$("img", obj).each(function(i) { // preload images
					preload = new Image($(this).attr("width"),$(this).attr("height")); 
					preload.src = $(this).attr("src");
				});

				function getRandom()
				{
					return Math.round(Math.random()*100000000);
				}
				
				function getDirection(imgIndex)
				{
					return ($("img:eq("+imgIndex+")", obj).attr("name") == "")? o.direction: $("img:eq("+imgIndex+")", obj).attr("name");
				}
				
				function setupNextTransition(direction)
				{
					if((direction== "lr" || direction== "rl"))
					{
						if(isHorizReversed && direction== "lr")
						{
							panelIDArrayHoriz.reverse();
							isHorizReversed = false;
						}
						if(!isHorizReversed && direction== "rl")
						{
							panelIDArrayHoriz.reverse();
							isHorizReversed = true;
						}
						setTimeout(function(){$("#p"+panelIDArrayHoriz[0]).fadeIn(o.sectionTransitionDelay,doNext)},o.imageTransitionDelay);
					}
					else if((direction== "tb" || direction== "bt"))
					{
						if(isVertReversed && direction== "tb")
						{
							panelIDArrayVert.reverse();
							isVertReversed = false;
						}
						if(!isVertReversed && direction== "bt")
						{
							panelIDArrayVert.reverse();
							isVertReversed = true;
						}
						setTimeout(function(){$("#p"+panelIDArrayVert[0]).fadeIn(o.sectionTransitionDelay,doNext)},o.imageTransitionDelay);
					}
				}

				var imgArray = $("img", obj);
				$("img:not(:first)", obj).hide(); // Hides all images in the container except the first one
				$("img", obj).css({'position':'absolute','top':'0px','left':'0px'}); // Set the position of all images in the container

				var sectionsVert = o.sections;
				var sectionsHoriz = o.sections;
				var imgWidth = $("img:first", obj).attr("width"); // Get width of base image;
				var imgHeight = $("img:first", obj).attr("height"); // Get height of base image;
				var sectionWidth = Math.floor(imgWidth/o.sections); // Used when transitioning lr and rl
				var sectionHeight = Math.floor(imgHeight/o.sections); // Used when transitioning tb and bt
				if (imgWidth%o.sections != 0) sectionsHoriz++; // This will either equal sections or sections+1
				if (imgHeight%o.sections != 0) sectionsVert++; // This will either equal sections or sections+1
				$(this).css({'width':imgWidth,'height':imgHeight}); // Sets the container width and height to match the first image's dimensions

				var imgOffsetLeft = 0;
				var imgOffsetTop = 0;
				var panelIDArrayVert = new Array(); // In order to accommodate multiple containers, we need unique div IDs
				var panelIDArrayHoriz = new Array(); // In order to accommodate multiple containers, we need unique div IDs

				for(var i=0;i<sectionsHoriz;i++)
				{
					panelID = getRandom();
					$(this).append('<div class="sectionHoriz" id="p'+panelID+'">'); // Create a new div 'part'
					$("#p"+panelID).css({'left':imgOffsetLeft+'px','background-position':-imgOffsetLeft+'px 50%','display':'none'}); // Set the left offset and background position. THIS ISNT WORKING IN WEBKIT
					imgOffsetLeft = imgOffsetLeft + sectionWidth;	// Increment the offset
					panelIDArrayHoriz[i] = panelID;
				}
				if(o.direction == "lr" || o.direction == "rl") $("div.sectionHoriz", obj).css({'top':'0px','background-repeat':'no-repeat','position':'absolute','z-index':'10','width':sectionWidth+'px','height':imgHeight+'px','float':'left','background-image':'url('+$("img:eq(1)", obj).attr("src")+')'});

				for(var i=0;i<sectionsVert;i++)
				{
					panelID = getRandom();
					$(this).append('<div class="sectionVert" id="p'+panelID+'">'); // Create a new div 'part'
					$("#p"+panelID).css({'top':imgOffsetTop+'px','background-position':'50% '+-imgOffsetTop+'px','display':'none'}); // Set the left offset and background position
					imgOffsetTop = imgOffsetTop + sectionHeight;	// Increment the offset
					panelIDArrayVert[i] = panelID;
				}
				$("div.sectionVert", obj).css({'left':'0px','background-repeat':'no-repeat','position':'absolute','z-index':'10','width':imgWidth+'px','height':sectionHeight+'px','background-image':'url('+$("img:eq(1)", obj).attr("src")+')'});

				var doingSection=0, doingImage=1, isHorizReversed = false, isVertReversed = false;

				function doNext()
				{
					doingSection++;
					var currentDirection = getDirection(doingImage);

					if((currentDirection == "lr" || currentDirection == "rl") && doingSection<sectionsHoriz)
					{
						$("#p"+panelIDArrayHoriz[doingSection]).fadeIn(o.sectionTransitionDelay,doNext);
					}
					else if((currentDirection == "tb" || currentDirection == "bt") && doingSection<sectionsVert)
					{
						$("#p"+panelIDArrayVert[doingSection]).fadeIn(o.sectionTransitionDelay,doNext);
					}
					else
					{
						//alert('done'+currentDirection);
						if(doingImage == 0 && o.repeat) $("img:last", obj).hide(); // If doingImage = 0 and we're repeating, hide last (top) image
						// When we finish fading in the individual panels, show the corresponding image
						// (which appears under the divs in terms of stacking order). This is a bit of
						// slight of hand and allows us to load up the panel divs with the next image in the sequence.
						$("img:eq("+doingImage+")", obj).show();
						$("div.sectionVert", obj).hide(); // Now hide all the divs so we can change their image
						$("div.sectionHoriz", obj).hide(); // Now hide all the divs so we can change their image
						doingSection=0;
						doingImage++;
						$("div.sectionHoriz", obj).css({'background-image':'url('+$("img:eq("+doingImage+")", obj).attr("src")+')'});
						$("div.sectionVert", obj).css({'background-image':'url('+$("img:eq("+doingImage+")", obj).attr("src")+')'});
						if(doingImage < imgArray.length) // need to stop when doingImage equals imgArray.length
						{
							nextDirection = getDirection(doingImage);
							setupNextTransition(nextDirection);
						}
						else if(o.repeat)
						{
							doingImage = 0;
							$("img:not(:last)", obj).hide(); // Hides all images in the container except the last one
							$("div.sectionVert", obj).hide();
							$("div.sectionHoriz", obj).hide();
							$("div.sectionHoriz", obj).css({'background-image':'url('+$("img:eq(0)", obj).attr("src")+')'});
							$("div.sectionVert", obj).css({'background-image':'url('+$("img:eq(0)", obj).attr("src")+')'});
							firstImageDirection = getDirection(0);
							setupNextTransition(firstImageDirection);
						}
					}
				}
				var startDirection = ($("img:eq(1)", obj).attr("name")=="") ? o.direction: $("img:eq(1)", obj).attr("name"); // Check direction of the second image
				if(startDirection == "rl")
				{
					panelIDArrayHoriz.reverse();
					isHorizReversed = true;
				}
				if(startDirection == "bt")
				{
					panelIDArrayVert.reverse();
					isVertReversed = true;
				}
				var startArray = (startDirection == "lr" || startDirection == "rl") ? panelIDArrayHoriz[0]:panelIDArrayVert[0];
				setTimeout(function(){$("#p"+startArray).fadeIn(o.sectionTransitionDelay,doNext)},o.startDelay); // Kickoff the sequence
 		});
    	}
	});
})(jQuery);