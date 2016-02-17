<?php
/**
 * @file
 * Context plugin that loads an Islandora Solr Metadata display configuration.
 */

/**
 * Expose a message as a context reaction.
 */
class IslandoraContextReactionDisplaySolrMetadata extends context_reaction {

  /**
   * Allow the admin to define some text to display.
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
    module_load_include('inc', 'islandora_solr_metadata', 'includes/db');
    $solr_metadata_configurations = islandora_solr_metadata_get_associations();
    $display_configurations = array();
    foreach ($solr_metadata_configurations as $config) {
      $display_configurations[$config['id']] = $config['name'];
    }
    
    $form = array(
      '#title' => t('Solr Metadata Configuration'),
      'solr_metadata_configuration' => array(
        '#title' => t('Solr Metadata Configuration'),
        '#description' => t('Choose the name of the Solr metadata configuration to use when reaction is active.'),
        '#type' => 'select',
        '#options' => $display_configurations,
        '#default_value' => isset($settings['solr_metadata_configuration']) ? $settings['solr_metadata_configuration'] : '',
      ),
    );
    return $form;
  }
  // @codingStandardsIgnoreEnd

  /**
   * Pass the Islandora Solr Metadata configuration to the theming function.
   */
  public function execute($object) {
    foreach ($this->get_contexts() as $context) {
      if (isset($context->reactions['islandora_context_reaction_display_solr_metadata']['solr_metadata_configuration'])) {
        $elements = array(
          'islandora_object' => $object,
          'associations' => array(array('configuration_id' => $context->reactions['islandora_context_reaction_display_solr_metadata']['solr_metadata_configuration'])),
          'print' => FALSE,
        );
        return theme('islandora_solr_metadata_display', $elements);
      }
    }
  }

}
