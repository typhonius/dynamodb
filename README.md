Requirements
------------
- The Amazon AWS SDK for PHP.

Installation
------------
- Download the [http://aws.amazon.com/sdkforphp/](AWS SDK for PHP) to a location the webserver is able to access.
- The default location is /path/to/dynamodb although this may be overridden by manually setting the $conf['dynamodb_sdk_path'] in settings.php.

If the SDK is downloaded to sites/all/libraries/aws, set the configuration variable thus:
    $conf['dynamodb_sdk_path'] = DRUPAL_ROOT . '/sites/all/libraries/aws';

Configuration
-------------
To connect to DynamoDB, take the access key, secret key and region name obtained from the AWS account and place them in the settings.php of the site.

    $conf['dynamodb_access_key'] = ACCESS_KEY;
    $conf['dynamodb_secret_key'] = SECRET_KEY;
    $conf['dynamodb_region_name'] = REGION_NAME;
