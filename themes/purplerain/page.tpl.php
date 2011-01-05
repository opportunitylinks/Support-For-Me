<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" lang="<?php print $language->language; ?>" xml:lang="<?php print $language->language; ?>">
	<head>
		<title><?php print $head_title; ?></title>
		<?php print $head; ?>
		<?php print $styles; ?>
		<!--[if lte IE 7]>
			<link rel="stylesheet" href="<?php print $base_path . $directory; ?>/ie7.css" type="text/css">    
		<![endif]-->
		<!--[if lte IE 6]>
			<link rel="stylesheet" href="<?php print $base_path . $directory; ?>/ie6.css" type="text/css"> 
				<style type="text/css">
		    	.fix { behavior: url(<?php print $base_path . $directory; ?>include/iepngfix/iepngfix.htc); }
			</style>   
		<![endif]-->
		<?php print $scripts; ?>
	</head>
	<body id="microsite">
		<div id="header">
	   		<div class="wrapper">
				<a href="http://demo.supportforme.info" title="<?php print t('Home'); ?>"> <img src="/sites/all/themes/supportforme/images/logo.png" alt="<?php print t('Home'); ?>" class="logo-fix" /></a>
				<?php print $micrositeselector ?>
	        	<ul id="menu">
	            	<?php print theme('links', $primary_links);  ?>
	            <!-- </ul> -->
	        </div>
	    </div>
	   	<div id="filler">
	    </div>
	    <div id="banner">
	    	<div class="wrapper">
				<div id="quote">
				</div>
	        </div>
	</div>
	    <div id="page">
	    	<div class="wrapper">
	        	<div class="title-page">
					<img src="<?php print $logo; ?>" class="logo-page" title="<?php print $site_name; ?> logo" alt="<?php print $site_name; ?> logo">
					<div class="ribbon-page fix">
						<h1><?php print $site_name; ?></h1>
					</div>
					<h2><?php print $title; ?></h2>
            	</div>	            
            	<div class="maincontent">
					<?php print $quicksearch; ?>
		            <?php print $content; ?>
	            </div>
	        </div>
	    </div>
		<div id="footer">
			<div class="wrapper">
	            <div class="links">
					<?php print $footerlinks; ?>
	            </div>
	            <img src="<?php print $base_path . $directory ?>/images/footer-break.png" class="break" width="1" height="150" />
	            <div class="powered">
					<?php print $footerpowered; ?>
	            </div>
	            <img src="<?php print $base_path . $directory ?>/images/footer-break.png" class="break" width="1" height="150" />
	            <div class="icons">
	            	<?php print $footericons; ?>    
	           	</div>
	   		</div>
	    </div>
	    <div id="version">
	        <div class="wrapper">
	            <?php print $versioninfo; ?>
	        </div>
	    </div>
	    <?php print $closure; ?>
	</body>
</html>