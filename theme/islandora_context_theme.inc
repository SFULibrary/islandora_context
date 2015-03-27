<?php

/**
 * @file
 * Theming functions for Islandora Context.
 */

/**
 * Preprocessor for theme('islandora_context_reaction_inserted_message').
 */
function template_preprocess_islandora_context_reaction_inserted_message(&$vars) {
  $vars['message_text'] = check_plain($vars['message_text']);
}
