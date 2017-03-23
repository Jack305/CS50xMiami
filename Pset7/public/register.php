<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("register_form.php", ["title" => "Register"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        if (empty($_POST["username"]) || empty($_POST["password"]))
        {
            apologize("You must provide your username and password!");
        }
        else if ($_POST["password"] != $_POST["confirmation"])
        {
            apologize("Your username and password have to be the same!");
        }
    }
    
    // checks if new user can be created in the database
    if (CS50::query("INSERT IGNORE INTO users (username, hash, cash) VALUES(?, ?, 10000.0000)", 
        $_POST["username"], password_hash($_POST["password"], PASSWORD_DEFAULT)) == 0)
	{
		// prints if there is an error 
		apologize('This username is not available. Please try to use another one.');
	}
	else
	{
		// insert new user into the database if it doesn't exist
		$rows = CS50::query("SELECT LAST_INSERT_ID() AS id");
        $id = $rows[0]["id"];
		$_SESSION["id"] = $id; 
		// redirects to index page
		redirect("index.php");
	}
?>