<?php

/**
 * @file
 * Class file for islandora_context_condition_rdf_requested plugin.
 */

/**
 * Request for application/rdf+xml as a condition.
 */
class IslandoraContextConditionRdfRequested extends context_condition {
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
  public function execute() {
    if ($this->condition_used()) {
      foreach ($this->get_contexts() as $context) {
        // Detect whether the client has requested RDF.
        $request_headers = getallheaders();
        if (isset($request_headers['Accept']) && $request_headers['Accept'] == 'application/rdf+xml') {
          $this->condition_met($context);
        }
      }
    }
  }

}
