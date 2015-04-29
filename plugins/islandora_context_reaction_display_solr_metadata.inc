<?php
/**
 * @file
 * Context plugin that generates a message to be displayed at the top
 * of an Islandora object's display.
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
    
    $form = array(
      '#title' => t('Text to insert'),

      'text_to_insert' => array(
        '#title' => t('Text to insert'),
        '#description' => t('Enter some text to insert when this reaction is active.'),
        '#type' => 'textfield',
        '#default_value' => isset($settings['text_to_insert']) ? $settings['text_to_insert'] : '',
      ),
    );
    return $form;
  }
  // @codingStandardsIgnoreEnd

  /**
   * @todo: template_preprocess_islandora_solr_metadata_display() won't work
   * as it currently exists, since it gets is associations be calling islandora_solr_metadata_get_associations_by_cmodels($object->models).
   * We'll need to open a feature ticket to let us pass in associations in the call to theme(), below. We'll define the
   * associations in the options form, above.
   */
  public function execute($object) {
    foreach ($this->get_contexts() as $context) {
      // if (isset($context->reactions['islandora_context_reaction_display_solr_metadata']['text_to_insert'])) {
      if (TRUE) {
        $elements = array(
          'islandora_object' => $object,
          // 'associations' => array(foo, bar),
          'print' => FALSE,
        );
        return theme('islandora_solr_metadata_display', $elements);
      }
    }
  }
}
