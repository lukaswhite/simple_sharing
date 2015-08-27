<?php

/**
 * Form for configuring the Simple Sharing widget
 * 
 * @param  array $form
 * @param  array $form_state
 * @return array
 */
function simple_sharing_config_form($form, &$form_state)
{

	$form['when'] = array(
		'#type'		=>	'fieldset',
		'#title'	=>	t('When to show the sharing links'),
	);

	foreach (node_type_get_types() as $key => $content_type) {
		$content_type_options[$key] = $content_type->name;
	}

	$form['when']['simple_sharing_node_types'] = array(
		'#type'						=>	'checkboxes',		
		'#title'					=>	t('Content Types'),
		'#description'		=>	t('Select which content types should include the simple sharing links'),
		'#options'				=>	$content_type_options,
		'#default_value'	=>	variable_get('simple_sharing_node_types', array()),
	);

	$entity_info = entity_get_info('node');
	$view_modes = $entity_info['view modes'];

	$view_modes_options = array();

	foreach ($view_modes as $key => $view_mode) {
		$view_modes_options[$key] = $view_mode['label'];		
	}

	$form['when']['simple_sharing_view_modes'] = array(
		'#type'						=>	'checkboxes',		
		'#title'					=>	t('View Modes'),
		'#description'		=>	t('Select which view modes should include the simple sharing links'),
		'#options'				=>	$view_modes_options,
		'#default_value'	=>	variable_get('simple_sharing_view_modes', array()),
	);

	$form['networks'] = array(
		'#type'		=>	'fieldset',
		'#title'	=>	t('Networks to include'),
	);

	$form['networks']['simple_sharing_show_facebook'] = array(
		'#type'						=>	'checkbox',
		'#title'					=>	'Facebook',
		'#default_value'	=>	variable_get('simple_sharing_show_facebook', TRUE),
	);
	
	$form['networks']['simple_sharing_show_twitter'] = array(
		'#type'						=>	'checkbox',
		'#title'					=>	'Twitter',
		'#default_value'	=>	variable_get('simple_sharing_show_twitter', TRUE),
	);

	$form['networks']['simple_sharing_show_googleplus'] = array(
		'#type'						=>	'checkbox',
		'#title'					=>	'Google+',
		'#default_value'	=>	variable_get('simple_sharing_show_googleplus', FALSE),
	);

	$form['networks']['simple_sharing_show_linkedin'] = array(
		'#type'						=>	'checkbox',
		'#title'					=>	'LinkedIn',
		'#default_value'	=>	variable_get('simple_sharing_show_linkedin', FALSE),
	);

	$form['networks']['simple_sharing_show_pinterest'] = array(
		'#type'						=>	'checkbox',
		'#title'					=>	'Pinterest',
		'#default_value'	=>	variable_get('simple_sharing_show_pinterest', FALSE),
	);

	$form['networks']['simple_sharing_show_email'] = array(
		'#type'						=>	'checkbox',
		'#title'					=>	t('Share via E-mail'),
		'#default_value'	=>	variable_get('simple_sharing_show_email', FALSE),
	);

	$form['email'] = array(
		'#type'		=>	'fieldset',
		'#title'	=>	t('Send via E-mail options'),
		'#states'	=> 	array(
			'visible' => array(
      	':input[name="simple_sharing_show_email"]' => array('checked' => TRUE),
    	),
    ),
	);

	$form['email']['simple_sharing_email_type'] = array(
		'#type'						=>	'radios',
		'#title'					=>	t('What kind of link to show'),
		'#options'				=>	array(
			'forward'		=>	(module_exists('forward')) ? t('Use the forward module') : t('Use the forward module (NOT INSTALLED)'),
			'print'			=>	(module_exists('print')) ? t('Use the print module') : t('Use the print module (NOT INSTALLED)'),
			'mailto'		=>	t('Open up an e-mail dialog'),
			'custom'		=>	(module_exists('token')) ? t('Specify a custom URL') : t('Specify a custom URL (requires the token module)'),
		),
		'#default_value'	=>	variable_get('simple_sharing_email_type', 'custom'),
	);	

	$form['email']['simple_sharing_email_custom_url'] = array(
		'#type'						=>	'textfield',
		'#title'					=>	t('Send via E-mail URL'),
		'#description'		=>	t('Enter the custom URL for e-mailing a node. Available tokens: [node:nid], [node:title], [node:url].'),		
		'#default_value'	=>	variable_get('simple_sharing_email_custom_url', 'http://www.example.com?url=[node:url]&title=[node:title]'),
		'#states'	=> 	array(
			'visible' => array(
      	':input[name="simple_sharing_email_type"]' => array('value' => 'custom'),
    	),
    	'required' => array(
      	':input[name="simple_sharing_email_type"]' => array('value' => 'custom'),
    	),
    ),
	);	

	if (!module_exists('forward')) {
	  $form['email']['simple_sharing_email_type']['forward'] = array(
	  	'#disabled'	=>	TRUE,
	  );
	}

	if (!module_exists('print')) {
	  $form['email']['simple_sharing_email_type']['print'] = array(
	  	'#disabled'	=>	TRUE,
	  );
	}

	if (!module_exists('token')) {
	  $form['email']['simple_sharing_email_type']['custom'] = array(
	  	'#disabled'	=>	TRUE,
	  );
	}

	$form['caption'] = array(
		'#type'		=>	'fieldset',
		'#title'	=>	t('Caption'),
	);

	$form['caption']['simple_sharing_caption_text'] = array(
		'#type'						=>	'textfield',
		'#title'					=>	t('Caption to show'),
		'#description' 		=>	t('If you leave this blank, no caption will be rendered. You can use the [node:content-type] token to inject the name of the content type. So for example, an article might display "Share this article" whereas a page might show "Share this page". Note that this requires the token module.'),
		'#default_value'	=>	variable_get('simple_sharing_caption_text', t('Share this Post')),
	);

	$form['caption']['simple_sharing_caption_level'] = array(
		'#type'						=>	'select',
		'#title'					=>	t('Level of the caption (e.g. h1, h2, h3 etc.)'),
		'#options'				=> 	drupal_map_assoc(array('h1', 'h2', 'h3', 'h4', 'h5', 'h6')),
		'#default_value'	=>	variable_get('simple_sharing_caption_level', 'h2'),
	);	

	$form['styling'] = array(
		'#type'		=>	'fieldset',
		'#title'	=>	t('Styling'),
	);

	$form['styling']['simple_sharing_outer_classes'] = array(
		'#type'						=>	'textfield',
		'#title'					=>	t('CSS classes to apply to the outer DIV'),
		'#default_value'	=>	variable_get('simple_sharing_outer_classes', 'simple-sharing'),
	);

	$form['styling']['simple_sharing_list_classes'] = array(
		'#type'						=>	'textfield',
		'#title'					=>	t('CSS classes to apply to the UL element'),
		'#default_value'	=>	variable_get('simple_sharing_list_classes', 'social simple-sharing-list list-inline'),
	);

	$form['links'] = array(
		'#type'		=>	'fieldset',
		'#title'	=>	t('Link options'),
	);

	$form['links']['simple_sharing_link_target'] = array(
		'#type'						=>	'select',
		'#title'					=>	t('Link target'),
		'#options'				=>	array(
			''					=>	t('Don\'t specify a target'),
			'_blank'		=>	t('New window (_blank)'),
			'_self'			=>	t('Current window (_self)'),
			'_parent'		=>	t('Parent window (_parent)'),
			'_top'			=>	t('Full browser window (_top)'),
		),
		'#default_value'	=>	variable_get('simple_sharing_link_target', ''),
	);

	$form['styling']['simple_sharing_list_classes'] = array(
		'#type'						=>	'textfield',
		'#title'					=>	t('CSS classes to apply to the UL element'),
		'#default_value'	=>	variable_get('simple_sharing_list_classes', 'social simple-sharing-list list-inline'),
	);

	
	if (module_exists('token')) {
	  $form['token_help'] = array(
	    '#theme' => 'token_tree',
	    '#token_types' => array ('node'),
	  );
	}
	
	

  return system_settings_form($form);

}
