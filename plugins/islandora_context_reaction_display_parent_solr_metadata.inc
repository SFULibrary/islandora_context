<?php
/**
 * @file
 * Context plugin that loads an Islandora Solr Metadata display configuration.
 *
 * The resulting metadata applies to an object's parent, and is rendered below
 * the object's 'Details' div.
 */

/**
 * Expose a message as a context reaction.
 */
class IslandoraContextReactionDisplayParentSolrMetadata extends context_reaction {

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
   * Pass the Islandora Solr Metadata configuration to the theming function.
   */
  public function execute($object) {
    foreach ($this->get_contexts() as $context) {
      if (isset($context->reactions['islandora_context_reaction_display_solr_metadata']['solr_metadata_configuration'])) {
        $parent_info = islandora_compound_object_retrieve_compound_info($object);
        if (isset($parent_info['parent_pid'])) {
          $parent_object = islandora_object_load($parent_info['parent_pid']);
          $elements = array(
            'islandora_object' => $parent_object,
            'associations' => array(array('configuration_id' => $context->reactions['islandora_context_reaction_display_solr_metadata']['solr_metadata_configuration'])),
            'print' => FALSE,
          );
          $markup = theme('islandora_solr_metadata_display', $elements);
          // The label 'Details' is not themable. We probobably want to offer a reaction-specific
          // option for this label.
          $markup = preg_replace('|Details|' , 'Is part of', $markup);
          return $markup;
        }
        else {
          return '';
        }
      }
    }
  }

}
