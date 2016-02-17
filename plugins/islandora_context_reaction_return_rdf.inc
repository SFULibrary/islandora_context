<?php
/**
 * @file
 * Context plugin that generates an RDF representation of an Islandora object.
 */

/**
 * Return the RDF representation of an Islandora object as a reaction.
 */
class IslandoraContextReactionReturnRdf extends context_reaction {
  function options_form($context) {
    return array('return_rdf' => array('#type' => 'value', '#value' => TRUE));
  }

  function options_form_submit($values) {
    return array('return_rdf' => 1);
  }

  /**
   * Return the RELS-EXT datastream's content (until we can think of a
   * better RDF representation of an Islandora object).
   */
  public function execute($object) {
    foreach ($this->get_contexts() as $context) {
      if ($context->reactions['islandora_context_reaction_return_rdf']['return_rdf']) {
        islandora_view_datastream($object['RELS-EXT']);
      }
    }
  }

}
