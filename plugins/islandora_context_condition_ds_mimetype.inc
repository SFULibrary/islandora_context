<?php

/**
 * @file
 * Class file for islandora_context_condition_ds_mimetype.
 */

/**
 * Datastream Mime Type as a condition.
 */
class IslandoraContextConditionDsMimetype extends context_condition {
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
      'islandora_ds_mimetype_dsid' => array(
        '#type' => 'textfield',
        '#size' => 20,
        '#title' => t('Datastream ID'),
        '#description' => t('Enter the ID of the datastream that should trigger this condition.'),
        '#default_value' => isset($defaults['islandora_ds_mimetype_dsid']) ?
          $defaults['islandora_ds_mimetype_dsid'] : '',
      ),
      'islandora_ds_mimetype_mimetypes' => array(
        '#type' => 'textarea',
        '#title' => t('Mimetypes to activate this condition'),
        '#description' => t('Set this condition when the datastream has one of the mime types in this list. Enter a list of mime types, one per line.'),
        '#default_value' => isset($defaults['islandora_ds_mimetype_mimetypes']) ?
          $defaults['islandora_ds_mimetype_mimetypes'] : '',
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
        $config = $this->fetch_from_context($context, 'options');
        $dsid = trim($config['islandora_ds_mimetype_dsid']);
        $mimetypes = preg_split("/\\r\\n|\\r|\\n/", $config['islandora_ds_mimetype_mimetypes']);
        foreach ($mimetypes as &$mimetype) {
          $mimetype = trim($mimetype);
        }
        if ($islandora_object[$dsid]) {
          if (in_array($islandora_object[$dsid]->mimetype, $mimetypes)) {
              $this->condition_met($context);
          }
        }
      }
    }
  }

}
