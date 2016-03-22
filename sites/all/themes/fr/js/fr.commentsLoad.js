(function ($) {
  Drupal.behaviors.frCommentsLoad = {
    attach: function (context, settings) {
      $('.node-fb-post .comments', context).once('frCommentsLoad', function () {
        $(this).find('.comment-item').each(function(index){
          cid = $(this).attr('data-cid');
          url = settings.basePath + 'fbrate/comment/' + cid;
          $.post(url, function(data){
            output = '<div class="actions">';
            output += '<div class="cta rate-good"><a href="#">Bueno</a></div>';
            output += '<div class="cta rate-bad"><a href="#">Malo</a></div>';
            output += '</div>';
            output += '<div class="data">';
            output += '<div class="from">' + data.from + '</div>';
            output += '<div class="message">' + data.message + '</div>';
            output += '<div class="likes"><span class="count">' + data.like_count + '</span> <span class="text">Me Gusta</span></div>';
            output += '</div>';
            $('#comment-item-' + data.cid).html(output);
            if ( data.parent != '0' ) {
              $('#comment-item-' + data.cid).addClass('child');
            }
          }, 'json');
        });
      });
    }
  };


})(jQuery);