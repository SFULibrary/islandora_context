<?php
/**
 * @file
 * Context plugin that retrieves a rendered viewer.
 */

/**
 * Expose a message as a context reaction.
 */
class IslandoraContextReactionUseViewer extends context_reaction {

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
    $viewers = $this->get_viewers();
    $form = array(
      '#title' => t('Islandora Viewers'),
      'islandora_viewer' => array(
        '#title' => t('Islandora Viewers'),
        '#description' => t('Choose the name of the viewer to use when reaction is active.'),
        '#type' => 'select',
        '#options' => $viewers,
        '#default_value' => isset($settings['islandora_viewer']) ? $settings['islandora_viewer'] : '',
      ),
    );
    return $form;
  }
  // @codingStandardsIgnoreEnd

  /**
   * Pass the rendered viewer output to the theme preprocess function.
   */
  public function execute($object) {
    foreach ($this->get_contexts() as $context) {
      if ($context->reactions['islandora_context_reaction_use_viewer']['islandora_viewer']) {
        module_load_include('inc', 'islandora', 'includes/solution_packs');
        $viewer_id = $context->reactions['islandora_context_reaction_use_viewer']['islandora_viewer'];
        $callback = islandora_get_viewer_callback($viewer_id);
        if (function_exists($callback)) {
          $params = array();
          return $callback($params, $object);
        }
      }
    }
  }

  /**
   * Get a list of all registered viewers.
   *
   * @return array
   *   An associative array of viewer IDs as keys and labels as values.
   */
  private function get_viewers() {
    $defined_viewers = module_invoke_all('islandora_viewer_info');
    $viewers = array();
    foreach ($defined_viewers as $key => $value) {
      $viewers[$key] = $value['label'];
    }
    return $viewers;
  }

}
