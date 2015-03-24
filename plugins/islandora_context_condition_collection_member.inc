<?php

/**
 * @file
 * Class file for islandora_context_condition_collection_member.
 */

/**
 * Islandora object's namespace as a condition.
 */
class IslandoraContextConditionCollectionMember extends context_condition {
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
      'islandora_collection_membership' => array(
        '#type' => 'textarea',
        '#title' => t('Collection PIDs to activate this condition'),
        '#description' => t('A list of collection PIDs, one per line.'),
        '#default_value' => isset($defaults['islandora_collection_membership']) ?
          $defaults['islandora_collection_membership'] : '',
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
        $collections = $this->fetch_from_context($context, 'options');
        $collection_list = preg_split('/$\R?^/m', trim($collections['islandora_collection_membership']));
        $object_collections = $islandora_object->relationships->get(FEDORA_RELS_EXT_URI, 'isMemberOfCollection');
        foreach ($object_collections as $object_collection) {
          if (in_array($object_collection['object']['value'], $collection_list)) {
            $this->condition_met($context);
          }
        }
      }
    }
  }
}
