<?php
/**
 * @file
 * Context plugin that hides the "Details" metadata fieldset.
 */

/**
 * Hide the "Details" collapsible div fieldset.
 */
class IslandoraContextReactionHideMetadataDetails extends context_reaction {
  function options_form($context) {
    return array('hide_metadata_details' => array('#type' => 'value', '#value' => TRUE));
  }

  function options_form_submit($values) {
    return array('hide_metadata_details' => 1);
  }

  /**
   * Include the JavaScript that hides the metadata Details fieldset.
   */
  public function execute($object) {
    foreach ($this->get_contexts() as $context) {
      if ($context->reactions['islandora_context_reaction_hide_metadata_details']['hide_metadata_details']) {
        drupal_add_js(drupal_get_path('module', 'islandora_context') . '/js/hide_metadata_details.js', 'file');
      }
    }
  }

}
