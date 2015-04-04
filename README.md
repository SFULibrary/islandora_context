# Islandora Context

Provides a set of [Context](https://dupal.org/project/context) "conditions" and "reactions" for Islandora objects. Think of this module as an "if-this-then-that" configurator for Islandora repositories. Use cases are welcome.

## Introduction

This module provides the following Context conditions:

* Collection membership: Define a set of collections; if the current object is a member of a collection in this set, the condition is triggered.
* Object namespace: Define a list of PID namespaces; if the current object's namespace is in this list, the condition is triggered.
* Object relationships: Define a statement stored in RELS-EXT; if the current object's RELS-EXT contains the relationship, the condition is triggered.
* Keywords in datastream: Define a DSID and a list of keywords; if any of the keywords in the list is found in the designated datastream, the condition is triggered.
* Is Islandora Object: Set this condition if you want the context to apply to all Islandora objects. Allows choice of collection, non-collection, and all objects.
* Perform basic content negotiation by detecting whether the requesting client has included an 'Accept' header with the value 'application/rdf+xml' (experimental).

It also provides two Context reactions:

* Insert text into Islandora object's display: Lets you define the text of a message (such as a rights statement) which is appended to an Islandora object's display. The HTML containing the message is themeable.
* Return the object's RELS-EXT datastream (experimental); for use with the content negotiation condition plugin (e.g., curl -H "Accept: application/rdf+xml" "http://localhost:8181/islandora/object/islandora%253A226").

## Requirements

* [Islandora](https://github.com/Islandora/islandora)
* [Context](https://dupal.org/project/context)

## Installation

Install as usual, see [this](https://drupal.org/documentation/install/modules-themes/modules-7) for further information.

## Usage

Install and configure. To create a context, go to Structure > Context and click on Add. The conditions and reactions listed above will appear in their respective sections of the context form.

Some possible uses of this module are to display a certain block if an Islandora object has specific words in its MODS datastream; alter a breadcrum or the navigation menu when displaying Islandora objects that have a specific relationship in their RELS-EXT; or adding a rights statement to all objects that are in a specific collection.

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

One common use of Context is to change a site's theme based on certain conditions, using the [Context Reaction: Theme](https://drupal.org/project/context_reaction_theme) module. As stated on that module's project page, "you can only use Context Reaction: Theme with the 'Sitewide' or 'Path' conditions." This means that the conditions defined by Islandora Context won't initiate theme switching. To switch themes for collections or for members of a collection, you should use the Path condition to match for namespaces or PIDs. You may also want to check out the [Islandora Themekey](https://github.com/mjordan/islandora_themekey) module, which lets you switch your site's theme based on collection membership of the current Islandora object.

## Troubleshooting/issues/feedback

Feedback and use cases for Islandora-specific "conditions" and "reactions" are welcome.

* [Islandora Group](https://groups.google.com/forum/?hl=en&fromgroups#!forum/islandora)
* [Islandora Dev Group](https://groups.google.com/forum/?hl=en&fromgroups#!forum/islandora-dev)

