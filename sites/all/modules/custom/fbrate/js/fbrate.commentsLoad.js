(function ($) {
  var comment_id_fb_id = [], rating_active = [];
  Drupal.behaviors.fbrateCommentsLoad = {
    attach: function (context, settings) {
      $('.node-fb-post .comments', context).once('frCommentsLoad', function () {
        comments = $(this).find('.comment-item');
        count = comments.length;
        $(comments).each(function(index){
          cid = $(this).attr('data-cid');
          rating_active[cid] = 0;
          url = settings.basePath + 'fbrate/comment/' + cid;
          $.post(url, function(data){
            url_good = settings.basePath + 'fbrate/comment/' + data.cid + '/good';
            url_bad = settings.basePath + 'fbrate/comment/' + data.cid + '/bad';
            if ( data.rate_status == 1 ) {
              //console.dir(data);
            }
            relation = [];
            relation['id'] = data.id;
            relation['cid'] = data.cid;
            i = comment_id_fb_id.length;
            comment_id_fb_id[i] = relation;
            output = '<div class="actions">';
            output += '<div class="cta rate-good"><a data-rate="rate-good" href="' + url_good + '">Bueno</a></div>';
            output += '<div class="cta rate-bad"><a data-rate="rate-bad" href="' + url_bad + '">Malo</a></div>';
            output += '<div class="rating"></div>';
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
              parent_cid = fbrateCommentsGetCidById(data.parent);
              if ( parent_cid == 0 ) {
                console.dir('Failed finding Parent Cid');
              } else {
                $('#comment-separator-' + parent_cid).before(output);
                $('#comment-separator-' + parent_cid).addClass('hasChildren');
              }
            }
            
            newcomment = $('#comment-item-' + data.cid);
            if ( data.rate_status == 1 ) {
              $(newcomment).addClass('rate-done');
              if ( data.rate.value == '100' ) {
                $(newcomment).addClass('rate-good').find('.rating').text('Bueno');
              } else {
                $(newcomment).addClass('rate-bad').find('.rating').text('Malo');
              }
            }
            // Attach Click to Buttons
            $('#comment-item-' + data.cid + ' .actions .cta a').click(commentsRateClick);
          }, 'json');
        });
      });
    }
  };
  
  function commentsRateClick(e) {
    comment = $(this).parent().parent().parent();
    cid = $(comment).attr('data-cid');
    if ( rating_active[cid] == 0 ) {
      rating_active[cid] = 1;
      comment = $(this).parent().parent().parent();
      url = $(this).attr('href');
      rate = $(this).attr('data-rate');
      text = $(this).text();
      $.post(url, function(data){
        $(comment).addClass('rate-done').addClass(rate);
        $(comment).find('.actions .rating').text(text);
      }, 'json');
    }
    e.preventDefault();
  }

  /**
   * Search for an ID relation.
   */
  function fbrateCommentsGetCidById(id) {
    for(i=0; i < comment_id_fb_id.length; i++) {
      item = comment_id_fb_id[i];
      if ( item['id'] == id ) {
        return item['cid'];
      }
    }
    return 0;
  }
  
  Drupal.behaviors.fbrateCommentsShowRated = {
    attach: function (context, settings) {
      $('#show-rated-comments', context).once('fbrateCommentsShowRated', function () {
        $(this).click(fbrateCommentsShowRatedClick);
      });
    }
  };
  
  function fbrateCommentsShowRatedClick() {
    if ( $(this)[0].checked ) {
      $('.node-fb-post .comments').addClass('show-rated-comments');
    } else {
      $('.node-fb-post .comments').removeClass('show-rated-comments');
    }
  }

})(jQuery);