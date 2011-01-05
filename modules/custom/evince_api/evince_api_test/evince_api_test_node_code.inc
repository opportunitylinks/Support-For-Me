<?php
// $Id$
/**
 * @file
 * evince webservice api node create/delete
 *
 * provides node create and delete functions for api test nodes
 */

/**
 * node add/delete code
 */

define("SFM_RS_COOKIE", "sfm-result-set");

function evince_api_test_delete_nodes() {
  $node_type = variable_get('evince_api_node_type', '');

  // get result set id from cookie.  Fallback if no cookie is user sid.
  global $user;
  $result_set_id = isset($_COOKIE[SFM_RS_COOKIE]) ? $_COOKIE[SFM_RS_COOKIE] : $user->sid;

  if ($node_type) {
    $sql = "SELECT n.nid FROM {node} n JOIN content_type_%s c ON n.nid=c.nid WHERE n.type='%s' AND c.field_result_set_id_value='%s'";

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


function evince_api_test_create_node($item) {

  $node_type = variable_get('evince_api_node_type', '');

  if ($node_type) {
    $sfm_node = new stdClass();

    $sfm_node->title = $item['title'];
    $sfm_node->body = $item['description'];
    $sfm_node->teaser = node_teaser($sfm_node->body);
    $sfm_node->type = $node_type;
    $sfm_node->created = time();
    $sfm_node->changed = $sfm_node->created;
    $sfm_node->status = 1;
    $sfm_node->promote = 0;
    $sfm_node->sticky = 0;
    $sfm_node->format = 1;
    $sfm_node->uid = 1;
    $sfm_node->language = '';   //language neutral

    global $user;
    $result_set_id = $user->sid;
    setcookie(SFM_RS_COOKIE, $result_set_id, time() + 86400, '/');
    $sfm_node->field_result_set_id[0]['value'] = $result_set_id;

    $sfm_node->field_record_type[0]['value'] = 'not yet set';
    $sfm_node->field_relevance[0]['value'] = 1;

    $rand_month = str_pad(rand(9, 12), 2, 0, STR_PAD_LEFT);
    $rand_day = str_pad(rand(1, 28), 2, 0, STR_PAD_LEFT);
    $rand_time = str_pad(rand(8, 12), 2, 0, STR_PAD_LEFT);
    $rand_time2 = str_pad(rand(13, 19), 2, 0, STR_PAD_LEFT);
    $sfm_node->field_date[0]['value'] = '2010-'. $rand_month .'-'. $rand_day .'T'. $rand_time .':00:00';
    $sfm_node->field_date[0]['value2'] = '2010-'. $rand_month .'-'. $rand_day .'T'. $rand_time2 .':00:00';

    $model_name = 'http://opp-links.org.uk/XMLSchema/AtomModel';
    $subitem = $item['content'][0]['child'][$model_name]['model'][0]['child'][$model_name];

    $sfm_node->locations[0]['lid'] = 1;
    $sfm_node->locations[0]['name'] = '';
    $sfm_node->locations[0]['street'] = '';
    $sfm_node->locations[0]['additional'] = '';
    $sfm_node->locations[0]['city'] = '';
    $sfm_node->locations[0]['province'] = '';
    $sfm_node->locations[0]['postal_code'] = $subitem['postcode'][0]['data'];
    $sfm_node->locations[0]['country'] = 'uk';
    $sfm_node->locations[0]['source'] = 1;
    $sfm_node->locations[0]['is_primary'] = 1;
    $sfm_node->locations[0]['locpick'] = array(
      'user_latitude' => $item['latitude'],
      'user_longitude' => $item['longitude'],
    );
    $sfm_node->locations[0]['province_name'] = '';
    $sfm_node->locations[0]['country_name'] = 'United Kingdom';

    $sfm_node->field_relevance[0]['value'] = $item['relevance'];

    $type = $subitem['contactnumber'][0]['child'][$model_name]['type'][0]['data'];
    $number = $subitem['contactnumber'][0]['child'][$model_name]['number'][0]['data'];
    $sfm_node->field_phone[0]['value'] = $type == 'Telephone' ? $number : '';
    $sfm_node->field_mobile[0]['value'] = $type == 'Mobile' ? $number : '';
    $sfm_node->field_email[0]['value'] = $subitem['email'][0]['data'];
    $sfm_node->field_contact[0]['value'] = $number ? $number : $email;
    $sfm_node->field_record_type[0]['value'] = $subitem['recordtype'][0]['data'];

    node_save($sfm_node);
  }
}
