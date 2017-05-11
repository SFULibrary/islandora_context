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
    $collections = islandora_context_get_collections();
    $values = $this->fetch_from_context($context);
    return array(
      'islandora_collection_membership' => array(
        '#type' => 'checkboxes',
        '#options' => $collections,
        '#title' => t('Collections to activate this condition'),
        '#description' => t('Set this condition when viewing an Islandora object that is a member of one or more of these collections.'),
        '#default_value' => isset($values['options']['islandora_collection_membership']) ?
          $values['options']['islandora_collection_membership'] : array(),
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
        // Convert the selected checkboxes into a simple array.
        $selected_collections = array_keys(array_filter($collections['islandora_collection_membership']));
        $object_collections = $islandora_object->relationships->get(FEDORA_RELS_EXT_URI, 'isMemberOfCollection');
        foreach ($object_collections as $object_collection) {
          if (in_array($object_collection['object']['value'], $selected_collections)) {
            $this->condition_met($context);
          }
        }
      }
    }
  }

}

/**
 * Query the resource index to get a list of collections.
 *
 * @return array
 *   Associative array of pid => label pairs.
 */
function islandora_context_get_collections() {
  // Query the rindex to get all collections.
  $tuque = islandora_get_tuque_connection();
  $ri_query = 'PREFIX fedora-model: <info:fedora/fedora-system:def/model#>
select $object $label from <#ri>
     where  { $object fedora-model:hasModel <info:fedora/islandora:collectionCModel> ;
      fedora-model:label $label . }
order by ($label)';
  $results = $tuque->repository->ri->sparqlQuery($ri_query, 'unlimited');
  $collections = array();
  foreach ($results as $member) {
    $pid = preg_replace('/info:fedora\//', '', $member['object']['value']);
    $label = $member['label']['value'];
    // We don't want the root collection.
    if ($pid != 'islandora:root') {
      $collections[$pid] = $label . ' (' . $pid . ')';
    }
  }
  return $collections;
}
