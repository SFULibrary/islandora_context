<?php
/**
 * @file
 * Context plugin that generates a message.
 *
 * Message is displayed at the bottom of an Islandora object's display.
 */

/**
 * Expose a message as a context reaction.
 */
class IslandoraContextReactionInsertText extends context_reaction {

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
        '#type' => 'textarea',
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
        $markup = array('#markup' => theme('islandora_context_reaction_inserted_message', array('message_text' => $message_text)));
      }
    }

    return $markup;
  }

}
