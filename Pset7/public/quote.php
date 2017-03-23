<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("quote_form.php", ["title" => "Quote"]);
    }
    
    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        $stock = lookup($_POST["symbol"]);
        if ($stock == false)
        {
            // if stock name isn't not found
            apologize("The symbol you entered is not valid. Please try again!");
        }
        else 
        {
            // if quote is ready to be printed
            render("../views/quote.php", ["title" => "Quote", "stock" => $stock]);
        }
    }    
?>