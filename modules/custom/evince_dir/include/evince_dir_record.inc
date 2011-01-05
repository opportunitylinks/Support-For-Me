<?php
// $Id$
/**
 * @file
 * evince dir display single record
 *
 * displays a single evince record
 */

function evince_dir_display_record($record_type = NULL, $record_id = 0, $ref, $page) {

  if (empty($record_type) || empty($record_id)) {
    drupal_set_message('no record to display', 'warning');
    return;
  }

  $data = evince_api_get_record($record_type, $record_id);

  if (empty($data)) {
    drupal_set_message('no data returned from API', 'warning');
    return;
  }
  global $user;
  if ($user->uid) {
    dsm($data->data, "Record data");

  
  }
  $xml = new SimpleXMLElement($data->data);
  $xml = (array)$xml;
  
  if ($record_type=="ascserviceproviders"){
  	$allservices = (array)$xml['Services'];
  	$services = (array)$allservices['Service'];
		for($i=0; $i<count($services); $i++) {
			$services_provided[$i] = $services[$i][1];
		}
		dsm ($services_provided, "Services provided...");
    $services_provided = implode('<br />', $services_provided);
  	
  }
  
  $title = $xml['DC.Title'];

  $description = (array)$xml['DC.Description'][1];
  $description = $description['DC.Description'];
  $contact_details = (array)$xml['ContactDetails'];

//Address
  $address = (array)$contact_details['Address'];
	if (!empty($address)) {
	  // Get long and lat for Google maps...
	  $gridref = (array)$address['GridReference'];
	
	  $bs7666_address = (array)$address['BS7666Address'];
	
	  $paon = (array)$bs7666_address['PAON'];
	  $paon = $paon['Description'];
	
	  $street = $bs7666_address['StreetDescription'];
	  $town = $bs7666_address['Town'];
	  $post_town = $bs7666_address['PostTown'];
	  $postcode = $bs7666_address['PostCode'];
	  $address = NULL;
	  if (is_numeric(substr($paon, 0, 1))) {
	    $address = array();
	    $address[] = $paon . " " . $street;;
	  } 
	  else {
	    $address = array();
	    $address[] = $paon;
	    $address[] = $street;
	  }
	  if ($town) {
	    $address[] = $town;
	  }
	  if ($post_town) {
	    $address[] = $post_town;
	  }
	  $address[] = $postcode;
	  $address = implode('<br />', $address);
    $longitude = $gridref['Longitude'];
    $latitude = $gridref['Latitude'];
  } // End check for address

//Contact Details
  $contact_number = (array)$contact_details['ContactNumber'];
  $contact_number = $contact_number['TelNationalNumber'];
  $contact_number = format_telfax2($contact_details['ContactNumber'][0]->TelNationalNumber);

  $email_address = (array)$contact_details['EmailAddress'];
  $email_address = $email_address['EmailAddress'];

  $website_address = $contact_details['WebsiteAddress'];
  if ($website_address) {
    $website_address = (substr(ltrim($website_address), 0, 7) != 'http://' ? 'http://' : '') . $website_address;
  }
  $contacts = array();
  $contacts[] = 'Telephone: '. $contact_number;
  if ($email_address) {
    $contacts[] = 'Email: <a href="mailto:'. $email_address .'">' . $email_address . '</a>';
  }
  if ($website_address) {
    $contacts[] = 'Web: <a href="'. $website_address .'">'. $website_address . '</a>';
  }
  if (empty($contacts)) {
    $contacts[]='';
  }
  $contacts = implode('<br />', $contacts);

//Availability - to process [Period][Day] etc.
  $avail = (array)$xml['Availability'];
  $periods = (array)$avail['Period'];
  $days = (array)$periods['Day'];
  $availability2 = array();
  foreach ($days as $period) {
    $availability2[] = $period;
  }
  $availability2_details = (array)$avail['Details'];
  foreach ($availability2_details as $details) {
    $availability2[] = $details;
  }
  $availability2 = implode('<br />', $availability2);

//Availability - process start and end dates for services only
  $avail = (array)$xml['Availability'];
  $start = $avail['StartDateTime'];
  $end = $avail['EndDateTime'];
  if ($record_type == 'ascservices') {
  if ($start && $start!='') {
    $availability = array();
    $ignore_repeats = FALSE;
    if (strtok($start, ' ') == strtok($end, ' ')) {
    $availability[] = date("D d/m/Y", strtotime($start));
    $ignore_repeats = TRUE;
    } 
    else {
      $availability[] = date("D d/m/Y", strtotime($start)) . ' to ' . date("D d/m/Y", strtotime($end));
    }
    if (strstr($start, 'T') == strstr($end, 'T')) {
      $availability[] = 'All day';
    } 
    else {
      $availability[] = 'From ' . date("ga", strtotime($start)) . ' to ' . date("ga", strtotime($end));
    }
    $availability = implode('<br />', $availability);
  }

  }
  
//Suitable Age Range
  $age_range = (array)$xml['SuitableAgeRange'];
  $age_from = (array)$age_range['From'];
  $age_to = (array)$age_range['To'];
  $agerange = array();
  if ($age_from) {
    $agerange[] = 'From: ' . $age_from['Years'] . 'yrs ';
    if ($age_from['Months']) {
      $agerange[] .= $age_from['Months'] . 'm';
    }
    if ($age_to['Years']) {
      $agerange[] = 'To: ' . $age_to['Years'] . 'yrs ';
      if ($age_to['Months']) {
        }
        $agerange[] .=  $age_to['Months'] . 'm';
      }
  } 
  else {
    $agerange[]='';
  }
  $agerange = implode('<br />', $agerange);

//Eligibility
  $eligibility = (array)$xml['EligibilityCriteria'];
  $eligible = $eligibility['Details'];

//Referrals
  $referral = (array)$xml['ReferralCriteria'];
  $refer = $referral['Details'];

//Referral Procedure
  $referralprocedure = (array)$xml['ReferralProcedure'];
  $referproc = $referralprocedure['Details'];

//SpecialProvisions
  if (is_array($xml['SpecialProvisions'])) {
    $provision = $xml['SpecialProvisions'];
    $provides = $provision['Details'];

    $wca = $provision['WheelchairAccess'];
    if ($wca -> HasProvision) {
      $wca = "Wheelchair access" . $wca -> Details;
    }
    else {
      $wca = "No wheelchair access";
    }

    $cp = $provision['CulturalProvision'];
    if ($cp -> HasProvision) {
      $cp = "Cultural Provision" . $cp -> Details . $cp -> Experiences;
    }
    else {
      $cp = "No cultural provision";
    }

    $sd = $provision['SpecialDiet'];
    if ($sd -> HasProvision) {
      $sd = "Special Dietary needs" . $sd -> Details . $sd -> Experiences;
    }
    else {
      $sd = "No provision for special dietary needs";
    }

    $sn = $provision['SpecialNeeds'];
    if ($sn -> HasProvision) {
      $sn = "Special needs" . $sn -> Details . $sn -> Experiences;
    }
    else {
      $sn = "No special needs provision";
    }

    $sprov = array();
    $sprov[] = $provides;
    $sprov[] = $wca;
    $sprov[] = $cp;
    $sprov[] = $sd;
    $sprov[] = $sn;
    $sprov = implode('<br />', $sprov);
  }
  else {
    $sprov = NULL;
  }

//Notes
  $notes = (array)$xml['Notes'];

//Costs
	if (!empty($xml['CostDetails'])) {    
	  $costs = array();
    $cost_details = (array)$xml['CostDetails'];
    //dsm($cost_details);
    $contact_for_costs = $cost_details['ContactForCosts'];
    $other_costs = $cost_details['OtherCosts'];
    if ($contact_for_costs == "false") {
      if ($cost_details['OtherCosts']) {
     	  $costs[] = $cost_details['OtherCosts'];
     	}
    } 
		if ($contact_for_costs == "true") {
			$costs[] = "Please contact for details.";
    }
  } 
  
  if (!empty($xml['Costs'])) { 
  	//dsm("Found ".count($xml['Costs'])." other costs...");   
	  $othercosts = array();
    $other_costs = (array)$xml['Costs'];
    $cost_types = (array)$other_costs['CostType'];
    $cost_values = (array)$other_costs['Cost'];
		for($i=0; $i<count($cost_types); $i++) {
			$othercosts[$i] = "&pound;".number_format($cost_values[$i]). " ".$cost_types[$i];
		}
    $othercosts = implode('<br />', $othercosts);
	}


//Build output array
//++++++++++++++++++

  $output .= '<h2>'. $title .'</h2>';
  $output .= '<p>'. $description .'</p>';
  if ($address) {
    $hdr = array('Address');
    $row = array();
    $row[] = array(
      '#address' => $address,
    );
    $output .= "<div class='addblock'>" . theme('table', $hdr, $row) . "</div>";
    $output .= "<div id='map_canvas' style='width: 100%; height: 100%'></div>";
  }
  if ($contacts) {
    $hdr = array('Contact');
    $row = array();
    $row[] = array(
     '#contacts' => $contacts,
    );
    $output .= "<div class='conblock'>" . theme('table', $hdr, $row) . "</div>";
  }
  if ($agerange) {
    $hdr = array('Age Range');
    $row = array();
    $row[] = array(
      '#agerange' => $agerange,
    );
    $output .= "<div class='agerange'>" . theme('table', $hdr, $row) . "</div>";
  }

  if ($eligible) {
    $hdr = array('Eligibility');
    $row = array();
    $row[] = array(
      '#details' => $eligible,
    );
    $output .= "<div class='eligible'>" . theme('table', $hdr, $row) . "</div>";
  }

  if ($referproc) {
    $hdr = array('Referral Criteria');
    $row = array();
    $row[] = array(
      '#details' => $refer,
      '#procedure' => $referproc,
    );
    $output .= "<div class='refer'>" . theme('table', $hdr, $row) . "</div>";
  }

  if ($sprov) {
    $hdr = array('Special Provisions');
    $row = array();
    $row[] = array(
      '#details' => $sprov,
    );
    $output .= "<div class='provides'>" . theme('table', $hdr, $row) . "</div>";
  }

  if ($notes) {
    $hdr = array('Notes');
    $row = array();
    $row[] = $notes;
    $output .= "<div class='notes'>" . theme('table', $hdr, $row) . "</div>";
  }

  if ($costs) {
    $hdr = array('Costs');
    $row = array();
    $row[] = $costs;
    $output .= "<div class='costs'>" . theme('table', $hdr, $row) . "</div>";
  }
  
  if ($othercosts) {
    $hdr = array('Costs');
    $row = array();
    $row[] = array(
    	'#costs' => $othercosts,
    );
    $output .= "<div class='costs'>" . theme('table', $hdr, $row) . "</div>";
  }

  if ($availability) {
    $hdr = array('Availability');
    $row = array();
    $row[] = array(
      '#avail' => $availability,
    );
    $output .= "<div class='availability'>" . theme('table', $hdr, $row) . "</div>";
  }


  if ($availability2) {
    $hdr = array('Availability');
    $row = array();
    $row[] = array(
      '#avail2' => $availability2,
    );
    $output .= "<div class='availability'>" . theme('table', $hdr, $row) . "</div>";
  }

  $output .= "<p class='back-to-search'><< Go back to <a href='/evince/dir?$ref&page=$page'><strong>your search results</strong></a></p>";
  return $output;
}


