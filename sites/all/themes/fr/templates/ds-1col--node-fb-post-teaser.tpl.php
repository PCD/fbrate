<?php
if ( isset($_GET['debug_fb']) ) {
  print_r($graphNode);
  exit;
}

// Body
$body = check_plain($graphNode['name']);

// Image
$newidth = 150;
if ( $graphNode['graph_type'] == 'video' ) {
  $image = $graphNode['embed_html'];
  $imagesrc = $graphNode['picture'];
  $pattern = '/src="([^"]*?)".*?width="([^"]*?)".*?height="([^"]*?)"/msi';
  preg_match($pattern, $image, $match);
  $newheight = intval($newidth/intval($match[2])*intval($match[3]));
  $image = "<img src=\"{$imagesrc}\" width=\"{$newidth}\" height=\"{$newheight}\" />";
} else if ( isset($graphNode['images'][0]) ) {
  $img = $graphNode['images'][0];
  $newheight = intval($newidth/intval($img['width'])*intval($img['height']));
  $image = "<img src=\"{$img['source']}\" width=\"{$newidth}\" height=\"{$newheight}\" />";
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

  <?php //print $ds_content; ?>
  <div class="post">
    <div class="image">
      <?php print $image;?>
    </div>
    <div class="data">
      <div class="body">
        <?php print $body;?>
      </div>
    </div>
  </div>
</<?php print $ds_content_wrapper ?>>

<?php if (!empty($drupal_render_children)): ?>
  <?php print $drupal_render_children ?>
<?php endif; ?>
