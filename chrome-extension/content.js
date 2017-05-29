// Avoid recursive frame insertion...
var extensionOrigin = 'chrome-extension://' + chrome.runtime.id;
if (!location.ancestorOrigins.contains(extensionOrigin)) {
  var iframe = document.createElement('iframe');

  // Pass the issue URL as query string to the parent IFrame.
  var issueUrl = window.location.href
    .replace('https://github.com/', '')
    .replace('/issues', '');

  // Must be declared at web_accessible_resources in manifest.json
  iframe.src = chrome.runtime.getURL('frame.html') + '?url=' + issueUrl;

  // Some styles for a fancy sidebar
  iframe.style.cssText = 'width:100%;height:200px;';

  var el = document.querySelector('.gh-header-title');
  el.appendChild(iframe);
}
