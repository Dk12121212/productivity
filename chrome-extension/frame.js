var url = window.location.href
  .replace('/issues', '')
  .replace('https://github.com', '');

 var url = 'https://productivity.gizra.com/per-issue/' + repoName + '/' + issueId;
// var url = 'http://localhost/productivity/www/per-issue/' + repoName + '/' + issueId;
 document.querySelector('iframe').src = url;
