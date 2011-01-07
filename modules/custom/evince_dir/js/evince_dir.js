//$(document).ready(function(){
//  $("div#sfmtabcal").hide();
//  $("div#sfmtabmap").fadeOut('fast');   // forces a map resize on .show so displays correctly
//  $("li#tabsfmlist").addClass("active");
//  $("li#tabsfmlist").click(function(){$("div.sfmtab").hide();$("div#sfmtablist").show();$("ul#tablinks li").removeClass("active");$(this).addClass("active");});
//  $("li#tabsfmcal").click(function(){$("div.sfmtab").hide();$("div#sfmtabcal").show();$("ul#tablinks li").removeClass("active");$(this).addClass("active");});
//  $("li#tabsfmmap").click(function(){ $("div.sfmtab").hide(); $("div#sfmtabmap").show();$("ul#tablinks li").removeClass("active");$(this).addClass("active");});
//});

$(document).ready(function(){
			
	$("li#tabsfmlist").click(function(){
		
		$("div.sfmtab").hide(); // Hides all div's using ".sfmtab" class.
		$("div#sfmtablist").show(); // Shows "#sfmtablist" by default.
		$("ul#tablinks li").removeClass("active"); // Remove any current "active" class tabs 
		$(this).addClass("active"); // Add "active" class to current tab (#sfmtablist)
		$.cookie('sfmtabcontrol', 'sfmlist');	
	});

	$("li#tabsfmcal").click(function(){
		
		$("div.sfmtab").hide();
		$("div#sfmtabcal").show();
		$("ul#tablinks li").removeClass("active");
		$(this).addClass("active");
		$.cookie('sfmtabcontrol', 'sfmcal');
	});
	
	$("li#tabsfmmap").click(function(){ 
		
		$("div.sfmtab").hide();
		$("div#sfmtabmap").show();
		$("ul#tablinks li").removeClass("active");
		$(this).addClass("active");
		$.cookie('sfmtabcontrol', 'sfmmap');
	});
	
	var sfmtabcontrol = $.cookie('sfmtabcontrol');

	switch (sfmtabcontrol) {
		case "sfmlist":
				
				$("div.sfmtab").hide();
				$("ul#tablinks li").removeClass("active"); // Remove any current "active" class tabs 
				$("div#sfmtablist").show(); // Shows "#sfmtablist" by default.
				$(this).addClass("active"); // Add "active" class to current tab (#sfmtablist)
				$.cookie('sfmtabcontrol', 'sfmlist');
				break;

		case "sfmcal":
				
				$("div.sfmtab").hide();
				$("ul#tablinks li").removeClass("active");
				$("div#sfmtabcal").show();

				$(this).addClass("active");
				$.cookie('sfmtabcontrol', 'sfmcal');
				break;

		case "sfmmap":
				
				$("div#sfmtablist").hide();
				$("div.sfmtab").hide();
				$("ul#tablinks li").removeClass("active");
				$("div#sfmtabmap").show();
				$(this).addClass("active");
				$.cookie('sfmtabcontrol', 'sfmmap');
				break;
				 

		default:
			
				$("div#sfmtabcal").hide();
				$("div#sfmtabmap").fadeOut('fast');   // forces a map resize on .show so displays correctly
				$("div.sfmtab").show();
				$("li#tabsfmlist").addClass("active");
				$.cookie('sfmtabcontrol', 'sfmlist');


	}
});
