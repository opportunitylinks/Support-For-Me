<?php
// $Id$
/**
 * @file
 * evince dir node create / delete functions
 *
 * provides create / delete functions for dir search nodes
 */

/**
 * node add/delete code
 */

function evince_dir_delete_nodes() {
  $node_type = variable_get('evince_api_node_type', '');

  $result_set_id = session_id();
  if ($node_type && $result_set_id) {
    $sql = "SELECT n.nid FROM {node} n JOIN content_type_%s c on n.nid=c.nid WHERE n.type='%s' AND c.field_result_set_id_value='%s'";

    $result = db_query($sql, array($node_type, $node_type, $result_set_id));

    // switch to user 1 while doing deletes.
    // protect against failure part way through by disabling session save.
    global $user;
    $temp_user = $user;
    session_save_session(FALSE);
    $user = user_load(1);

    while ($node = db_fetch_object($result)) {
      node_delete($node->nid);
    }

    $user = $temp_user;
    session_save_session(TRUE);
  }
}


function evince_dir_create_node($item) {

  $node_type = variable_get('evince_api_node_type', '');
  
  if ($node_type) {
    $sfm_node = new stdClass();
    $sfm_node->title = htmlspecialchars_decode($item['title']);
    $sfm_node->body = $item['description'];
    $sfm_node->teaser = node_teaser($sfm_node->body);
    $sfm_node->type = $node_type;
    $sfm_node->created = time();
    $sfm_node->changed = $sfm_node->created;
    $sfm_node->status = 1;
    $sfm_node->promote = 0;
    $sfm_node->sticky = 0;
    $sfm_node->format = 2;
    $sfm_node->uid = 1;
    $sfm_node->language = '';   //language neutral

    $result_set_id = session_id();
    $sfm_node->field_result_set_id[0]['value'] = $result_set_id;

//  Legacy Repeat Date processing...
    $todate = NULL;
    $rrule = NULL;
    $enddate = NULL;

    if ($item['startdate'] == NULL) {
      $sfm_node->field_date = NULL;
    }
    else {
      $fromdate = $item['startdate'];
      $todate = $item['enddate'];
      if ($item['repeats']) {
        $rrule = 'FREQ=DAILY;INTERVAL=1;BYDAY=';
        $enddate = $item['enddate'];
        $todate = strtok($fromdate, 'T') . strstr($enddate, 'T');

        foreach ($item['repeats'] as $dayname) {
          $rrule .= strtoupper(substr($dayname['day'], 0, 2)) .',';
        }
        $rrule = substr($rrule, 0, strlen($rrule)-1);
      }

      if (substr(strstr($fromdate, 'T'), 1, 5) == '00:00') {
        $todate = $item['enddate'];
        $rrule = 'FREQ=DAILY;INTERVAL=1';
        $enddate = $item['enddate'];
      }

      if ($rrule) {
        $rptdates = date_repeat_calc($rrule, $fromdate, $enddate);
        foreach ($rptdates as $rptdate) {
          $rptd = strtok($rptdate, ' ');
          $sfm_node->field_date[] = array(
            'value' => $rptd  . strstr($fromdate, 'T'),
            'value2' => $rptd . strstr($todate, 'T'),
            'rrule' => $rrule .';UNTIL='. date("Ymd", strtotime($enddate)) .'T000000Z;WKST=SU',
            'enddate' => $enddate,
          );
        }
      }
      else {
        $sfm_node->field_date[] = array(
          'value' => $fromdate,
          'value2' => $todate,
          'enddate' => $enddate,
          'timezone_db' => 'Europe/London',
        );
      }
    }
//...end of repeat dates

    $model_name = 'http://opp-links.org.uk/XMLSchema/AtomModel';
    $subitem = $item['content'][0]['child'][$model_name]['model'][0]['child'][$model_name];

    $sfm_node->locations[0]['lid'] = 1;
    $sfm_node->locations[0]['name'] = '';
    $sfm_node->locations[0]['street'] = '';
    $sfm_node->locations[0]['additional'] = '';
    $sfm_node->locations[0]['city'] = $item['location'];
    $sfm_node->locations[0]['province'] = '';
    $sfm_node->locations[0]['postal_code'] = $subitem['postcode'][0]['data'];
    $sfm_node->locations[0]['country'] = 'uk';
    $sfm_node->locations[0]['source'] = 1;
    $sfm_node->locations[0]['is_primary'] = 1;
    $sfm_node->locations[0]['locpick']['user_latitude'] = $item['latitude'];
    $sfm_node->locations[0]['locpick']['user_longitude'] = $item['longitude'];
    $sfm_node->locations[0]['province_name'] = '';
    $sfm_node->locations[0]['country_name'] = 'United Kingdom';

    $sfm_node->field_relevance[0]['value'] = $item['relevance'] * 100;

    $type = $subitem['contactnumber'][0]['child'][$model_name]['type'][0]['data'];
    $number = format_telfax2($subitem['contactnumber'][0]['child'][$model_name]['number'][0]['data']);
    $sfm_node->field_phone[0]['value'] = $type == 'Telephone' ? $number : '';
    $sfm_node->field_mobile[0]['value'] = $type == 'Mobile' ? $number : '';
    $sfm_node->field_email[0]['value'] = $subitem['email'][0]['data'];
    $sfm_node->field_contact[0]['value'] = $number ? $number : $email;
    $sfm_node->field_record_type[0]['value'] = $subitem['recordtype'][0]['data'];
    $sfm_node->field_record_id[0]['value'] = $subitem['recordid'][0]['data'];

    $term = taxonomy_get_term_by_name($subitem['recordtype'][0]['data']);
    $sfm_node->taxonomy[$term[0]->tid] = $term[0];

    node_save($sfm_node);
    return $sfm_node->nid;
  }
}

function evince_dir_set_search($search = array()) {

  $node_type = variable_get('evince_api_search_node_type', 'asc_search');
  $result_set_id = session_id();

  if ($node_type && $result_set_id) {

    $node = node_load(array('type' => $node_type, 'title' => $result_set_id));

    if ($node) {
      $search_node = $node;
    }
    else {
      $search_node = new stdClass();

      $search_node->title = $result_set_id;
      $search_node->type = $node_type;
      $search_node->created = time();
      $search_node->changed = $search_info_node->created;
      $search_node->status = 1;
      $search_node->promote = 0;
      $search_node->sticky = 0;
      $search_node->format = 1;
      $search_node->uid = 1;
      $search_node->language = '';   //language neutral
    }
    $search_node->body = serialize($search);

    node_save($search_node);
  }
}

function evince_dir_get_search() {
  $result_set_id = session_id();

  if ($result_set_id) {
    $node = node_load(array('title' => $result_set_id));
  }

  return $node ? unserialize($node->body) : NULL;
}

function evince_dir_delete_search() {
  $node_type = variable_get('evince_api_search_node_type', 'asc_search');

  $result_set_id = session_id();

  if ($node_type && $result_set_id) {
    $sql = "SELECT n.nid FROM {node} n WHERE n.type='%s' AND n.title='%s'";

    $result = db_query($sql, array($node_type, $result_set_id));

    // switch to user 1 while doing deletes.
    // protect against failure part way through by disabling session save.
    global $user;
    $temp_user = $user;
    session_save_session(FALSE);
    $user = user_load(1);

    // should be only one but loop just in case
    while ($node = db_fetch_object($result)) {
      node_delete($node->nid);
    }

    $user = $temp_user;
    session_save_session(TRUE);
  }
}

include_once(drupal_get_path('module', 'date_repeat') .'/date_repeat_calc.inc');
