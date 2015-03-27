<?php
/**
 * @file
 * Context plugin that generates a message to be displayed at the top
 * of an Islandora object's display.
 */

/**
 * Expose a message as a context reaction.
 */
class IslandoraContextReactionInsertText extends context_reaction {

  /**
   * Grab the available themes and provide them as a reaction for context.
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
   * Return some markup wrapping a message.
   *
   * @return string $markup
   *   Markup that is appended to the render array for the object view.
   */
  public function execute() {
    $markup = '';
    foreach ($this->get_contexts() as $context) {
      if (isset($context->reactions['islandora_context_reaction_insert_text']['text_to_insert'])) {
        $message_text = '';
        $message_text = $context->reactions['islandora_context_reaction_insert_text']['text_to_insert'];
        $markup = array('#markup' => "<div class=\"islandora-metadata\">$message_text</div>");
      }
    }

    return $markup;
  }
}
