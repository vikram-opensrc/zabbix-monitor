<?php
/**
* Implementation of zabbix setting form
*/
require_once 'lib/ZabbixApi.class.php';
use ZabbixApi\ZabbixApi;
function zabbix_monitor_settings(){
  $form['zabbix_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Zabbix settings'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );
    $form['zabbix_settings']['zabbix_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Zabbix URL'),
	'#required' => TRUE,
    '#size' => 120,
    '#maxlength' => 120,
    '#default_value' => variable_get('zabbix_url', ''),
    '#description' => t('The generic URL over which the communication is to take place. Example: https://your.host.com/zabbix/api_jsonrpc.php'),	
	'#attributes' =>array('placeholder' => t('Zabbix URL')),
  );
  $form['zabbix_settings']['zabbix_user'] = array(
    '#type' => 'textfield',
    '#title' => t('Zabbix Username'),
	'#required' => TRUE,
    '#size' => 50,
    '#maxlength' => 10,
    '#default_value' => variable_get('zabbix_user', ''),
    '#description' => t('The username for zabbix.'),
	'#attributes' =>array('placeholder' => t('Zabbix Username')),
  );
  $form['zabbix_settings']['zabbix_pass'] = array(
    '#type' => 'password',
    '#title' => t('Zabbix Password'),
	'#required' => TRUE,
    '#size' => 50,
    '#maxlength' => 10,
    '#default_value' => variable_get('zabbix_pass', ''),
    '#description' => t('The password for zabbix.'),
	'#attributes' =>array('placeholder' => t('Zabbix Password')),
  );
  
  //$form['#validate'] = 'zabbix_monitor_settings_validate';
  //$form['#submit'] = 'zabbix_monitor_settings_submit';
  
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Submit',
  );
  return $form;
}

function zabbix_monitor_settings_validate($form,&$form_state){
  $url = $form_state['values']['zabbix_url'];
  if (filter_var($url, FILTER_VALIDATE_URL) === false) {
    form_set_error('zabbix_url',"$url ".t("is not a valid URL."));
  }
  if(!empty($form_state['values']['zabbix_url']) && !empty($form_state['values']['zabbix_user']) && !empty($form_state['values']['zabbix_pass'])){
    check_connection($form_state['values']['zabbix_url'],$form_state['values']['zabbix_user'],$form_state['values']['zabbix_pass'],$form,$form_state);
  }
}

function zabbix_monitor_settings_submit($form,&$form_state){
  $url=filter_xss($form_state['values']['zabbix_url']);
  $user=filter_xss($form_state['values']['zabbix_user']);
  $pass=filter_xss($form_state['values']['zabbix_pass']);
  variable_set('zabbix_url',$url);
  variable_set('zabbix_user',$user);
  variable_set('zabbix_pass',$pass);
}

function check_connection($url='',$user='',$pass='',$form,&$form_state){
  try
  {
      // connect to Zabbix API
      $api = new ZabbixApi($url ,$user,$pass);
	  drupal_set_message(t('Connected successfully to Zabbix server'));
      /* ... do your stuff here ... */
  }
  catch(Exception $e)
  {
      // Exception in ZabbixApi catched
      $msg = $e->getMessage();
	  form_set_error('zabbix_settings',$msg);
  }
}

function get_connection($url='',$user='',$pass=''){
  try
  {
      // connect to Zabbix API
      $api = new ZabbixApi($url ,$user,$pass);
	  $GLOBALS['connection'] = $api;
      /* ... do your stuff here ... */
  }
  catch(Exception $e)
  {
      // Exception in ZabbixApi catched
      $msg = $e->getMessage();
  }
}

function zabbix_graph_settings(){

}
