LazyAccess
==========

LazyAccess is a wrapper around any arrays. Provides easy way of getting it's values or get a default value instead.

Replaces stupid long constructions like 

    isset($var) ? $var : NULL.

#Description


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
It provides ability to use array operator ("[]") or object operator ("->") to access nesting array elements!

#Note

There are two classes LazyAccess and LazyAccessTyped. LazyAccessTyped provides ability to use converters such as asFloat(), asInteger() and etc.

Please, do not use LazyAccess, cause it can behave unpredictible with it's return value. LazyAccessTyped is more better decision.
