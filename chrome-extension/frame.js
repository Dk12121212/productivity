var url = window.location.href
  .replace('https://github.com', '')
  .replace('/issues', '');

var url = 'https://productivity.gizra.com/per-issue/' + url;
document.querySelector('iframe').src = url;
