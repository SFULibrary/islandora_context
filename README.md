# Islandora Context

Provides a set of [Context](https://dupal.org/project/context) conditions for Islandora objects. Still very early in development - use cases are welcome.

## Introduction

Provides a set of Context conditions for Islandora objects:

* Object namespace: Define a list of PID namespaces to trigger a condition; if the current object's namespace is in this list, the condition is triggered.
* Collection membership: Define a list of collection PIDs to trigger a condition; if the current object is a member of a collection in this list, the condition is triggered.

## Requirements

[Context](https://dupal.org/project/context)

## Installation

Install as usual, see [this](https://drupal.org/documentation/install/modules-themes/modules-7) for further information.

## Usage

Install and configure. To create a context, go to Structure > Context and click on Add. "Islandora Collection Membership" and "Islandora PID Namespace" will appear in the Conditions list.

One common use of Context is with the accompanying [Context Reaction: Theme](https://drupal.org/project/context_reaction_theme) module. As stated on that module's project page, "you can only use Context Reaction: Theme with the 'Sitewide' or 'Path' conditions." This means that the conditions defined by Islandora Context won't initiate theme switching. To switch themes for collections or for members of a collection, you should use the Path condition to match for namespaces or PIDs. You may also want to check out the [Themekey](https://www.drupal.org/project/themekey) module, althought it doesn't currently have any Islandora-specific functionality.

## Troubleshooting/issues/feedback

Feedback and use cases (including Islandora-specific 'reactions') are welcome.

* [Islandora Group](https://groups.google.com/forum/?hl=en&fromgroups#!forum/islandora)
* [Islandora Dev Group](https://groups.google.com/forum/?hl=en&fromgroups#!forum/islandora-dev)

