<?php

/**
 * @file
 * Class file for islandora_context_condition_content_models.
 */

/**
 * Islandora object's namespace as a condition.
 */
class IslandoraContextConditionContentModels extends context_condition {
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
    $cmodels = islandora_context_get_cmodels();
    $values = $this->fetch_from_context($context);
    return array(
      'islandora_cmodels' => array(
        '#type' => 'checkboxes',
        '#options' => $cmodels,
        '#title' => t('Content models to activate this condition'),
        '#description' => t('Set this condition when viewing an Islandora object that one or more of these content models.'),
        '#default_value' => isset($values['options']['islandora_cmodels']) ?
          $values['options']['islandora_cmodels'] : array(),
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
        $cmodels = $this->fetch_from_context($context, 'options');
        // Convert the selected checkboxes into a simple array.
        $selected_cmodels = array_keys(array_filter($cmodels['islandora_cmodels']));
        $object_cmodels = $islandora_object->models;
        foreach ($object_cmodels as $object_cmodel) {
          if (in_array($object_cmodel, $selected_cmodels)) {
            $this->condition_met($context);
          }
        }
      }
    }
  }

}

/**
 * Query the resource index to get a list of all content model objects.
 *
 * @return array
 *   Associative array of pid => label pairs.
 */
function islandora_context_get_cmodels() {
  // Query the rindex to get all cmodels.
  $tuque = islandora_get_tuque_connection();
  $ri_query = 'PREFIX fedora-model: <info:fedora/fedora-system:def/model#>
select $object $label from <#ri>
     where { $object fedora-model:hasModel <info:fedora/fedora-system:ContentModel-3.0> ;
      fedora-model:label $label .}';
  $results = $tuque->repository->ri->sparqlQuery($ri_query, 'unlimited');
  $cmodels = array();
  foreach ($results as $member) {
    $pid = preg_replace('/info:fedora\//', '', $member['object']['value']);
    $label = $member['label']['value'];
    $cmodels[$pid] = $label;
  }
  return $cmodels;
}
