<?php
/**
 * @file
 * Context plugin that restricts access to Islandora objects.
 *
 * Compares client IP address to set of registered addresses.
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
        '#description' => t('Enter the IP address ranges, one per line, that are allowed to view objects. ' .
          'Separate the low and high ends of each range with a colon, e.g. 111.111.111.111:222.222.222.222. ' .
          ' Asterisks are not allowed. Single IP addresses are also allowed, each on its own line.'),
        '#type' => 'textarea',
        '#default_value' => isset($settings['allowed_ip_ranges']) ? $settings['allowed_ip_ranges'] : '',
      ),
      'redirect_url' => array(
        '#title' => t('Redirect URL'),
        '#description' => t("URL to redirect user to, e.g., an Ezproxy login URL. If option below is " .
          " checked, object's URL will be appended to this URL."),
        '#type' => 'textfield',
        '#default_value' => isset($settings['redirect_url']) ? $settings['redirect_url'] : '',
      ),
      'append_object_url' => array(
        '#type' => 'checkbox',
        '#title' => t("Append object's URL"),
        '#default_value' => isset($settings['append_object_url']) ?
          $settings['append_object_url'] : FALSE,
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
   * @return bool|array|NULL
   *    TRUE if the client's IP address is in a registered range,
   *    FALSE if it is not. Null if no check is made because no IP addresses
   *    have been registered. If redirect_url option is configured, return
   *    an array containing the redirect_url value and the optional append
   *    object URL flag.
   */
  public function execute() {
    $is_allowed = array();
    foreach ($this->get_contexts() as $context) {
      if (isset($context->reactions) && (!empty($context->reactions[$this->plugin]['allowed_ip_ranges']))) {
        $configured_ranges = $context->reactions[$this->plugin]['allowed_ip_ranges'];
        $is_allowed = $this->check_ip($configured_ranges);
        if (in_array(1, $is_allowed)) {
          return TRUE;
        }
        if (in_array(0, $is_allowed) && strlen($context->reactions[$this->plugin]['redirect_url'])) {
          $return = array($context->reactions[$this->plugin]['redirect_url']);
          if ($context->reactions[$this->plugin]['append_object_url']) {
            $return[] = TRUE;
          }
          return $return;
        }
        if (in_array(0, $is_allowed)) {
          return FALSE;
        }
      }
      return NULL;
    }
  }

  /**
   * Loop through IP ranges to see if the client address is within any of them.
   *
   * @param string $ip_ranges
   *   The value of the reaction's configuration form field containing the
   *   IP ranges.
   *
   * @return array
   *   An array that may contain 1 or 0 to indicate whether the client IP
   *   address was within each range.
   */
  private function check_ip($ip_ranges) {
    $is_allowed = array();

    // Get client's IP address and convert it to a long integer for
    // comparison with the registered ranges.
    $comparable_address = ip2long(ip_address());

    $ranges = preg_split("/\\r\\n|\\r|\\n/", $ip_ranges);
    foreach ($ranges as $range) {
      $range = preg_replace('/\s+/', '', $range);
      if (!strlen($range)) {
        continue;
      }
      list($low, $high) = array_pad(explode(':', $range, 2), 2, NULL);

      // Check ranges of IP addresses.
      if (!is_null($low) && !is_null($high)) {
        $comparable_low = ip2long($low);
        $comparable_high = ip2long($high);
        if ($comparable_address >= $comparable_low && $comparable_address <= $comparable_high) {
          $is_allowed[] = 1;
        }
        else {
          $is_allowed[] = 0;
        }
      }

      // Check individual IP addresses.
      if (!is_null($low) && is_null($high)) {
        if (ip_address() == $low) {
          $is_allowed[] = 1;
        }
        else {
          $is_allowed[] = 0;
        }
      }

    }
    return $is_allowed;
  }

}
