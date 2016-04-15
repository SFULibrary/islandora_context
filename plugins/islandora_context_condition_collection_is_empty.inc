<?php

/**
 * @file
 * Class file for islandora_context_condition_collection_is_empty.
 */

/**
 * Wheterh Islandora collection object is empty or not as a condition.
 */
class IslandoraContextConditionCollectionIsEmpty extends context_condition {
  /**
   * Override of condition_values().
   */
  // @codingStandardsIgnoreStart
  public function condition_values() {
    return array();
  }
  // @codingStandardsIgnoreEnd

  /**
   * Override of condition_form().
   */
  // @codingStandardsIgnoreStart
  public function condition_form($context) {
    $form = parent::condition_form($context);
    $form['#type'] = 'value';
    $form['#value'] = TRUE;
    return $form;
  }
  // @codingStandardsIgnoreEnd

  /**
   * Override of condition_form_submit().
   */
  // @codingStandardsIgnoreStart
  public function condition_form_submit($values) {
    return array($values);
  }
  // @codingStandardsIgnoreEnd

  /**
   * Override of execute().
   */
  public function execute($islandora_object) {
    if ($this->condition_used()) {
      foreach ($this->get_contexts() as $context) {
        $values = $this->fetch_from_context($context);
        $cmodels = $islandora_object->relationships->get('info:fedora/fedora-system:def/model#', 'hasModel');
        $islandora_object_cmodels = array();
        foreach ($cmodels as $cmodel) {
          $islandora_object_cmodels[] = $cmodel['object']['value'];
        }
        if (is_object($islandora_object) && property_exists($islandora_object, 'id')) {
          if (in_array('islandora:collectionCModel', $islandora_object_cmodels)) {
            list($count, $results) = islandora_basic_collection_get_member_objects($islandora_object);
            if ($count == 0) {
              $this->condition_met($context);
            }
          }
        }
      }
    }
  }

}
