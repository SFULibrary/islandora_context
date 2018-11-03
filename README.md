# Islandora Context

Provides a set of [Context](https://drupal.org/project/context) "conditions" and "reactions" for Islandora objects. Think of this module as an "if-this-then-that" configurator for Islandora repositories.

Use cases, and ideas for new conditions and reactions, are welcome.

## Introduction

This module provides the following Context conditions:

* Collection membership: Define a set of collections; if the current object is a member of a collection in this set, the condition is triggered.
* Collection is empty: Determine if a collection object is empty (i.e., has no members). If the current collection object is empty, this condition is triggered.
* Content models: Define a set of content models; if the current object has any of the content models in this set, the condition is triggered.
* Object namespace: Define a list of PID namespaces; if the current object's namespace is in this list, the condition is triggered.
* Object relationships: Define a statement stored in RELS-EXT; if the current object's RELS-EXT contains the relationship, the condition is triggered.
* Keywords in datastream: Define a DSID and a list of keywords; if any of the keywords in the list is found in the designated datastream, the condition is triggered.
* Datastream mime type: Define a DSID and a list of mime types; if the datastream has any of the listed mime types, the condition is triggered.
* Is Islandora Object: Set this condition if you want the context to apply to all Islandora objects. Allows choice of collection, non-collection, and all objects.
* HTTP content negotiation: Detect whether a requesting client has included an 'Accept' header with the value 'application/rdf+xml' (experimental).

It also provides the following Context reactions:

* Insert text into Islandora object's display: Lets you define the text of a message (such as a rights statement) which is appended to an Islandora object's display. The HTML containing the message is themeable.
* Use an Islandora Solr Metadata Configuration: Lets you choose a Solr Metadata display. The Islandora Solr Metadata module associates displays with content types; this reaction lets you associate displays with any context. If associated conditions are not set, metadata displays fall back to whatever is configured for the current object in Islandora Solr Metadata.
  * Use the corresponding Islandora Solr Metadata description: Display a description element corresponding to the selected Solr Metadata configuration. Note that you must choose these two reactions separately.
* Display the metadata of an object's compound parent: If the object is part of a compound object, display the parent's metadata beneath the object's. Works with default DC metadata or Solr Metadata display configurations managed by Islandora Context.
* Hide an object's metadata "Details" div. Uses JavaScript to hide the div, does not remove the markup from the HTML.
* Hide an object's metadata "Description" markup. Uses JavaScript to hide the markup, does not remove it from the HTML.
* Hide an object's "In collections" markup. Uses JavaScript to hide the markup, does not remove it from the HTML.
* Restrict access to an object based on the user's IP address: Lets you define a set of IP ranges (or single IP addresses) that objects are allowed to be accessed from. Users outside these ranges receive an "Access denied" message. Thumbnails are excluded from this restriction (that is, users outside the allowed IP ranges can view a restricted object's thumbnail). There is also an option to configure a URL to redirect users to, for example an Ezproxy URL.
* Filter generation of Islandora derivatives: Lets you define which derivates to generate. Only triggered by the "Islandora Collection Membership", "Islandora Content Models", "Islandora PID Namespace", and "Islandora Relationship" conditions.
* Use an Islandora viewer: Use one of the configured Islandora viewers. Experimental; currently only works with basic image objects.
* Return the object's RELS-EXT datastream; for use with the content negotiation condition plugin (e.g., curl -H "Accept: application/rdf+xml" "http://localhost:8181/islandora/object/islandora%253A226") (experimental).

## Requirements

* [Islandora](https://github.com/Islandora/islandora)
* [Context](https://drupal.org/project/context)
* [Islandora Solr Metadata](https://github.com/Islandora/islandora_solr_metadata) if you want to use the "Use an Islandora Solr Metadata Configuration" reaction.

## Installation

Install as usual, see [this](https://drupal.org/documentation/install/modules-themes/modules-7) for further information. In addition:

* Be sure to enable the Context UI module, which is part of the Context module.
* You will likely need to clear your Drupal cache to see the Islandora-specific conditions and reactions.

## Usage

Install and configure. To create a context, go to Structure > Context and click on Add. The conditions and reactions listed above will appear in their respective sections of the context form.

Some possible uses of this module are to display a certain block if an Islandora object has specific words in its MODS datastream; disable specific theme regions when Islandora objects have a specific relationship in their RELS-EXT; show users of a certain role a specific Solr Metadata display; or add a rights statement or other text to all objects that are in a specific collection.

If you want to use the "Use an Islandora Solr Metadata Configuration" reaction, you will need to create a Solr Metadata configuration at admin/islandora/search/islandora_solr/metadata and then select "Islandora Solr Metadata managed by the Islandora Context module" as the default viewer at admin/islandora/metadata.

The conditions and reaction provided by this module can be used with other Context modules, such as:

* [Context Add Assets](https://drupal.org/project/context_addassets): Add Javascript or CSS based on a condition
* [Context Disable Context](https://drupal.org/project/context_disable_context): Disable a context based on a condition
* [Context GeoIP](https://drupal.org/project/context_geoip): Use the user's IP address as a condition
* [Context HTTP Headers](https://drupal.org/project/context_http_headers): Set custom HTTP headers based on a condition
* [Context Hide Local Tasks](https://drupal.org/project/context_local_tasks): Hide local task tabs, no coding required
* [Context PHP](https://drupal.org/project/contextphp): Evaluate PHP code as a condition and execute PHP code as a reaction
* [Context Reaction Theme](https://drupal.org/project/context_reaction_theme): Change site theme based on a condition (see note below)
* [Context Rules](https://drupal.org/project/context_rules): Integrate [Rules](https://www.drupal.org/project/rules) into contexts
* [Context Useragent](https://drupal.org/project/context_useragent): Define reactions based on the user's browser
* [Context as Reaction](https://drupal.org/project/context_as_reaction): Set a context via a reaction

And there are many more.

## Limitations

* One common use of Context is to change a site's theme based on certain conditions, using the [Context Reaction: Theme](https://drupal.org/project/context_reaction_theme) module. As stated on that module's project page, "you can only use Context Reaction: Theme with the 'Sitewide' or 'Path' conditions." This means that the conditions defined by Islandora Context can't initiate theme switching. To switch themes for collections or for members of a collection, you should use the Path condition to match for namespaces or PIDs. You may also want to check out the [Islandora Themekey](https://github.com/mjordan/islandora_themekey) module, which lets you switch your site's theme based on attributes of the current Islandora object.
* The "Breadcrumbs" reaction [does not work with Islandora objects](https://github.com/mjordan/islandora_context/issues/1).
* The "Display the metadata of an object's compound parent" reaction does not apply to compound objects that are children of other compound objects.

## Maintainer

* [Mark Jordan](https://github.com/mjordan)

### Troubleshooting

As a general rule, if disabling or changing a Context condition or reaction doesn't work, clear your site's cache and try again.

## Feedback and Contrubuting

Feedback, but reports, use cases, and pull requests are welcome. See CONTRIBUTING.md for details. Also feel free to post to the [Islandora Group](https://groups.google.com/forum/?hl=en&fromgroups#!forum/islandora) before opening an issue.
