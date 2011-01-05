$(document).ready(function(){
  $("div#sfmtabcal").hide();
  $("div#sfmtabmap").fadeOut('fast');	// forces a map resize on .show so displays correctly
  $("li#tabsfmlist").addClass("active");
  $("li#tabsfmlist").click(function(){$("div.sfmtab").hide();$("div#sfmtablist").show();$("ul#tablinks li").removeClass("active");$(this).addClass("active");});
  $("li#tabsfmcal").click(function(){$("div.sfmtab").hide();$("div#sfmtabcal").show();$("ul#tablinks li").removeClass("active");$(this).addClass("active");});
  $("li#tabsfmmap").click(function(){ $("div.sfmtab").hide(); $("div#sfmtabmap").show();$("ul#tablinks li").removeClass("active");$(this).addClass("active");});
});
