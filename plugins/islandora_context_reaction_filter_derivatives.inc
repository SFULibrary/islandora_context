<?php
/**
 * @file
 * Context plugin that determines which Islandora derivatives to generate.
 */

/**
 * Filter which derivatives to generate.
 */
class IslandoraContextReactionFilterDerivatives extends context_reaction {

  /**
   * Allow the user to define DSIDs for derivatives.
   *
   * @param string $context
   *   The context as passed from context module.
   *
   * @return array
   *   The FAPI array as read by context module.
   */
  // @codingStandardsIgnoreStart
  function options_form($context) {
    $settings = $this->fetch_from_context($context);
    $form = array(
     'islandora_derivative_action' => array(
        '#type' => 'radios',
        '#options' => array(
          'include' => t('Generate only these derivatives'),
          'exclude' => t('Do not generate these derivatives'),
        ),
        '#title' => t('Action'),
        '#description' => t('Whether to generate or not generate the list of derivatives below.'),
        '#default_value' => isset($settings['islandora_derivative_action']) ?
          $settings['islandora_derivative_action'] : 'include',
      ),
      'islandora_derivative_dsids' => array(
        '#type' => 'textfield',
        '#size' => 60,
        '#title' => t('Derivatives'),
        '#description' => t('Comma-separated list of datastream IDs of the derivatives to generate or not generate. Note that this plugin does not check whether a datastream is required or optional for specific content models.'),
        '#default_value' => isset($settings['islandora_derivative_dsids']) ?
          $settings['islandora_derivative_dsids'] : '',
      ),
    );
    return $form;
  }
  // @codingStandardsIgnoreEnd

  /**
   * Assemble the configuration data for this context for use in islandora_context_islandora_derivative_alter().
   *
   * @return array
   *   Associative array with two keys, 'action' and 'dsids'.
   *     -'action' is either 'include' or 'exclude'.
   *     -'dsids' is an array of DSIDs corresponding to the derivatives. 
   */
  public function execute() {
    $return = array();
    $dsids = array();
    foreach ($this->get_contexts() as $context) {
      if (isset($context->reactions['islandora_context_reaction_filter_derivatives']['islandora_derivative_dsids'])) {
        $dsids = explode(',', $context->reactions['islandora_context_reaction_filter_derivatives']['islandora_derivative_dsids']);
        foreach ($dsids as &$dsid) {
          $dsid = trim($dsid);
        }
        $action = $context->reactions['islandora_context_reaction_filter_derivatives']['islandora_derivative_action'];
        $return = array('action' => $action, 'dsids' => $dsids);
      }
    }
    return $return;
  }

}
