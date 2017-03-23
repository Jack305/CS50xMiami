<?php

    // configuration
    require("../includes/config.php");

    // getting data from portfolios table 
    $sells = CS50::query("SELECT * FROM portfolios WHERE user_id = ?", $_SESSION["id"]);
    
    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        if (empty($sells))
        {
             apologize("There is nothing to sell. You have to buy stocks first.");
        }
        // else render form
        render("sell_form.php", ["title" => "Quote", "sells" => $sells]);
    }
    
    // else if user reached page via POST (as by submitting a form via POST)
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        if (empty($_POST["symbol"]))
        {
            // if stock name isn't not found
            apologize("You have to select one of the symbols or visit other pages!");
        }
            // checks for current price for symbol
            $stock = lookup($_POST["symbol"]);

            // amount of shares per type
            $shares = CS50::query("SELECT shares FROM portfolios WHERE user_id = ? AND symbol = ?", 
            $_SESSION["id"], $_POST["symbol"]);
            
            // add to history table
            CS50::query("INSERT INTO history (user_id, symbol, shares, price, action) VALUES (?, ?, ?, ?, 'SELL')", 
            $_SESSION["id"], $_POST["symbol"], $shares[0]["shares"], $stock["price"]);
            
            // delete selected shares
            CS50::query("DELETE FROM portfolios WHERE user_id = ? AND symbol = ?", $_SESSION["id"], $_POST["symbol"]);
            
            // updates cash value in users
            $newcash = $stock["price"] * $shares[0]["shares"];
            CS50::query("UPDATE users SET cash = cash + ? WHERE id = ?", $newcash, $_SESSION["id"]);
            
            // redirects to main page - portfolios
            redirect("/index.php");
    }
?>