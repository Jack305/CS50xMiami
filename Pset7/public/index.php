<?php

    // configuration
    require("../includes/config.php"); 

    // getting users ID
    $id = $_SESSION["id"];
    
    // getting data from portfolios table 
    $rows = CS50::query("SELECT * FROM portfolios WHERE user_id = $id");
    // getting the remaining amount of cash
    $cash = CS50::query("SELECT cash FROM users WHERE id = $id");
    // declaring variable to pass to render
    $positions = [];
    
    // iterates through the rows
    foreach ($rows as $row)
    {
        $stock = lookup($row["symbol"]);
        if ($stock !== false)
        {
            $positions[] = [
            "name" => $stock["name"],
            "price" => $stock["price"],
            "shares" => $row["shares"],
            "symbol" => $row["symbol"]
            ];
        }
    }
    
    // render portfolio
    render("portfolio.php", ["position" => $positions, "title" => "Portfolio", "cash" =>  $cash[0]["cash"]]);
?>
