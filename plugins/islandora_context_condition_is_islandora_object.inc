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
      'islandora_is_islandora_object' => array(
        '#type' => 'checkbox',
        '#title' => t('Apply to all Islandora objects'),
        '#description' => t('Set this condition when you want it to apply to all Islandora objects.'),
        '#default_value' => isset($values['options']['islandora_is_islandora_object']) ?
          $values['options']['islandora_is_islandora_object'] : FALSE,
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
        if ($values['options']['islandora_is_islandora_object']) {
          if (is_object($islandora_object) && property_exists($islandora_object, 'id')) {
            $this->condition_met($context);
          }
        }
      }
    }
  }
}
