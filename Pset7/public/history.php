<?php

    // configuration
    require("../includes/config.php"); 

    // getting users ID
    $id = $_SESSION["id"];
    
    // getting data from portfolios table 
    $h_rows = CS50::query("SELECT * FROM history WHERE user_id = $id");
    // getting the remaining amount of cash
    
    $h_positions = [];
    foreach ($h_rows as $h_row)
    {
        $h_positions[] = [
            "action" => $h_row["action"],
            "date" => $h_row["date"],
            "price" => $h_row["price"],
            "shares" => $h_row["shares"],
            "symbol" => $h_row["symbol"]
        ];
    }
    
    // render history
    render("history.php", ["position" => $h_positions, "title" => "HISTORY"]);
?>