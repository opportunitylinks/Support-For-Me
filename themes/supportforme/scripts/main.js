var myNewFlow = new ContentFlow('coverflow',
{
    visibleItems:       4,
    flowDragFriction:   0,
    scrollWheelSpeed:   0,
    onMakeActive:       function(img)
    {
        $("#coverflow .arrow, #coverflow .highlight").show();
        $("#coverflow h3").text(img.caption.innerHTML);
    }
});

$(function()
{
    $(".js").show();
    
    $("#coverflow .arrow.left").click(function()
    {
        myNewFlow.moveTo("previous");
    });
    $("#coverflow .arrow.right").click(function()
    {
        myNewFlow.moveTo("next");
    });

});