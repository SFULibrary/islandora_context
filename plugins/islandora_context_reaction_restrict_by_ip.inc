<?php
/**
 * @file
 * Context plugin that restricts access to Islandora objects 
 * based on the IP address of the client.
 */

/**
 * Expose a message as a context reaction.
 */
class IslandoraContextReactionRestrictByIp extends context_reaction {

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
      '#title' => t('Allowed IP ranges'),
      'allowed_ip_ranges' => array(
        '#title' => t('Allowed IP ranges'),
        '#description' => t('Enter the IP address ranges, one per line, that are allowed to view objects. Separate the low and high ends of each range with a colon, e.g. 111.111.111.111:222.222.222.222'),
        '#type' => 'textarea',
        '#default_value' => isset($settings['allowed_ip_ranges']) ? $settings['allowed_ip_ranges'] : '',
      ),
    );
    return $form;
  }
  // @codingStandardsIgnoreEnd

  /**
   * Check the client's IP address and test it against the configured ranges.
   *
   * IP checking code borrowed from Islandora IP Embargo.
   *
   * @return bool
   *  TRUE if the client's IP address is in a registered range,
   *    FALSE if it is not.
   */
  public function execute() {
    foreach ($this->get_contexts() as $context) {
      if (isset($context->reactions['islandora_context_reaction_restrict_by_ip']['allowed_ip_ranges'])) {
        $is_allowed = FALSE;
        // Get client's IP address.
        $comparable_address = ip2long(ip_address());
        // Loop through the ranges and test to see if the address is within any of them.
        $configured_ranges = $context->reactions['islandora_context_reaction_restrict_by_ip']['allowed_ip_ranges'];
        $ranges = explode(PHP_EOL, $configured_ranges);
        foreach ($ranges as $range) {
          list($low, $high) = explode(':', $range);
          $comparable_high = ip2long(trim($high));
          $comparable_low = ip2long(trim($low));
          if ($comparable_address >= $comparable_low && $comparable_address <= $comparable_high) {
            $is_allowed = TRUE;
          }
        }
        if ($is_allowed) {
          return TRUE;
        }
        else {
          return FALSE;
        }
      }
      else {
        return TRUE;
      }
    }
  }
}
