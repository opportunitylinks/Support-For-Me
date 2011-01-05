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
				<a href="<?php print $base_path; ?>" title="<?php print t('Home'); ?>"> <img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" class="logo-fix" /></a>
				<select id="micro" name="microsite" class="hidden">
					<option value="http://staffs.supportforme.info">Staffordshire</option>
					<option value="http://wandsworth.supportforme.info">Wandsworth</option>
				</select>
				
				<?php print $micrositeselector ?>
	        	<ul id="menu">
	            	<?php print theme('links', $primary_links);  ?>
	            </ul>
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
				<div id="slideshow">
					<?php print $laheader; ?>
					<img src="/sites/default/files/ribbon-diagonal.png" class="ribbon fix" width="182" height="161" title="Ribbon" alt="Ribbon" />
				</div>
				<div class="maincontent">
				
				<!-- Contentflow slideshow... -->
				
				
				<h2>Select your local authority...</h2>
				<div id="coverflow">
            	
					<img src="<?php print $base_path . $directory; ?>/images/arrow-left.png" class="arrow left" title="Left arrow" alt="Left arrow" />
    	            <img src="<?php print $base_path . $directory; ?>/images/arrow-right.png" class="arrow right" alt="Right arrow" />

            		<div class="loadIndicator"><div class="indicator"></div></div>
            		<div class="flow">
                		<a class="item" href="#"><img class="content" src="<?php print $base_path . $directory; ?>/images/authorities/calerdale.jpg" title="Calerdale"/><span class="caption">Calerdale</span></a>
                		<a class="item" href="#"><img class="content" src="<?php print $base_path . $directory; ?>/images/authorities/cornwall.jpg" title="Cornwall"/><span class="caption">Cornwall</span></a>
						<a class="item" href="#"><img class="content" src="<?php print $base_path . $directory; ?>/images/authorities/coventry.jpg" title="Coventry" alt="Coventry" /><span class="caption">Coventry</span></a>
						<a class="item" href="#"><img class="content" src="<?php print $base_path . $directory; ?>/images/authorities/darlington.jpg" title="Darlington" alt="Darlington" /><span class="caption">Darlington</span></a>
						<a class="item" href="#"><img class="content" src="<?php print $base_path . $directory; ?>/images/authorities/devon.jpg" title="Devon" alt="Devon" /><span class="caption">Devon</span></a>
						<a class="item" href="#"><img class="content" src="<?php print $base_path . $directory; ?>/images/authorities/manchester.jpg" title="Manchester" alt="Manchester" /><span class="caption">Manchester</span></a>
						<a class="item" href="#"><img class="content" src="<?php print $base_path . $directory; ?>/images/authorities/middlesbrough.jpg" title="Middlesbrough" alt="Middlesbrough" /><span class="caption">Middlesbrough</span></a>
						<a class="item" href="#"><img class="content" src="<?php print $base_path . $directory; ?>/images/authorities/northtyneside.jpg" title="North Tyneside" alt="North Tyneside" /><span class="caption">North Tyneside</span></a>
						<a class="item" href="#"><img class="content" src="<?php print $base_path . $directory; ?>/images/authorities/nottinghamshire.jpg" title="Nottinghamshire" alt="Nottinghamshire" /><span class="caption">Nottinghamshire</span></a>
						<a class="item" href="#"><img class="content" src="<?php print $base_path . $directory; ?>/images/authorities/redbridge.jpg" title="Redbridge" alt="Redbridge" /><span class="caption">Redbridge</span></a>
						<a class="item" href="http://staffs.supportforme.info"><img class="content" src="<?php print $base_path . $directory; ?>/images/authorities/staffordshire.jpg" title="Staffordshire"" title="Staffordshire"/><span class="caption">Staffordshire</span></a>
						<a class="item" href="#"><img class="content" src="<?php print $base_path . $directory; ?>/images/authorities/stockton.jpg" title="Stockton" alt="Stockton" /><span class="caption">Stockton</span></a>
						<a class="item" href="#"><img class="content" src="<?php print $base_path . $directory; ?>/images/authorities/suffolk.jpg" title="Suffolk" alt="Suffolk" /><span class="caption">Suffolk</span></a>
						<a class="item" href="http://wandsworth.supportforme.info"><img class="content" src="<?php print $base_path . $directory; ?>/images/authorities/wandsworth.jpg" title="Wandsworth"" title="Wandsworth"/><span class="caption">Wandsworth</span></a>
            		</div>
					<div class="scrollbar">
						<div class="slider"></div>
                    </div>
                    <div class="highlight" style="display: none;">
                    	<h3>Loading...</h3>
                            <p>Family Information Service</p>
                        </div>
        		</div>
				
						<h2>...or choose from the list below:</h2>
				</div>
				<div id="select" class="hidden">
					<div class="shadow">
						<div class="highlight">
							<div class="content">
								<img src="/sites/default/files/select-logo.png" class="logo" width="137" height="54" title="Select logo" alt="Select logo" />
								<select id="microsite" name="microsite">
									<option value="http://staffs.supportforme.info">Staffordshire</option>
									<option value="http://wandsworth.supportforme.info">Wandsworth</option>
								</select>
								<input class="fix" type="submit" id="go" name="go" value="&nbsp;"/>
							</div>
						</div>
					</div>
					<div class="note">
						<em>We apologise if your Local Authority is not listed.</em>
					</div>
				</div>
				<div id="info">
					<div id="opplinks" class="shadow">
						<div class="highlight">
							<div class="content">
								<h4><span class="highlight-1">Opportunity</span> <span class="highlight-2">Links</span></h4>
								<p>Opportunity Links supports government to deliver high quality information to the public through IT, new media and strategic support.</p>
							</div>
						</div>
					</div>
					<div id="sfm" class="shadow">
						<div class="highlight">
							<div class="content">
								<img src="/sites/default/files/what-is-thumb.jpg" width="124" height="120" title="Photo of PA and PA employee" alt="Photo of PA and PA employee" />
								<h4>What is <span class="highlight-1">Support</span><span class="highlight-2"> for Me</span>?</h4>
								<p>Support for Me is our national online service for delivering adult social care information to the public. Local authorities can develop their own presence on the site to help fulfil the duty to deliver universal information services in their region.</p>
							</div>
						</div>
					</div>
				</div>
				
				
				<!-- Ends... -->
				
					<?php print $content; ?>
				</div>
			</div>
		</div>
		<div id="footer">
			<div class="wrapper">
	            <div class="links">
		            <div class="links">
						<?php print $footerlinks; ?>
					</div>
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
<script type="text/javascript">
    <!--
    $(document).ready(function(){
        $(".js").fadeIn('slow').removeClass("hidden");
        $("#select").fadeIn('slow').removeClass("hidden");
      	$("#go").click(function() {
            
            $("#microsite option:selected").each(function() {
                $(location).attr("href", $(this).val().toLowerCase());
            });
        });  
        $("#micro").change(function() {
            
            $("#micro option:selected").each(function() {
                $(location).attr("href", $(this).val().toLowerCase());
            });
        });  
    });
    -->
    </script>
	    <?php print $closure; ?>
	    
	</body>
</html>