<?php

/**
 * @file
 * Class file for islandora_context_condition_relationship plugin.
 */

/**
 * Islandora object's namespace as a condition.
 */
class IslandoraContextConditionRelationship extends context_condition {
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
      'islandora_relationship_predicate_uri' => array(
        '#type' => 'textfield',
        '#title' => t('Predicate URI'),
        '#description' => t('Enter the predicate URI of the relationship, e.g. info:fedora/fedora-system:def/model#.'),
        '#default_value' => isset($defaults['islandora_relationship_predicate_uri']) ?
          $defaults['islandora_relationship_predicate_uri'] : '',
      ),
      'islandora_relationship_predicate' => array(
        '#type' => 'textfield',
        '#title' => t('Predicate'),
        '#description' => t('Enter the predicate of the relationship, e.g., hasModel.'),
        '#default_value' => isset($defaults['islandora_relationship_predicate']) ?
          $defaults['islandora_relationship_predicate'] : '',
      ),
      'islandora_relationship_values' => array(
        '#type' => 'textarea',
        '#title' => t('Relationship values to activate this condition'),
        '#description' => t('Set this condition when one or more of the relationship values in this list applies to the objet. Enter a list of values (e.g., islandora:collectionCModel), one per line.'),
        '#default_value' => isset($defaults['islandora_relationship_values']) ?
          $defaults['islandora_relationship_values'] : '',
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
        $wanted_relationships = $this->fetch_from_context($context, 'options');
        $predicate_uri = trim($wanted_relationships['islandora_relationship_predicate_uri']);
        $predicate = trim($wanted_relationships['islandora_relationship_predicate']);
        $predicate_values = preg_split('/$\R?^/m', trim($wanted_relationships['islandora_relationship_values']));
        $predicate_values = array_map('trim', $predicate_values);
        $object_relationships = $islandora_object->relationships->get($predicate_uri, $predicate);
        // Loop through the object's relationships and see if any of them
        // are in the defined list.
        foreach ($object_relationships as $relationship) {
          if (($wanted_relationships['islandora_relationship_predicate_uri'] != '') &&
            ($wanted_relationships['islandora_relationship_predicate'] != '')) {
            if (in_array($relationship['object']['value'], $predicate_values)) {
              $this->condition_met($context);
            }
          }
        }
      }
    }
  }

}
