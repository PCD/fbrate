<?php
// Implements hook_permissions.
function fbrate_api_permission() {
  return array(
    'consultar comentarios' => array(
      'title' => t('Consultar los comentarios de fb'),
      'description' => t('Consultar los comentarios de facebook.'),
    ),
  );
}