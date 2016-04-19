<?php
/**
 * P1ratRuleZZZ\Tools\LazyAccessTyped class
 */

namespace P1ratRuleZZZ\Tools;

/**
 * Provides some type conversion methods like
 *  asString()
 *  asFloat()
 *  asDouble()
 *  asInteger()
 *  value() -- actually gets raw value
 *
 */
class LazyAccessTyped extends LazyAccess {

  /**
   * Overrides LazyAccess::normalizeValues()
   * Always get an instance of LazyAccessTyped
   * @param $values
   * 	an array reference with data to wrap
   * @return LazyAccessTyped
   */
  protected function normalizeValues(&$values) {
    return new LazyAccessTyped($values);
  }

  /*
   * Gets raw value or default
   * @todo value() should convert type according to defaults array
   */
  public function value($default = NULL) {
    $ret = $this->getNormalValOrNull($default, FALSE);
    if ($ret === NULL) {
      return $default;
    }

    return $ret;
  }

  /**
   * Gets and integer value
   * @param mixed $default
   * @return int|null
   */
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

  public function __toString() {
    return (string) $this->asString('');
  }
}

