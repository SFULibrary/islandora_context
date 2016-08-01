<?php

/**
 * @file
 * Class file for islandora_context_condition_collection_member.
 */

/**
 * Islandora object's namespace as a condition.
 */
class IslandoraContextConditionIsIslandoraObject extends context_condition {
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
   * Override of options_form().
   */
  // @codingStandardsIgnoreStart
  public function options_form($context) {
    $values = $this->fetch_from_context($context);
    return array(
      'islandora_is_islandora_object_types' => array(
        '#type' => 'radios',
        '#options' => array(
          'collection' => t('Collection objects'),
          'noncollection' => t('Non-collection objects'),
          'both' => t('Both'),
        ),
        '#title' => t('Object types'),
        '#description' => t('Object types to include.'),
        '#default_value' => isset($values['options']['islandora_is_islandora_object_types']) ?
          $values['options']['islandora_is_islandora_object_types'] : 'both',
      ),
    );
  }
  // @codingStandardsIgnoreEnd

  /**
   * Override of execute().
   */
  public function execute($islandora_object) {
    if ($this->condition_used()) {
      foreach ($this->get_contexts() as $context) {
        $values = $this->fetch_from_context($context);
        // For all objects.
        if  ($values['options']['islandora_is_islandora_object_types'] == 'both') {
          if (is_object($islandora_object) && property_exists($islandora_object, 'id')) {
            $this->condition_met($context);
          }
        }
        // For collection objects.
        if  ($values['options']['islandora_is_islandora_object_types'] == 'collection') {
          $cmodels = $islandora_object->relationships->get('info:fedora/fedora-system:def/model#', 'hasModel');
          $islandora_object_cmodels = array();
          foreach ($cmodels as $cmodel) {
            $islandora_object_cmodels[] = $cmodel['object']['value'];
          }
          if (is_object($islandora_object) && property_exists($islandora_object, 'id')) {
            if (in_array('islandora:collectionCModel', $islandora_object_cmodels)) {
              $this->condition_met($context);
            }
          }
        }
        // For non-collection objects.
        if ($values['options']['islandora_is_islandora_object_types'] == 'noncollection') {
          $cmodels = $islandora_object->relationships->get('info:fedora/fedora-system:def/model#', 'hasModel');
          $islandora_object_cmodels = array();
          foreach ($cmodels as $cmodel) {
            $islandora_object_cmodels[] = $cmodel['object']['value'];
          }
          if (is_object($islandora_object) && property_exists($islandora_object, 'id')) {
            if (!in_array('islandora:collectionCModel', $islandora_object_cmodels)) {
              $this->condition_met($context);
            }
          }
        }
      }
    }
  }

}
