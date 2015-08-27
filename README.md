#Simple Sharing Module for Drupal 7

> This is a work-in-progress, although as things stand it should work out-of-the-box.

There are [a number of modules](https://www.ostraining.com/blog/drupal/4-social-sharing-modules-drupal/) for adding links to Drupal content for sharing via social networks. But they tend to either be needlessly complicated, integrate with external services such as AddThis, or litter your pages with nasty Javascript widgets.

This module makes it dead simple. It just generates a bunch of URLs for services. No JS, no messing around.

It supports the following:

* Facebook
* Twitter
* Google+
* LinkedIn
* Pinterest
* E-mail

##Share via E-mail

Sharing via e-mail is a special case, as it's not supported out-of-the-box. Nevertheless, it's still pretty simple to set up. You have a few options:

* Integration with the [forward](https://www.drupal.org/project/forward) module - it simply auto-generates the appropriate link
* Integration with the e-mail feature within the [print](https://www.drupal.org/project/forward) module - it simple auto-generates the appropriate link
* Use a `mailto:` link, which opens up an e-mail dialog with the node title as the subject, and the URL as the body 
* Specify a custom URL; you can inject the Node URL, Node title and / or the Node's `nid` using the [token](https://www.drupal.org/project/forward) module

##Installation

Download the module, enable it, then configure it.

##Configuration

You'll find the configuration form here:

```
admin/config/search/simple-sharing
```

Alternatively, the menu item can be found by browsing as follows: *Configuration -> Search and metadata -> Simple Sharing*.

The config form provides a number of options:

* You can select which content (node) types for which you want the links to appear
* You can select which view modes for which you want the links to appear (e.g. Full content, teaser etc)
* You can select which networks to include (e.g. Facebook, Twitter, etc - full list is above)
* You can customize the text (default is "Share this Post"), as well as its level (e.g. h1, h2, h3...)
* Additionally, you can specify the options for sharing via E-mail, as specified above
* You can also specify CSS classes for the containing `<div>` and/or the `<ul>` element which contains the actual links
* Finally, you can specify where to open the links, e.g. in the current window, a new window etc (i.e. the target attribute)

##Enhancements

If I have time, I'll add the following:

* Aditional networks (which ones?)
* The ability to specify an image for Pinterest