function format_telfax2($number, $fax=FALSE) {
  // http://james.cridland.net/code/format_uk_phonenumbers.html
  // v2: worked on by Olly Benson to make it look better and work faster!
  // v2.1: removal of a bugette
  // Change the international number format and remove any non-number character
  $number=ereg_replace( '[^0-9]+', '', str_replace("+", "00", $number)); 
  // Turn number into array based on Telephone Format
  $number_array = split_number($number, explode(",", get_telephone_format($number)));
  // Add brackets around first split of numbers if number starts with 01 or 02
  if (substr($number, 0, 2)=="01" || substr($number, 0, 2)=="02") $number_array[0]="(". $number_array[0] .")";
  // Convert array back into string, split by spaces
  $formatted_number = implode(" ", $number_array);
  return $formatted_number;
}

function get_telephone_format($number) {
  // This uses full codes from http://www.area-codes.org.uk/formatting.shtml
  $telephone_format = array(
    '02' => "3,4,4",
    '03' => "4,3,4",
    '05' => "5,6", 
    '0500' => "4,6",
    '07' => "5,6",
    '08' => "4,3,4",
    '09' => "4,3,4",
    '01' => "5,6",
    '011' => "4,3,4",
    '0121' => "4,3,4",
    '0131' => "4,3,4",
    '0141' => "4,3,4",
    '0151' => "4,3,4",
    '0161' => "4,3,4",
    '0191' => "4,3,4",
    '013873' => "6,5", 
    '015242' => "6,5", 
    '015394' => "6,5",
    '015395' => "6,5",
    '015396' => "6,5",
    '016973' => "6,5",
    '016974' => "6,5",
    '017683' => "6,5",
    '017684' => "6,5",
    '017687' => "6,5",
    '019467' => "6,5",
    '0169737' => "5,6",
    '0169772' => "6,4",
    '0169773' => "6,4",
    '0169774' => "6,4"
  );

  // Sorts into longest key first
  uksort($telephone_format, "sort_str_len");    
  foreach ($telephone_format AS $key => $value) {
    if (substr($number, 0, strlen($key)) == $key) break;
  };
  return $value;
}

function split_number($number, $split) {
  $start=0;
  $array = array();
  foreach ($split AS $value) {
    $array[] = substr($number, $start, $value);
    $start = $start+$value;
  }
  return $array;
}

function sort_str_len($a, $b) {
  return strlen($b)-strlen($a);
}
