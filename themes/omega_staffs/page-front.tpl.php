<?php
// $Id: page.tpl.php,v 1.1.2.15 2010/06/14 13:38:05 himerus Exp $
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" 
  "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language ?>" lang="<?php print $language->language ?>" dir="<?php print $language->dir ?>">

<head>
  <title><?php print $head_title; ?></title>
  <?php print $head; ?>
  <?php print $styles; ?>
  <!--[if lte IE 7]>
			<link rel="stylesheet" href="<?php print $base_path . $directory; ?>css/ie7.css" type="text/css">    
		<![endif]-->
		<!--[if lte IE 6]>
			<link rel="stylesheet" href="<?php print $base_path . $directory; ?>css/ie6.css" type="text/css"> 
				<style type="text/css">
		    	.fix { behavior: url(<?php print $base_path . $directory; ?>include/iepngfix/iepngfix.htc); }
			</style>   
		<![endif]-->
  
  <?php print $scripts; ?>
</head>

<body class="<?php print $body_classes; ?> <?php print themer_body_class(); ?>">
  <?php if (!empty($admin)) print $admin; ?>
  <div id="header">
	   		<div class="wrapper">
				<a href="http://supportforme.info" title="<?php print t('Home'); ?>"> <img src="http://supportforme.info/sites/all/themes/supportforme/images/logo.png" alt="<?php print t('Home'); ?>" class="logo-fix" /></a>

				
				
				<div id="menu">
	        	<ul>
					<li class="active"><a href="/" title="" class="active">Home</a></li>
					<li><a href="directory" title="">Directory</a></li>
					
				</ul>
				</div>
	        </div>
	    </div>
	    <div id="banner">
	    	<div class="wrapper">
	    	<?php if ($quote): ?>
				<div id="quote"><?php print $quote; ?></div>
			<?php endif; ?>
				</div>
	        </div>
		</div>
		
  <div id="page" class="container-16 clearfix">
    

    <?php if($header_first || $header_last): ?>
    <div id="header-regions" class="container-<?php print $header_wrapper_width; ?> clearfix">
      <?php if($header_first): ?>
        <div id="header-first" class="<?php print $header_first_classes; ?>">
          <?php print $header_first; ?>
        </div><!-- /#header-first -->
      <?php endif; ?>
      <?php if($header_last): ?>
        <div id="header-last" class="<?php print $header_last_classes; ?>">
          <?php print $header_last; ?>
        </div><!-- /#header-last -->
      <?php endif; ?>
    </div><!-- /#header-regions -->
    <?php endif; ?>
    
    <?php if($site_slogan && $is_front || $search_box || $breadcrumb): ?>
    <div id="internal-nav" class="container-<?php print $internal_nav_wrapper_width; ?> clearfix">
      <div id="slogan-bcrumb" class="grid-<?php print $breadcrumb_slogan_width; ?>">
        <?php if ($site_slogan && $is_front): ?>
          <div id="slogan"><?php print $site_slogan; ?></div><!-- /#slogan -->
        <?php endif; ?>
      </div>
      <?php if ($search_box): ?>
        <div id="search-box" class="grid-<?php print $search_width; ?>"><?php print $search_box; ?></div><!-- /#search-box -->
      <?php endif; ?>
    </div><!-- /#internal-nav -->
    <?php endif; ?>
    
    
    <div id="preface-wrapper" class="container-<?php print $preface_wrapper_grids; ?> clearfix">
        <div id="preface-first" class="preface grid-10">
          <div class="ribbon fix">
						<h1><?php print $site_name; ?></h1>
					</div>
					<?php print $mission; ?>
        </div><!-- /#preface-first -->
        <div id="preface-last" class="preface grid-6">
          <img src="<?php print $logo; ?>" class="logo" title="<?php print $site_name; ?> logo" alt="<?php print $site_name; ?> logo">
        </div><!-- /#preface-last -->
    </div><!-- /#preface-wrapper -->
    
    
    <?php if($help || $messages): ?>
    <div class="container-<?php print $default_container_width; ?> clearfix">
      <div class="grid-<?php print $default_container_width; ?>">
        <?php print $help; ?><?php print $messages; ?>
      </div>
    </div><!-- /.container-xx -->
    <?php endif; ?>
    
    <div id="main-content-container" class="container-<?php print $content_container_width; ?> clearfix">
      <div id="main-wrapper" class="column <?php print $main_content_classes; ?>">
       <div class="clearfix">
        <?php if($content_top): ?>
        <div id="content-top" class="grid-10 alpha">
          <?php print $content_top; ?>
        </div><!-- /#content-top -->
        <?php endif; ?>
        
        <?php if($a_to_z): ?>
        <div id="a-to-z" class="grid-6 omega">
          <?php print $a_to_z; ?>
        </div><!-- /#a_to_z -->
        <?php endif; ?>
        </div>
        <?php if ($tabs): ?>
          <div id="content-tabs" class=""><?php print $tabs; ?></div><!-- /#content-tabs -->
        <?php endif; ?>
    
	<!--DISABLED BECAUSE NOT NECESSARY
        <?php if ($title): ?>
          <h1 class="title" id="page-title"><?php print $title; ?></h1>
        <?php endif; ?>
	-->
    
        <div id="main-content" class="region clearfix">
          <?php print $content; ?>
        </div><!-- /#main-content -->
        
        <?php if($content_bottom): ?>
        <div id="content-bottom">
          <?php print $content_bottom; ?>
        </div><!-- /#content-bottom -->
        <?php endif; ?>
      </div><!-- /#main-wrapper -->
    
      <?php if ($sidebar_first): ?>
        <div id="sidebar-first" class="column sidebar region <?php print $sidebar_first_classes; ?>">
          <?php print $sidebar_first; ?>
        </div><!-- /#sidebar-first -->
      <?php endif; ?>
    
      <?php if ($sidebar_last): ?>
        <div id="sidebar-last" class="column sidebar region <?php print $sidebar_last_classes; ?>">
          <?php print $sidebar_last; ?>
        </div><!-- /#sidebar-last -->
      <?php endif; ?>
    </div><!-- /#main-content-container -->
    
   
  </div><!-- /#page -->
  
  <div id="outer-postscript-wrapper">
   <?php if($postscript_one || $postscript_two || $postscript_three || $postscript_four): ?>
    <div id="postscript-wrapper" class="container-<?php print $postscript_container_width; ?> clearfix">
      <?php if($postscript_one): ?>
        <div id="postscript-one" class="postscript grid-5">
          <?php print $postscript_one; ?>
        </div><!-- /#postscript-one -->
      <?php endif; ?>
      <?php if($postscript_two): ?>
        <div id="postscript-two" class="postscript grid-7">
          <?php print $postscript_two; ?>
        </div><!-- /#postscript-two -->
      <?php endif; ?>
      <?php if($postscript_three): ?>
        <div id="postscript-three" class="postscript grid-4">
          <?php print $postscript_three; ?>
        </div><!-- /#postscript-three -->
      <?php endif; ?>
      <?php if($postscript_four): ?>
        <div id="postscript-four" class="postscript <?php print $postscript_four_classes; ?>">
          <?php print $postscript_four; ?>
        </div><!-- /#postscript-four -->
      <?php endif; ?>
    </div><!-- /#postscript-wrapper -->
    <?php endif; ?>
    
   
  
  </div><!-- #outer-wrapper -->
  
  <div id="outer-footer-wrapper">
   <?php if($footer_first || $footer_last || $footer_message): ?>
    <div id="footer-wrapper" class="container-<?php print $footer_container_width; ?> clearfix">
      <?php if($footer_first): ?>
        <div id="footer-first" class="<?php print $footer_first_classes; ?>">
          <?php print $footer_first; ?>
        </div><!-- /#footer-first -->
      <?php endif; ?>
      <?php if($footer_last || $footer_message): ?>
        <div id="footer-last" class="<?php print $footer_last_classes; ?>">
          <?php print $footer_last; ?>
          <?php if ($footer_message): ?>
            <div id="footer-message">
              <?php print $footer_message; ?>
            </div><!-- /#footer-message -->
          <?php endif; ?>
        </div><!-- /#footer-last -->
      <?php endif; ?>
    </div><!-- /#footer-wrapper -->
    <?php endif; ?>
  </div>
  <?php print $closure; ?>
</body>
</html>
