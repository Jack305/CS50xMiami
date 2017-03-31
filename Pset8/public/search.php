<?php

    require(__DIR__ . "/../includes/config.php");

    // numerically indexed array of places
    $places = CS50::query("
        SELECT * FROM places WHERE postal_code LIKE '{$_GET["geo"]}%' 
        Union
        SELECT * FROM places WHERE place_name LIKE '{$_GET["geo"]}%'
        Union
        SELECT * FROM places WHERE admin_code1 LIKE '{$_GET["geo"]}%'");

    // output places as JSON (pretty-printed for debugging convenience)
    header("Content-type: application/json");
    print(json_encode($places, JSON_PRETTY_PRINT));

?>