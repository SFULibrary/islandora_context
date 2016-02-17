<?php

/**
 * @file
 * Class file for islandora_context_condition_namespace.
 */

/**
 * Islandora object's namespace as a condition.
 */
class IslandoraContextConditionNamespace extends context_condition {
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
    $defaults = $this->fetch_from_context($context, 'options');
    return array(
      'islandora_namespaces' => array(
        '#type' => 'textarea',
        '#title' => t('PID namespaces to activate this condition'),
        '#description' => t('Set this condition when viewing an Islandora object whose PID namespace is in this list. Enter a list of PID namespaces, separated by spaces (end each one with a colon).'),
        '#default_value' => isset($defaults['islandora_namespaces']) ? $defaults['islandora_namespaces'] : '',
      ),
    );
  }
  // @codingStandardsIgnoreEnd

  /**
   * Override of execute().
   */
  public function execute($pid) {
    if ($this->condition_used()) {
      foreach ($this->get_contexts() as $context) {
        $namespaces = $this->fetch_from_context($context, 'options');
        $namespace_list = explode(' ', trim($namespaces['islandora_namespaces']));
        $object_namespace = preg_replace('/:.*$/', '', $pid);
        if (in_array($object_namespace . ':', $namespace_list)) {
          $this->condition_met($context);
        }
      }
    }
  }

}
