<?php
function phptemplate_links($links, $attributes = array()) {

  if (!count($links)) {
    return '';
  }
  $level_tmp = explode('-', key($links));
  $level = $level_tmp[0];
  $output = "<ul class=\"links-$level ".$attributes['class']. "\">\n";
  foreach ($links as $index => $link) {
    $output .= '<li';
    if (stristr($index, 'active')) {
      $output .= ' class="active"';
    }// frontpage AND current-link in menu is <front>
    elseif((drupal_is_front_page()) && ($link['href']=='<front>')){
      $link['attributes']['class'] = 'active';//add class active to <li
      $output .= ' class="active"';//add class active to <a
    }
    $output .= ">". l($link['title'], $link['href'], $link) ."</li>\n";
  }
  
  // Support for Me
  // Custom more... menu 
  //$output .= '<li class="more"><a href="#" class="fix">More</a></li>';
  //$output .= '</ul>';
  //$output .= '<div id="menulinks" style="display: none;">';
  //$output .= '<a href="#">Jobs in Childcare</a>';
  //$output .= '<a href="#">Grandparents</a>';
  //$output .= '<a href="#">Customer Feedback</a>';
  //$output .= '<a href="#">Brokerage Service</a>';
  //$output .= '<a href="#">Privacy</a>';
  //$output .= '</div>';
  //$output .= '</ul>';

  return $output;
}