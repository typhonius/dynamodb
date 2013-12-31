<?php

/**
 * @file
 * Include file to define cache methods for DynamoDB integration.
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

    // Check to see if we have a result before attempting to gzuncompress or
    // PHP will error out.
    if ($data = $result['Item']['data']['B']) {
      $cache = new stdClass();

      // AWS runs a base64_encode on any binary type data stored in DynamoDB.
      // Because of this, a base64_decode is required first on data retrieved
      // from DynamoDB.
      $cache->data = unserialize(gzuncompress(base64_decode($data)));
      $cache->expire = $result['Item']['expire']['N'];
      $cache->cid = $cid;
      $cache->bin = $this->bin;

      return $cache;
    }

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

    // Since DynamoDB has a max item size of 64k, we must compress the data to
    // be cached in order to store it.
    $data = gzcompress(serialize($data));

    $result = $this->dynamo->putItem(array(
      'TableName' => $conf['dynamodb_table'],
      'Item' => array(
        'cid'      => array('S' => $cid),
        'bin'    => array('S' => $this->bin),
        'data'   => array('B' => $data),
        'expire' => array('N' => $expire),
      ),
    ));

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
