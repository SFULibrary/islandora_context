<?php

/**
 * @file
 * Class file for islandora_context_condition_keyword_in_datastream.
 */

/**
 * Presence of keywords in a datastream as a condition.
 */
class IslandoraContextConditionKeywordInDatastream extends context_condition {
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
      'islandora_keywords_in_datastream_dsid' => array(
        '#type' => 'textfield',
        '#size' => 20,
        '#title' => t('Datastream to search'),
        '#description' => t('Enter the ID of the datastream to search. The search only works on text or XML datastreams.'),
        '#default_value' => isset($defaults['islandora_keywords_in_datastream_dsid']) ?
          $defaults['islandora_keywords_in_datastream_dsid'] : '',
      ),
      'islandora_keywords_in_datastream' => array(
        '#type' => 'textarea',
        '#title' => t('Keywords to activate this condition'),
        '#description' => t('Set this condition when one or more of the keywords in this list is present in the designated datastream. Enter a list of keywords, separated by spaces. Search is case-insensitive.'),
        '#default_value' => isset($defaults['islandora_keywords_in_datastream']) ?
          $defaults['islandora_keywords_in_datastream'] : '',
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
        $keyword_string = preg_replace('/\s+/', '|', $config['islandora_keywords_in_datastream']);
        $dsid = trim($config['islandora_keywords_in_datastream_dsid']);
        $allowed_mimetypes = array('text/plain', 'text/xml');
        if ($islandora_object[$dsid]) {
          if (in_array($islandora_object[$dsid]->mimetype, $allowed_mimetypes)) {
            if (preg_match("/$keyword_string/is", $islandora_object[$dsid]->content)) {
              $this->condition_met($context);
            }
          }
        }
      }
    }
  }

}
