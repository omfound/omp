<?php if (!empty($image_path)): ?>
   <a target="_blank" href="http://pinterest.com/pin/create/button/?url=<?php print $url; ?>&media=<?php print $image_path; ?>" class="pin-it-button" count-layout="horizontal">
    <img border="0" src="//assets.pinterest.com/images/PinExt.png" title="Pin It" />
  </a>
<?php endif; ?>
