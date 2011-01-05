<?php
#This script is designed to be possible to run as a more
#privileged user than the web environment to create
#apache conf or other operations
#
#Move this script to the base drupal directory, where you can run it
#This will only work if your main drupal site is defined 
# in sites/default/settings.php

include_once './includes/bootstrap.inc';
// disable error reporting for bootstrap process
error_reporting(E_ERROR);
// let's bootstrap: we will be able to use drupal apis
drupal_bootstrap(DRUPAL_BOOTSTRAP_FULL);
// enable full error reporting again
error_reporting(E_ALL);


// allow execution only from the command line!
if(empty($_SERVER['REQUEST_METHOD'])) {
  multisite_manager_batch_install();
}
else {
  print t('This script is only executable from the command line.');
  die();
}


// This function installs all of the pending drupal sites. It is meant to be run by an external script.
function multisite_manager_batch_install() {
  // XXX This query will install multiple times sites that have several revisions once the _update function is
  // properly overriden in the .module file.
  $result = db_query("SELECT * FROM {drupal_site} WHERE installed = 0");
  while ($node = db_fetch_object($result)) {
    multisite_manager_install_site($node);
    db_query("UPDATE {drupal_site} SET installed = 1 WHERE vid = %d and nid = %d", $node->vid, $node->nid);
  }
}
