<?php
/**
 * @file
 * Context plugin that loads an Islandora Solr Metadata display configuration.
 *
 * Must be used in conjunction with an Islandora Solr Metadtata configuration.
 */

/**
 * Expose an Islandora Solr Metadata description as a context reaction.
 */
class IslandoraContextReactionDisplaySolrMetadataDescription extends context_reaction {

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
    $form = array(
      'solr_metadata_configuration' => array(
        '#type' => 'value',
        '#value' => isset($settings['solr_metadata_configuration']) ? $settings['solr_metadata_configuration'] : '',
      ),
    );

    return $form;
  }
  // @codingStandardsIgnoreEnd



  /**
   * Pass the Islandora Solr Metadata configuration to the description theming function.
   */
  public function execute($object) {
    foreach ($this->get_contexts() as $context) {
      if (isset($context->reactions['islandora_context_reaction_display_solr_metadata']['solr_metadata_configuration'])) {
        $elements = array(
          'islandora_object' => $object,
          'associations' => array(array('configuration_id' => $context->reactions['islandora_context_reaction_display_solr_metadata']['solr_metadata_configuration'])),
        );
        drupal_alter('islandora_solr_metadata_description_elements', $elements);
        if (count($elements['associations']) > 0) {
          return theme('islandora_solr_metadata_description', $elements);
        }
      }
    }
  }

}
