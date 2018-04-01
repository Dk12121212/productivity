<?php

/**
 * Implementation of hook_drush_command().
 */
function productivity_payment_drush_command() {
  return [
    'gi-import' => [
      'callback' => 'drush_productivity_payment_green_invoice_import',
      'aliases' => array('gii'),
      'description' => 'Get invopices from Greeninvoice',
      'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_FULL,
    ],
  ];
}

/**
 * Pull
 */
function drush_productivity_payment_green_invoice_import() {
  // see https://greeninvoice.docs.apiary.io/#reference/items/search-items/search-items.

  $apiKey = "756a241e-be41-4098-8409-c67fc48abe27";
  $apiSecret = "XHT0Pm7rrwVwILi_g3wGdQ";

  $params = array(
    "timestamp" => time(), //Current timestamp
    "callback_url" => "{your-callback-url}",
    "doc_type" => 320,
    "description" => "תיאור מסמך",
    "client" => array(
      "send_email" => true,
      "name" => "לקוח חדש",
      "tax_id" => "123456789",
      "email" => "user@email.com",
      "address" => "רח' דיזנגוף 300",
      "city" => "תל אביב",
      "zip" => "1234567"
    ),
    "income" => array(
      array(
        "price" => "500.00",
        "description" => "תיאור שורת הכנסה"
      )
    ),
    "payment" => array(
      array(
        "type" => 2, //Cheque
        "date" => "2012-01-01", //YYYY-MM-DD
        "amount" => "500.00",
        "bank" => "מזרחי טפחות",
        "branch" => "761",
        "account" => "123456",
        "number" => "10928"
      )
    )
  );

//Compute hashed signature with SHA-256 algorithm and the secret key
  $params_encoded = json_encode($params);
  $signature = base64_encode(hash_hmac('sha256', $params_encoded, $apiSecret, true));

  $data = array(
    "apiKey" => $apiKey,
    "params" => $params,
    "sig" => $signature
  );

//Initializing curl
  $ch = curl_init();

//Configuring curl options
  $options = array(
    CURLOPT_URL => "https://www.greeninvoice.co.il/api/documents/add",
    CURLOPT_POST => true,
    CURLOPT_POSTFIELDS => "data=" . urlencode(json_encode($data)),
    CURLOPT_SSL_VERIFYPEER => false,
    CURLOPT_RETURNTRANSFER => true,
    CURLOPT_HTTPHEADER => array("Content-Type: application/x-www-form-urlencoded; charset=utf-8")
  );

//Setting curl options
  curl_setopt_array($ch, $options);

//Getting results
  $result = curl_exec($ch); // Getting jSON result string
  curl_close($ch);

//Parse result to JSON
  $response = json_decode($result);

//If Ok
  if ($response->error_code == 0) {
    //Process response here
  }
}
