Drupal.behaviors.renderDotSVGIssues = {
  attach: function (context, settings) {
  var result = Viz(dataSVG);
  document.body.innerHTML += result;
  }
};
