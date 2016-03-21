<?php
require_once drupal_get_path('module', 'fbrate') . '/vendor/autoload.php';
$graphNode = unserialize($variables['field_fb_graph_node'][0]['value']);
// Get First Image if Any
print_r($graphNode['images']);exit;
if ( isset($graphNode['images'][0]) ) {
  $img = $graphNode['images'][0];
  $image = "<img src=\"{$img['source']}\" width=\"{$img['width']}\" height=\"{$img['height']}\" />";
}


/**
 * @file
 * Display Suite 1 column template.
 */
?>
<<?php print $ds_content_wrapper; print $layout_attributes; ?> class="ds-1col <?php print $classes;?> clearfix">

  <?php if (isset($title_suffix['contextual_links'])): ?>
  <?php print render($title_suffix['contextual_links']); ?>
  <?php endif; ?>

  <?php if (isset($image)):?>
  <div class="image">
    <?php print $image;?>
  </div>
  <?php endif;?>
</<?php print $ds_content_wrapper ?>>

<?php if (!empty($drupal_render_children)): ?>
  <?php print $drupal_render_children ?>
<?php endif; ?>
