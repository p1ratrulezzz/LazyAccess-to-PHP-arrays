<?php
/*
 * @file
 */

/*
 * Lazy access to the elements in array
 * @todo Provide possibility of using nested objects as well as arrays
 * @todo Provide methods for type conversion (C# style: asString(), asInteger(), asFloat() and etc)
 * @todo Fix ->raw() method for properly getting raw data
 * @todo Lazy setters?
 * @todo Implement setters
 * @todo Auto type conversions on getting values according to the $defaults array
 */
class LazyAccess implements Iterator, ArrayAccess {
  protected $_values = array();
  protected $_defaults = array();
  protected $_current_key = NULL;

  public function __construct(&$values, $defaults = array()) {
    $this->_values = &$values;
    $this->_defaults = $defaults;

    reset($this->_values);
    $this->__setKey();
  }

  public function __isset($key) {
    return isset($this->_values[$key]);
  }

  public function __get($key) {
    if (!empty($this->_values) && !is_array($this->_values)) {
      return $this->normalizeValues($this->_values);
    }
    elseif (!isset($this->_values[$key]) && isset($this->_defaults[$key])) {
      $this->_values[$key] = $this->_defaults[$key];
    }
    elseif (!isset($this->_values[$key])) {
      //return NULL;
      $empty = array();
      return $this->normalizeValues($empty);
    }

    return $this->normalizeValues($this->_values[$key]);
  }

  public function raw() {
    return $this->_values;
  }

  public function value($default = NULL) {
    $ret = $this->getNormalValOrNull() or $ret = $default;
    return $ret;
  }

  public function getValue($default = NULL) {
    if (!isset($this->_values)) {
      return $default;
    }

    return $this->_values;
  }

  protected function normalizeValues($values) {
    if (!is_array($values)) { //} && !is_object($values)) {
      return $values;
    }

    return new LazyAccess($values);
  }

  protected function __setKey() {
    $this->_current_key = key($this->_values);
  }

  public function __toString() {
    if (is_array($this->_values)) {
      return 'Array';
    }
    elseif (is_object($this->_values)) {
      return 'Object';
    }

    return (string) $this->_values;
  }

  public function __set($key, $value) {
    $this->_values[$key] = $value;
  }

  public function current() {
    return $this->{$this->_current_key};
  }

  public function key() {
    return $this->_current_key;
  }

  public function next() {
    next($this->_values);
    $this->__setKey();
  }

  public function rewind() {
    reset($this->_values);
    $this->__setKey();
  }

  public function valid() {
    return $this->_current_key ? TRUE : FALSE;
  }

  //Array Access
  public function offsetExists($offset) {
    return $this->__isset($offset);
  }

  public function offsetGet($offset) {
    return $this->{$offset};
  }

  public function offsetSet($offset, $value) {
    throw new Exception('Not implemented yet!');
  }

  public function offsetUnset($offset) {
    throw new Exception('Not implemented yet!');
  }


  protected function getNormalValOrNull($default = NULL) {
    $ret = $this->normalizeValues($this->_values);

    if ($ret->isEmpty() || is_array($ret->_values) || is_object($ret->_values)) {
      return $default;
    }

    return $ret->_values;
  }

  public function isEmpty() {
    return empty($this->_values);
  }


  //public function __clone() {}
}

class LazyAccessTyped extends LazyAccess {

  /**
   * Overrides LazyAccess::normalizeValues()
   * Always get an instance of LazyAccessTyped
   * @param $values
   * @return LazyAccess
   */
  protected function normalizeValues(&$values) {
    return new LazyAccessTyped($values);
  }

  public function value($default = NULL) {
    $ret = $this->getNormalValOrNull();
    if ($ret === NULL) {
      return $default;
    }

    return $ret;
  }

  public function asInteger($default = NULL) {
    $ret = $this->getNormalValOrNull();
    if ($ret === NULL) {
      return $default;
    }

    return intval($ret);
  }

  public function asDouble($default = NULL) {
    $ret = $this->getNormalValOrNull();
    if ($ret === NULL) {
      return $default;
    }

    $ret = str_replace(array(',', ' '), array('.', ''), $ret);
    return doubleval($ret);
  }

  public function asFloat($default = NULL) {
    $ret = $this->getNormalValOrNull();
    if ($ret === NULL) {
      return $default;
    }

    $ret = str_replace(array(',', ' '), array('.', ''), $ret);
    return floatval($ret);
  }

  public function asString($default = NULL) {
    $ret = $this->getNormalValOrNull();
    if ($ret === NULL) {
      return $default;
    }

    return $ret;
  }
}

/**
 * @todo Magic storage to provide storing objects
 * @todo
 * @todo
 */
abstract class MagicStorage {
  protected $storage = NULL;
  public function __construct(&$values) {
    $this->storage = &$values;
  }

  function exists() {

  }
}

interface MagicStorageAdapterInterface {
  public function exists();
  public function get();
  //public function getStorage();
  //public function set();
}

abstract class MagicStorageAdapterAbstract implements MagicStorageAdapterInterface {
  protected $storage = array();
  protected $storage_key = 'default';
  protected function &getStorage() {
    return $this->storage[$this->storage_key];
  }

  protected function setStorage(&$values) {

    $this->storage[$this->storage_key] = &$values;
  }

  protected function defineStorageKey(&$values) {
    $this->storage_key = 'default';
    if (is_array($values)) {
      $this->storage_key = 'array';
    }elseif (is_object($values)) {
      $this->storage_key = 'object';
    }
  }
}

class MagicStorage_array extends MagicStorageAdapterAbstract {
  public function exists() {

  }
  public function get() {

  }

  protected function getStorage() {

  }
}

/*class MagicStorage_object implements MagicStorageAdapterInterface {

}*/
