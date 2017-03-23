<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("add_form.php", ["title" => "Register"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        if (empty($_POST["funds"]))
        {
            apologize("You must provide the amount of money you would like to add or visit other pages!");
        }
        else if (!preg_match("/^\d+$/", $_POST["funds"]) || preg_match("/^\d+$/", $_POST["funds"]) < 1)
        {
            // if input is not a positive int
            apologize("The number of shares has to be a positive integer.");
        }
 
        // checks if new user can be created in the database
        if (CS50::query("UPDATE users SET cash = cash + ? WHERE id = ?", 
            $_POST["funds"], $_SESSION["id"]) != 0)
    	{
    		// prints if successful
    		congrats('Your funds were successfully added!');
    	}
    	else
    	{
    		// prints if couldn't change
    		apologize('SOMETHING WENT WRONG. Please try again!');
    	}
    	
    	// redirects to index page
        redirect("index.php");
    }
?>