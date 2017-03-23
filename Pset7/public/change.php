<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("change_form.php", ["title" => "Register"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // if password wasn't provided
        if (empty($_POST["password"]))
        {
            apologize("You must provide your new password or visit other pages!");
        }
        // if password doesn't math the confirmation field
        else if ($_POST["password"] != $_POST["confirmation"])
        {
            apologize("Your New password and Confirmation have to be the same!");
        }
    }
 
    // checks if new user can be created in the database
    if (CS50::query("UPDATE users SET hash = ? WHERE id = ?", 
        password_hash($_POST["password"], PASSWORD_DEFAULT), $_SESSION["id"]) != 0)
	{
		// prints if successful
		congrats('Your password was successfully changed!');
	}
	else
	{
		// prints if couldn't change
		apologize('SOMETHING WENT WRONG. Please try again!');
	}
	
	// redirects to index page
    redirect("index.php");
?>