<?php
/**
 * @file
 * Context plugin that hides the "In collections" markup in an object's metadata display.
 */

/**
 * Hide the "In collections" markup.
 */
class IslandoraContextReactionHideInCollections extends context_reaction {
  function options_form($context) {
    return array('hide_in_collections' => array('#type' => 'value', '#value' => TRUE));
  }

  function options_form_submit($values) {
    return array('hide_in_collections' => 1);
  }

  /**
   * Include the JavaScript that hides the description markup.
   */
  public function execute($object) {
    foreach ($this->get_contexts() as $context) {
      if ($context->reactions['islandora_context_reaction_hide_in_collections']['hide_in_collections']) {
        drupal_add_js(drupal_get_path('module', 'islandora_context') . '/js/hide_in_collections.js', 'file');
      }
    }
  }

}
