var url = window.location.href
  .replace('/issues', '')
  .replace('https://github.com', '');

// @todo: This will need to be HTTPS
// var url = 'http://productivity.gizra.com/' + repoName + '/' + issueId;
var url = "https://shoov.io/per-issue/" + url;
document.querySelector('iframe').src = url;
