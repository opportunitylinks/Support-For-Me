<?php
// $Id$
/**
 * @file
 * evince dir postcode
 *
 * evince directory postcode functions
 */
function check_postcode(&$to_check) {

  // Permitted letters depend upon their position in the postcode.
  $alpha1 = "[abcdefghijklmnoprstuwyz]";                          // Character 1
  $alpha2 = "[abcdefghklmnopqrstuvwxy]";                          // Character 2
  $alpha3 = "[abcdefghjkpmnrstuvwxy]";                            // Character 3
  $alpha4 = "[abehmnprvwxy]";                                     // Character 4
  $alpha5 = "[abdefghjlnpqrstuwxyz]";                             // Character 5
  
  // Expression for postcodes: AN NAA, ANN NAA, AAN NAA, and AANN NAA with a space
  $pcexp[0] = '^('. $alpha1 .'{1}'. $alpha2 .'{0,1}[0-9]{1,2})([[:space:]]{0,})([0-9]{1}'. $alpha5 .'{2})$';

  // Expression for postcodes: ANA NAA
  $pcexp[1] =  '^('. $alpha1 .'{1}[0-9]{1}'. $alpha3 .'{1})([[:space:]]{0,})([0-9]{1}'. $alpha5 .'{2})$';

  // Expression for postcodes: AANA NAA
  $pcexp[2] =  '^('. $alpha1 .'{1}'. $alpha2 .'{1}[0-9]{1}'. $alpha4 .')([[:space:]]{0,})([0-9]{1}'. $alpha5 .'{2})$';
  
  // Exception for the special postcode GIR 0AA
  $pcexp[3] =  '^(gir)(0aa)$';
  
  // Standard BFPO numbers
  $pcexp[4] = '^(bfpo)([0-9]{1,4})$';
  
  // c/o BFPO numbers
  $pcexp[5] = '^(bfpo)(c\/o[0-9]{1,3})$';
  
  // Overseas Territories
  $pcexp[6] = '^([a-z]{4})(1zz)$/i';

  // Load up the string to check, converting into lowercase
  $postcode = strtolower($to_check);

  // Assume we are not going to find a valid postcode
  $valid = FALSE;
  
  // Check the string against the six types of postcodes
  foreach ($pcexp as $regexp) {
  
    if (ereg($regexp, $postcode, $matches)) {
      
      // Load new postcode back into the form element  
      $postcode = strtoupper($matches[1] . ' ' . $matches [3]);
      
      // Take account of the special BFPO c/o format
      $postcode = ereg_replace('C\/O', 'c/o ', $postcode);
      
      // Remember that we have found that the code is valid and break from loop
      $valid = TRUE;
      break;
    }
  }
    
  // Return with the reformatted valid postcode in uppercase if the postcode was 
  // valid - (Webmech - but only the first part!)
  if ($valid) {
    $to_check = strtok($postcode, ' '); 
    return TRUE;
  } 
  else return FALSE;
}

function get_lat_long($code) {
  if (!$code) {
    return FALSE;
  };
  $maps_api_key = variable_get('googlemap_api_key', '');
  $query = "http://maps.google.co.uk/maps/geo?q=" . urlencode($code[0]) . "&output=json&key=" . $maps_api_key;
  $data = file_get_contents($query);
// if data returned
  if ($data) {
// convert into readable format
    $data = json_decode($data);
    $long = $data->Placemark[0]->Point->coordinates[0];
    $lat = $data->Placemark[0]->Point->coordinates[1];

    return array('Latitude' => $lat, 'Longitude' => $long);
  } 
  else {
    return FALSE;
  }
}
