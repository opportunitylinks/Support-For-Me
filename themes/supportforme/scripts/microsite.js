$(function()
{
    var links = $("#menulinks");

    var menuHover = false;
    var menuLocked = false;

    var timeout = null;

    $("#menu li.more").mouseenter(function()
    {
        menuHover = true;

        var offset = $(this).position();

        $(links).css({ top: (offset.top + 100) +"px", left: (offset.left - 75) +"px" });
        $(links).slideDown(100);
    })
    .mouseleave(function()
    {
        menuHover = false;

        clearTimeout(timeout);
        timeout = setTimeout
        (
            function()
            {
                timeout = null;
                hideMenuLinks();
            },
            100
        );
    });

    $("#menulinks").mouseenter(function()
    {
        menuLocked = true;
    })
    .mouseleave(function()
    {
        menuLocked = false;
        
        clearTimeout(timeout);
        timeout = setTimeout
        (
            function()
            {
                timeout = null;
                hideMenuLinks();
            },
            100
        );
    });

    function hideMenuLinks()
    {
        if (!menuHover && !menuLocked)
        {
            $(links).slideUp(100);
        }
    }
});