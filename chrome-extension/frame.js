var url = window.location.href
  .replace(/chrome-extension:\/\/.*\?url=/, '');


var url = 'https://productivity.gizra.com/per-issue/' + url;
document.querySelector('iframe').src = url;
