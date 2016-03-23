(function ($) {
  var comment_id_fb_id = [];
  Drupal.behaviors.frCommentsLoad = {
    attach: function (context, settings) {
      $('.node-fb-post .comments', context).once('frCommentsLoad', function () {
        comments = $(this).find('.comment-item');
        count = comments.length;
        $(comments).each(function(index){
          cid = $(this).attr('data-cid');
          url = settings.basePath + 'fbrate/comment/' + cid;
          $.post(url, function(data){
            relation = [];
            relation['id'] = data.id;
            relation['cid'] = data.cid;
            i = comment_id_fb_id.length;
            comment_id_fb_id[i] = relation;
            output = '<div class="actions">';
            output += '<div class="cta rate-good"><a href="#">Bueno</a></div>';
            output += '<div class="cta rate-bad"><a href="#">Malo</a></div>';
            output += '</div>';
            output += '<div class="data">';
            output += '<div class="from">' + data.from + '</div>';
            output += '<div class="message">' + data.message + '</div>';
            output += '<div class="likes"><span class="count">' + data.like_count + '</span> <span class="text">Me Gusta</span></div>';
            output += '</div>';
            if ( data.parent == '0' ) {
              $('#comment-item-' + data.cid).html(output);
            } else {
              $('#comment-item-' + data.cid).remove();
              $('#comment-separator-' + data.cid).remove();
              output = '<div class="comment-item child" id="comment-item-'+ data.cid + '" data-cid="' + data.cid + '">' + output + '</div>';
              // Find Parent CID
              parent_cid = frCommentsGetCidById(data.parent);
              if ( parent_cid == 0 ) {
                console.dir('Failed finding Parent Cid');
              } else {
                $('#comment-separator-' + parent_cid).before(output);
                $('#comment-separator-' + parent_cid).addClass('hasChildren');
              }
              
            }
          }, 'json');
        });
      });
    }
  };

  /**
   * Search for an ID relation.
   */
  function frCommentsGetCidById(id) {
    for(i=0; i < comment_id_fb_id.length; i++) {
      item = comment_id_fb_id[i];
      if ( item['id'] == id ) {
        return item['cid'];
      }
    }
    return 0;
  }

})(jQuery);