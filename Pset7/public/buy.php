<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("buy_form.php", ["title" => "BUY"]);
    }
    
    // else if user reached page via POST (as by submitting a form via POST)
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        $stock = lookup($_POST["symbol"]);
        if ($stock == false)
        {
            // if stock name isn't not found
            apologize("Please try again! Make sure you are providing a correct symbol.");
        }
        else if (!preg_match("/^\d+$/", $_POST["shares"]) || preg_match("/^\d+$/", $_POST["shares"]) == 0)
        {
            // if input is not a positive int
            apologize("The number of shares has to be a positive integer.");
        }
        else
        {
            // cash check
            $cash = CS50::query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
            $newcash = $cash[0]["cash"] - ($stock["price"] * $_POST["shares"]);
            
            // checks if user has enough money to buy shares
            if ($newcash < 0)
            {
                apologize("You don't have enough money to buy this shares. Try to lower the amount.");    
            }
            
            // makes all letters uppercase
            $_POST["symbol"] = strtoupper($_POST["symbol"]);
            
            // add to history table
            CS50::query("INSERT INTO history (user_id, symbol, shares, price, action) VALUES (?, ?, ?, ?, 'BUY')", 
            $_SESSION["id"], $_POST["symbol"], $_POST["shares"], $stock["price"]);
            
            // insert selected shares
            CS50::query("INSERT INTO portfolios (user_id, symbol, shares) VALUES (?, ?, ?) ON DUPLICATE KEY UPDATE shares = shares + VALUES (shares)", 
            $_SESSION["id"], $_POST["symbol"], $_POST["shares"]);
            
            // updates cash value in users
            CS50::query("UPDATE users SET cash = ? WHERE id = ?", $newcash, $_SESSION["id"]);
            
            // redirects to main page - portfolios
            redirect("/index.php");
        }
    }    
?>