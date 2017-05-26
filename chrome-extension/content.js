// Avoid recursive frame insertion...
var extensionOrigin = 'chrome-extension://' + chrome.runtime.id;
if (!location.ancestorOrigins.contains(extensionOrigin)) {
  var iframe = document.createElement('iframe');
  // Must be declared at web_accessible_resources in manifest.json
  iframe.src = chrome.runtime.getURL('frame.html');

  // Some styles for a fancy sidebar
  iframe.style.cssText = 'width:100%;height:200px;';

  var el = document.querySelector('.gh-header-title');
  el.appendChild(iframe);
}
