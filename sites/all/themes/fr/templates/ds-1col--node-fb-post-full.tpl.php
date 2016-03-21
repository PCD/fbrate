<?php
require_once drupal_get_path('module', 'fbrate') . '/vendor/autoload.php';
$graphNode = unserialize($variables['field_fb_graph_node'][0]['value']);
if ( isset($_GET['debug_fb']) ) {
  print_r($graphNode);
  exit;
}
$from = $graphNode['from']['name'];
$when = $graphNode['created_time']->date;
$link = $graphNode['link'];
$total_likes = $graphNode['total_likes'];
// Get First Image if Any
$name = check_plain($graphNode['name']);
if ( isset($graphNode['images'][0]) ) {
  $img = $graphNode['images'][0];
  $image = "<img src=\"{$img['source']}\" width=\"{$img['width']}\" height=\"{$img['height']}\" />";
}


// Comments
$total_comments = $graphNode['total_comments'];

/**
 * @file
 * Display Suite 1 column template.
 */
?>
<<?php print $ds_content_wrapper; print $layout_attributes; ?> class="ds-1col <?php print $classes;?> clearfix">

  <?php if (isset($title_suffix['contextual_links'])): ?>
  <?php print render($title_suffix['contextual_links']); ?>
  <?php endif; ?>
  <div class="from">
    <?php print $from;?>
  </div>
  <div class="when">
    <a href="<?php print $link;?>" target="_blank"><?php print $when;?></a>
  </div>
  <div class="body">
    <?php print $name;?>
  </div>
  
  <?php if (isset($image)):?>
  <div class="image">
    <?php print $image;?>
  </div>
  
  <div class="total_likes">
    <?php print number_format($total_likes);?> Me Gusta
  </div>
  
  <div class="total_comments">
    <?php print number_format($total_comments);?> Comentarios
  </div>
  <?php endif;?>
</<?php print $ds_content_wrapper ?>>

<?php if (!empty($drupal_render_children)): ?>
  <?php print $drupal_render_children ?>
<?php endif; ?>
