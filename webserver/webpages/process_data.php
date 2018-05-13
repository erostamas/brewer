<?xml version="1.0"?>
<processdata>
<?php
require "predis/autoload.php";
Predis\Autoloader::register();

try {
	$redis = new Predis\Client();

	$process_data = $redis->hgetall('brewer_process_data');
    foreach ($process_data as $key => $value)
        echo "<$key>$value</$key>";
}
catch (Exception $e) {
	die($e->getMessage());
}
?>
</processdata>