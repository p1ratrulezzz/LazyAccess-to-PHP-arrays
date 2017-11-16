LazyAccess
==========

LazyAccess is a wrapper around any arrays. Provides easy way of getting it's values or get a default value instead.

Replaces stupid long constructions like 

    isset($var) ? $var : NULL.
    
# Installation

## Using composer

Update your composer.json with following:

    "repositories": [
        {
            "type": "git",
            "url": "https://github.com/p1ratrulezzz/LazyAccess-to-PHP-arrays.git"
        }
    ],
    require: [
        "p1ratrulezzz/lazyaccess": "master"
    ]

and run 

    composer install  
or (recommended)

    composer require p1ratrulezzz/lazyaccess master

Second method will allow you to install this package without manual changes in composer.lock file.

## Manual installation

    git clone --branch master https://github.com/p1ratrulezzz/LazyAccess-to-PHP-arrays.git lazyaccess
    
Then in PHP code include the files

    require_once 'lazyaccess/src/LazyAccess.php';
    require_once 'lazyaccess/src/LazyAccessTyped.php';

# Description

For example:
  usual PHP code is 

     $somevar = isset($array[$key]['key2'][0]) ? $array[$key]['key2'][0] : 'some_default_value';

This code is long and duplicates same things. 
With LazyAccess same code will be
  
    $wrapper = new LazyAccessTyped($array); //Define it once somewhere in your code
    $somevar = $array[$key]->key2[0]->value('some_default_value');
    //or
    $somevar = $array[$key]['key2'][0]->value('some_default_value'); //the same as the above
    //or
    $somevar = $array->$key->key2->0->value('some_default_value'); //the same as the above
    // Also there are some wrappers with types: asString(), asInteger(), asDouble()
    $somevar $array->{$key}->key2->0->asString('some_default_value');
    $somevar $array->{$key}->key2->0->asInteger(0); // It will perform intval() operation before returning, so you can be sure that there will be an integer value.
    
It provides ability to use array operator ("[]") or object operator ("->") to access nesting array elements!

# Note

There are two classes LazyAccess and LazyAccessTyped. LazyAccessTyped provides ability to use converters such as asFloat(), asInteger() and etc.

Please, do not use LazyAccess, cause it can behave unpredictible with it's return value. LazyAccessTyped is more better decision.
