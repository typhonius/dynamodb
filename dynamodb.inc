<?php

/**
 * @file
 *
 */

require dirname(__FILE__) . '/vendor/autoload.php';

class DynamodbCache implements DrupalCacheInterface {
  function __construct() {
	  global $conf;

	}

  /**
   * Implements DrupalCacheInterface::get().
   */
  function get($cid) {
    return FALSE;
  }

  /**
   * Implements DrupalCacheInterface::get().
   */
  function getMultiple(&$cid) {
    return array();
  }

  /**
   * Implements DrupalCacheInterface::set().
   */
  function set($cid, $data, $expire = CACHE_PERMANENT) {
  }

  /**
   * Implements DrupalCacheInterface::clear().
   */
  function clear($cid = NULL, $wildcard = FALSE) {

  }

  /**
   * Implements DrupalCacheInterface::get().
   */
  function isEmpty() {
    return FALSE;
  }

}
