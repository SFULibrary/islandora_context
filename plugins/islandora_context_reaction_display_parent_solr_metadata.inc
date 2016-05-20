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
      '#title' => t('Label for parent metadata'),
      'parent_metadata_label' => array(
        '#title' => t('Label for parent metadata'),
        '#description' => t('Enter the label for the collapsible div containing the parent metadata.'),
        '#type' => 'textfield',
        '#default_value' => isset($settings['parent_metadata_label']) ? $settings['parent_metadata_label'] : 'Is part of',
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
      // This reaction is used in conjuction with a Solr metadata display configuration.
      if (isset($context->reactions['islandora_context_reaction_display_solr_metadata']['solr_metadata_configuration'])) {
        $label = $context->reactions['islandora_context_reaction_display_parent_solr_metadata']['parent_metadata_label'];
        $parent_info = islandora_compound_object_retrieve_compound_info($object);
        if (isset($parent_info['parent_pid'])) {
          $parent_object = islandora_object_load($parent_info['parent_pid']);
          $elements = array(
            'islandora_object' => $parent_object,
            'associations' => array(array('configuration_id' => $context->reactions['islandora_context_reaction_display_solr_metadata']['solr_metadata_configuration'])),
            'print' => FALSE,
          );
          $markup = theme('islandora_solr_metadata_display', $elements);
          // The label 'Details' is not themable so we search 'n replace in the themed HTML!
          $markup = preg_replace('|Details|' , $label, $markup);
          return $markup;
        }
        else {
          return '';
        }
      }
    }
  }

}
