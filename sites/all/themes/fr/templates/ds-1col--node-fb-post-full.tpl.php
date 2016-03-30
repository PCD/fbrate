<?php
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
if ( $graphNode['graph_type'] == 'video' ) {
  $image = $graphNode['embed_html'];
  $pattern = '/src="([^"]*?)".*?width="([^"]*?)".*?height="([^"]*?)"/msi';
  preg_match($pattern, $image, $match);
  $newidth = 720;
  $newheight = intval(720/intval($match[2])*intval($match[3]));
  $image = "<iframe src=\"{$match[1]}\" width=\"{$newidth}\" height=\"{$newheight}\" frameborder=\"0\"></iframe>";
} else if ( isset($graphNode['images'][0]) ) {
  $img = $graphNode['images'][0];
  $image = "<img src=\"{$img['source']}\" width=\"{$img['width']}\" height=\"{$img['height']}\" />";
}


// Comments
$total_comments = count($cids);

/**
 * @file
 * Display Suite 1 column template.
 */
?>
<<?php print $ds_content_wrapper; print $layout_attributes; ?> class="ds-1col <?php print $classes;?> clearfix">

  <?php if (isset($title_suffix['contextual_links'])): ?>
  <?php print render($title_suffix['contextual_links']); ?>
  <?php endif; ?>
  <div class="post">
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
    
    <div class="post-bottom">
      <div class="post-data">
        <div class="total_likes">
          <?php print number_format($total_likes);?> Me Gusta
        </div>
        
        <div class="total_comments">
          <?php print number_format($total_comments);?> Comentarios
        </div>
      </div>
      
      <div class="post-actions">
        <label id="label-show-rated-comments" for="show-rated-comments"><input type="checkbox" id="show-rated-comments" value="1" /> Ocultar Comentarios Calificados</label>
      </div>
    </div>
  </div>
  
  <?php if ($cids):?>
  <div class="comments">
    <?php foreach($cids as $item):?>
    <div class="comment-item" id="comment-item-<?php print $item->fbrate_comment_id;?>" data-cid="<?php print $item->fbrate_comment_id;?>"></div>
    <div class="comment-separator" id="comment-separator-<?php print $item->fbrate_comment_id;?>"></div>
    <?php endforeach;?>
  </div>
  <?php endif;?>
  
  <?php endif;?>
</<?php print $ds_content_wrapper ?>>

<?php if (!empty($drupal_render_children)): ?>
  <?php print $drupal_render_children ?>
<?php endif; ?>
