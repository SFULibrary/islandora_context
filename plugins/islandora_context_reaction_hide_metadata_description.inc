<?php
/**
 * @file
 * Context plugin that hides the "Description" markup in an object's metadata display.
 */

/**
 * Hide the "Description" markup.
 */
class IslandoraContextReactionHideMetadataDescription extends context_reaction {
  function options_form($context) {
    return array('hide_metadata_description' => array('#type' => 'value', '#value' => TRUE));
  }

  function options_form_submit($values) {
    return array('hide_metadata_description' => 1);
  }

  /**
   * Include the JavaScript that hides the description markup.
   */
  public function execute($object) {
    foreach ($this->get_contexts() as $context) {
      if ($context->reactions['islandora_context_reaction_hide_metadata_description']['hide_metadata_description']) {
        drupal_add_js(drupal_get_path('module', 'islandora_context') . '/js/hide_metadata_description.js', 'file');
      }
    }
  }

}
