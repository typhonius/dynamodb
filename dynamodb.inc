<?php

/**
 * @file
 *
 */

require dirname(__FILE__) . '/vendor/autoload.php';

use Aws\DynamoDb\DynamoDbClient;

class DynamodbCache implements DrupalCacheInterface {
  protected $dynamo;

  function __construct($bin) {
	  global $conf;

    $this->bin = $bin;

    $this->dynamo = DynamoDbClient::factory(array(
      'key'    => $conf['dynamodb_access_key'],
      'secret' => $conf['dynamodb_secret_key'],
      'region' => $conf['dynamodb_region_name'],
    ));

	}

  /**
   * Implements DrupalCacheInterface::get().
   */
  function get($cid) {
    global $conf;

    $result = $this->dynamo->getItem(array(
      'ConsistentRead' => true,
      'TableName' => $conf['dynamodb_table'],
      'Key'       => array(
        'cid'   => array('S' => $cid),
        'bin' => array('S' => $this->bin)
      )
    ));

    var_dump($result);

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
    global $conf;

    $data = gzcompress(serialize($data));
//    var_dump($cid);
//    var_dump($this->bin);
//    var_dump(strlen($data));

    $result = $this->dynamo->putItem(array(
      'TableName' => $conf['dynamodb_table'],
      'Item' => array(
        'cid'      => array('S' => $cid),
        'bin'    => array('S' => $this->bin),
        'data'   => array('S' => $data),
        'expire' => array('S' => $expire),
      )
    ));

    var_dump($result);

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
